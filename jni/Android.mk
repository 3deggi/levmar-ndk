LOCAL_PATH := $(call my-dir)

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
export MAINDIR:= $(LOCAL_PATH)

#LAPACK, BLAS, F2C compilation
include $(CLEAR_VARS)
include $(MAINDIR)/clapack/Android.mk
LOCAL_PATH := $(MAINDIR)
include $(CLEAR_VARS)
LOCAL_MODULE:= lapack
LOCAL_STATIC_LIBRARIES := tmglib clapack1 clapack2 clapack3 blas f2c
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
include $(BUILD_STATIC_LIBRARY)

#LEVMAR compilation
include $(CLEAR_VARS)
LMOBJ = levmar/lm.c levmar/Axb.c levmar/misc.c levmar/lmlec.c levmar/lmbc.c levmar/lmblec.c levmar/lmbleic.c   
LOCAL_MODULE          := levmar
LOCAL_SRC_FILES := $(LMOBJ)  
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
include $(BUILD_STATIC_LIBRARY)

#driver compilation
include $(CLEAR_VARS)
LOCAL_MODULE    := lmdriver
LOCAL_SRC_FILES := jni_part.cpp  
LOCAL_STATIC_LIBRARIES  = levmar lapack
LOCAL_LDLIBS +=  -llog -ldl 
include $(BUILD_SHARED_LIBRARY)
