LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Config.mk

LOCAL_MODULE:= clapack1
#LOCAL_CFLAGS:= -O3 -fPIC
LOCAL_SRC_FILES:= $(ALLOBJ1)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/Config.mk

LOCAL_MODULE:= clapack2
#LOCAL_CFLAGS:= -O3 -fPIC
LOCAL_SRC_FILES:= $(ALLOBJ2)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/Config.mk

LOCAL_MODULE:= clapack3
#LOCAL_CFLAGS:= -O3 -fPIC
LOCAL_SRC_FILES:= $(ALLOBJ3)

include $(BUILD_STATIC_LIBRARY)
