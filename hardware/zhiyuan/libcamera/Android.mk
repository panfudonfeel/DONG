LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:=               \
    S3C6410CameraHardware.cpp      \
    Ov965xCamera.cpp

LOCAL_SHARED_LIBRARIES:= \
    libui \
    libutils \
    libbinder \
    liblog \
    libcamera_client

LOCAL_MODULE:= libcamera

LOCAL_MODULE_TAGS := eng

LOCAL_C_INCLUDES += \
                frameworks/base/libs

include $(BUILD_SHARED_LIBRARY)
