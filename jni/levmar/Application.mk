APP_BUILD_SCRIPT := $(call my-dir)/Android.mk
APP_PROJECT_PATH := $(call my-dir)

APP_CPPFLAGS += -fno-exceptions
APP_CPPFLAGS += -fno-rtti
APP_OPTIM := release

APP_STL := gnustl_static
APP_ABI := armeabi-v7a
