LOCAL_PATH := $(call my-dir)

# Prebuilt 32-bit ARM libstlport (stlport was removed from AOSP in Android 8).
# Needed by vendor blobs: libsecnativefeature, libreference-ril_sp, libfactoryutil, gps.default, gpsd
include $(CLEAR_VARS)
LOCAL_MODULE := libstlport
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_SRC_FILES := libstlport.so
include $(BUILD_PREBUILT)
