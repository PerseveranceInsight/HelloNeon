#ifndef __FIR_FILTER_INTRINSIC_H__
#define __FIR_FILTER_INTRINSIC_H__
void fir_filter_intrinsics(short *output,
                           const short *input,
                           const short *kernel,
                           int width,
                           int kernelSize);
#endif
