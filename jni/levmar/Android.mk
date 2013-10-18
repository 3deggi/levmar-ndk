LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/
LOCAL_SRC_FILES := $(LOCAL_PATH)/lm.c \
                   $(LOCAL_PATH)/Axb.c \
                   $(LOCAL_PATH)/misc.c \
                   $(LOCAL_PATH)/lmlec.c \
                   $(LOCAL_PATH)/lmbc.c \
                   $(LOCAL_PATH)/lmblec.c \
                   $(LOCAL_PATH)/lmbleic.c    
                   
LOCAL_MODULE := levmar
include $(BUILD_STATIC_LIBRARY)