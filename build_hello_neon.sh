export EN_DEBUG=true
ndk-build -B APP_BUILD_SCRIPT=Android.mk NDK_PROJECT_PATH=. APP_ABI=arm64-v8a NDK_APPLICATION_MK=Application.mk NDK_DEBUG=1
