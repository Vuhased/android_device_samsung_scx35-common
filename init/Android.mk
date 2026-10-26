ifeq ($(TARGET_INIT_VENDOR_LIB),libinit_sec)

LOCAL_PATH := $(call my-dir)
LIBINIT_SEC_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := system/core/init system/core/base/include
LOCAL_CFLAGS := -Wall -Wextra -Wno-unused-parameter -DANDROID_TARGET=\"$(TARGET_BOARD_PLATFORM)\"
LOCAL_SRC_FILES := init_sec.cpp
LOCAL_STATIC_LIBRARIES := libbase
LOCAL_MODULE := libinit_sec
LOCAL_CFLAGS += -Wno-error -Wno-error=int-conversion -Wno-error=address -Wno-error=sequence-point -Wno-error=format-security -Wno-error=non-virtual-dtor -Wno-error=date-time
include $(BUILD_STATIC_LIBRARY)

endif
