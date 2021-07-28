#ifndef __HELLO_NEON_UTILS_H__
#define __HELLO_NEON_UTILS_H__

#define FIR_KERNEL_SIZE 32
#define FIR_OUTPUT_SIZE 25600
#define FIR_INPUT_SIZE (FIR_OUTPUT_SIZE + FIR_KERNEL_SIZE)
#define FIR_ITERATIONS 600

void fir_filter_c(short *output, const short *input, const short *kernel, int width, int kernelSize);

double now_ms(void);
#endif
