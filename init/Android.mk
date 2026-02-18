ifeq ($(TARGET_INIT_VENDOR_LIB),libinit_sec)

LOCAL_PATH := $(call my-dir)
LIBINIT_SEC_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional

# Прописываем пути к папкам с заголовками вручную
LOCAL_C_INCLUDES := \
    system/core/init \
    system/core/base/include \
    external/selinux/libselinux/include

LOCAL_CFLAGS := -Wall -DANDROID_TARGET=\"$(TARGET_BOARD_PLATFORM)\"
LOCAL_SRC_FILES := init_sec.cpp
LOCAL_MODULE := libinit_sec

# Оставляем только libbase_headers, она точно есть в Oreo
LOCAL_HEADER_LIBRARIES := libbase_headers

include $(BUILD_STATIC_LIBRARY)

endif
