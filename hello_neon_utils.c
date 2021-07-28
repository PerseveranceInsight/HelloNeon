#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "hello_neon_utils.h"

double now_ms(void) {
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0*res.tv_sec + (double)res.tv_sec/1e6;
}

void fir_filter_c(short *output, 
                  const short* input, 
                  const short* kernel,
                  int width,
                  int kernelSize) {
    int offset = -kernelSize/2;
    int nn = 0;
    for (nn = 0; nn < width; nn++) {
        int sum = 0;
        int mm = 0;
        for (mm = 0; mm < kernelSize; mm++) {
            sum += kernel[mm]*input[nn+offset+mm];
        }
        output[nn] = (short)((sum + 0x8000) >> 16);
    }
}
