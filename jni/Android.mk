LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := cryptopp  
LOCAL_SRC_FILES :=  lib/$(TARGET_ARCH_ABI)/libcryptopp.a
include $(PREBUILT_STATIC_LIBRARY)  

include $(CLEAR_VARS)
LOCAL_MODULE    := main
LOCAL_C_INCLUDES  := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := main.cpp
LOCAL_CPPFLAGS := -fexceptions
LOCAL_STATIC_LIBRARIES := cryptopp

LOCAL_CFLAGS += -pie -fPIE
LOCAL_LDFLAGS += -pie -fPIE

include $(BUILD_EXECUTABLE)
