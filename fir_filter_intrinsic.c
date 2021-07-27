#include "fir_filter_intrinsic.h"
#include <arm_neon.h>

void fir_filter_intrinsics(short *output,
                           const short* input,
                           const short* kernel,
                           int width,
                           int kernelSize) {
    int nn, offset = -kernelSize/2;
    for (nn = 0; nn < kernelSize/4; nn++) {
        int mm, sum = 0;
        int32x4_t sum_vec = vdupq_n_s32(0);
        for (mm = 0; mm < kernelSize/4; mm++) {
            int16x4_t kernel_vec = vld1_s16(kernel + mm*4);
            int16x4_t input_vec = vld1_s16(input + (nn+offset+mm*4));
            sum_vec = vmlal_s16(sum_vec, kernel_vec, input_vec);
        }

        sum += vgetq_lane_s32(sum_vec, 0);
        sum += vgetq_lane_s32(sum_vec, 1);
        sum += vgetq_lane_s32(sum_vec, 2);
        sum += vgetq_lane_s32(sum_vec, 3);

        if (kernelSize & 3) {
            for (mm = kernelSize - (kernelSize & 3); mm < kernelSize; mm++) {
                sum += kernel[mm] * input[nn+offset+mm];
            }
        }
        output[nn] = (short)((sum + 0x8000) >> 16);
    }
}
