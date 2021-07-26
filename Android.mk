LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloneon

LOCAL_SRC_FILES := hello_neon_main.c

# ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
# endif

LOCAL_LDLIBS := -llog

include $(BUILD_EXECUTABLE)

