#include <stdio.h>

#if __DEBUG__
#include <android/log.h>
#define ex_log(x...) __android_log_print(ANDROID_LOG_INFO, "helloneon", x)
#else
#define ex_log(x...) do {} while (0)
#endif


int main(int argc, char** argv) {
    printf("%s, hello neon\n", __func__);
    ex_log("%s, hello neon", __func__);
    return 0;
}
