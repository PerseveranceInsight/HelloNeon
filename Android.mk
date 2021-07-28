LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloneon

ifeq ($(EN_DEBUG),true)
LOCAL_CFLAGS += -D__DEBUG__
endif

LOCAL_C_INCLUDES := $(NDK_ROOT)/sources/android/cpufeatures

LOCAL_C_INCLUDES +=	fir_filter_intrinsic.h \
					hello_neon_utils.h 

LOCAL_SRC_FILES += hello_neon_utils.c \
				   hello_neon_main.c \
				   fir_filter_intrinsic.c 

# ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
# endif

LOCAL_LDLIBS := -lm -llog
LOCAL_LDFLAGS := -nodefaultlibs -lc -lm -ldl

LOCAL_STATIC_LIBRARIES := cpufeatures

include $(BUILD_EXECUTABLE)
include $(NDK_ROOT)/sources/android/cpufeatures/Android.mk

