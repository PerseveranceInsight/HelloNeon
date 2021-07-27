LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloneon

ifeq ($(EN_DEBUG),true)
LOCAL_CFLAGS += -D__DEBUG__
endif

LOCAL_C_INCLUDES := fir_filter_intrinsic.h

LOCAL_SRC_FILES += hello_neon_main.c \
				   fir_filter_intrinsic.c 

# ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
# endif

LOCAL_LDLIBS := -lm -llog
LOCAL_LDFLAGS := -nodefaultlibs -lc -lm -ldl


include $(BUILD_EXECUTABLE)

