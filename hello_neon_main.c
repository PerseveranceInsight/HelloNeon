#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cpu-features.h>
#include "fir_filter_intrinsic.h"
#include "hello_neon_utils.h"

#if __DEBUG__
#include <android/log.h>
#define LOG_ERROR   ANDROID_LOG_ERROR
#define LOG_INFO    ANDROID_LOG_INFO
#define LOG_DEBUG   ANDROID_LOG_DEBUG
#define LOG_VERBOSE ANDROID_LOG_VERBOSE
#define ex_log(LOG_LEVEL, x...) __android_log_print(LOG_LEVEL, "helloneon", x)
#else
#define ex_log(LOG_LEVEL, x...) do {} while (0)
#endif

static const short fir_kernel[FIR_KERNEL_SIZE] = {
    0x10, 0x20, 0x40, 0x70, 0x8c, 0xa2, 0xce, 0xf0, 0xe9, 0xce, 0xa2, 0x8c, 070, 0x40, 0x20, 0x10,
    0x10, 0x20, 0x40, 0x70, 0x8c, 0xa2, 0xce, 0xf0, 0xe9, 0xce, 0xa2, 0x8c, 070, 0x40, 0x20, 0x10 };

static short        fir_output[FIR_OUTPUT_SIZE];
static short        fir_input_0[FIR_INPUT_SIZE];
static const short* fir_input = fir_input_0 + (FIR_KERNEL_SIZE/2);
static short        fir_output_expected[FIR_OUTPUT_SIZE];




int main(int argc, char** argv) {
    ex_log(LOG_DEBUG,"%s hello NEON" ,__func__);
    char *str;
    uint64_t features;
    char buffer[512];
    char tryNeon = 0;
    double t0, t1, time_c, time_neon;

    {
        int nn;
        for (nn = 0; nn < FIR_INPUT_SIZE; nn++) 
        {
            fir_input_0[nn] = (5*nn) & 255;
        }
        fir_filter_c(fir_output_expected, fir_input, fir_kernel, FIR_OUTPUT_SIZE, FIR_KERNEL_SIZE);
    }

    t0 = now_ms();
    {
        int count = FIR_ITERATIONS;
        for (; count > 0; count--) {
            fir_filter_c(fir_output, fir_input, fir_kernel, FIR_OUTPUT_SIZE, FIR_KERNEL_SIZE);
        }
    }
    t1 = now_ms();
    time_c = t1 - t0;

    features = android_getCpuFeatures();
    if ((features & ANDROID_CPU_ARM_FEATURE_NEON) == 0) {
        ex_log(LOG_ERROR, "CPU doesn't support NEON");
        goto EXIT;
    }

    t0 = now_ms();
    {
        int count = FIR_ITERATIONS;
        for(; count > 0; count--) {
            fir_filter_intrinsics(fir_output, fir_input, fir_kernel, FIR_OUTPUT_SIZE, FIR_KERNEL_SIZE);
        }
    }
    t1 = now_ms();
    time_neon = t1 - t0;

    {
        int nn, fails = 0;
        for (nn = 0; nn < FIR_OUTPUT_SIZE; nn++) {
            if (fir_output[nn] != fir_output_expected[nn]) {
                if (++fails < 16) {
                    ex_log(LOG_DEBUG, "neon[%d] = %d expected %d", nn, fir_output[nn], fir_output_expected[nn]);
                }
            }
        }
        ex_log(LOG_DEBUG, "%d fails\n", fails);
    }
    ex_log(LOG_DEBUG, "time_c : %f time_neon : %f", time_c, 
                                                    time_neon);
EXIT:
    return 0;
}
