#include <jni.h>
#include <cstring>
#include "Common.h"
#include "JNIYuvDataTransfer.h"

//
// Created by ZaneWang on 2022/12/30.
//

const signed int TTT_FOURCC_NV21 = 1;
const signed int TTT_FOURCC_NV12 = 2;
const signed int TTT_FOURCC_RGBA = 3;
const signed int TTT_FOURCC_ABGR = 4;
const signed int TTT_FOURCC_I420 = 5;
const signed int TTT_FOURCC_ARGB = 6;

extern "C" JNIEXPORT jlong JNICALL Java_com_example_mycxxapplication_JNITransDataTest_00024YuvDataTransfer_nativeInitialize(JNIEnv *env, jobject thiz, jobject transfer) {
    auto *yuvDataTransfer = new YuvDataTransfer();
    jclass videoYuvScaleBeanClass = env->FindClass("com/example/mycxxapplication/JNITransDataTest$YuvDataTransfer$JNIYuvDataBean");
    if (videoYuvScaleBeanClass == nullptr) {
        return 0;
    }
    yuvDataTransfer->m_videoYuvDataST.formatFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mPixelFormat", "I");
    yuvDataTransfer->m_videoYuvDataST.srcDataArrayFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mSrcByteArray", "[B");
    yuvDataTransfer->m_videoYuvDataST.destDataArrayFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mDestByteArray", "[B");
    yuvDataTransfer->m_videoYuvDataST.srcBufferFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mSrcDirectByteBuffer", "Ljava/nio/ByteBuffer;");
    yuvDataTransfer->m_videoYuvDataST.cropBufferFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mCropDirectByteBuffer", "Ljava/nio/ByteBuffer;");
    yuvDataTransfer->m_videoYuvDataST.destBufferFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mDestDirectByteBuffer", "Ljava/nio/ByteBuffer;");
    yuvDataTransfer->m_videoYuvDataST.widthFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mWidth", "I");
    yuvDataTransfer->m_videoYuvDataST.heightFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mHeight", "I");
    yuvDataTransfer->m_videoYuvDataST.cropXFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mCropX", "I");
    yuvDataTransfer->m_videoYuvDataST.cropYFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mCropY", "I");
    yuvDataTransfer->m_videoYuvDataST.cropWidthFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mCropWidth", "I");
    yuvDataTransfer->m_videoYuvDataST.cropHeightFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mCropHeight", "I");
    yuvDataTransfer->m_videoYuvDataST.scaleWidthFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mScaleWidth", "I");
    yuvDataTransfer->m_videoYuvDataST.scaleHeightFieldId = env->GetFieldID(videoYuvScaleBeanClass, "mScaleHeight", "I");
    yuvDataTransfer->m_videoYuvDataST.rotate = env->GetFieldID(videoYuvScaleBeanClass, "mRotate", "I");
    yuvDataTransfer->m_videoYuvDataST.mirrored = env->GetFieldID(videoYuvScaleBeanClass, "mIsMirrored", "Z");
    return (jlong) yuvDataTransfer;
}
extern "C" JNIEXPORT jint JNICALL Java_com_example_mycxxapplication_JNITransDataTest_00024YuvDataTransfer_nativeTransferObjectToCXX(JNIEnv *env, jobject thiz, jlong pointer, jobject videoYuvDataBeanObj) {
    if (pointer == 0) {
        return -100;
    }
    auto *p_yuvDataTransfer = (YuvDataTransfer *) pointer;
    YuvDataTransfer::VideoDataScaleST videoDataScaleSt = p_yuvDataTransfer->m_videoYuvDataST;
    int yuvFormat = env->GetIntField(videoYuvDataBeanObj, videoDataScaleSt.formatFieldId);
    // 获取原始内存首地址
    jbyte *p_srcByteArray = nullptr;
    void *p_srcByteBuffer = nullptr;
    auto srcByteArrayObj = (jbyteArray) env->GetObjectField(videoYuvDataBeanObj, videoDataScaleSt.srcDataArrayFieldId);
    if (srcByteArrayObj != nullptr) {
        p_srcByteArray = env->GetByteArrayElements(srcByteArrayObj, nullptr);
    }
    jobject srcByteBufferObj = env->GetObjectField(videoYuvDataBeanObj, p_yuvDataTransfer->m_videoYuvDataST.srcBufferFieldId);
    if (srcByteBufferObj != nullptr) {
        p_srcByteBuffer = env->GetDirectBufferAddress(srcByteBufferObj);
    }

    if (p_srcByteArray == nullptr && p_srcByteBuffer == nullptr) {
        return -102;
    }
    // 获取目标内存首地址
    jbyte *p_destByteArray = nullptr;
    void *p_destByteBuffer = nullptr;
    auto destByteArrayObj = (jbyteArray) env->GetObjectField(videoYuvDataBeanObj, videoDataScaleSt.destDataArrayFieldId);
    if (destByteArrayObj != nullptr) {
        p_destByteArray = env->GetByteArrayElements(destByteArrayObj, nullptr);
    }
    jobject destByteBufferObj = env->GetObjectField(videoYuvDataBeanObj, p_yuvDataTransfer->m_videoYuvDataST.destBufferFieldId);
    if (destByteBufferObj != nullptr) {
        p_destByteBuffer = env->GetDirectBufferAddress(destByteBufferObj);
    }

    if (p_destByteArray == nullptr && p_destByteBuffer == nullptr) {
        return -103;
    }
    int width = env->GetIntField(videoYuvDataBeanObj, p_yuvDataTransfer->m_videoYuvDataST.widthFieldId);
    int height = env->GetIntField(videoYuvDataBeanObj, p_yuvDataTransfer->m_videoYuvDataST.heightFieldId);
    LOGI("YuvDataTransfer Receive java object, yuv format: %d, width: %d, height: %d", yuvFormat, width, height);
    // 内存拷贝
    memcpy(p_destByteArray, p_srcByteArray, width * height * 4);
    // 释放 JNI 资源
    if (srcByteArrayObj != nullptr && p_srcByteArray != nullptr) {
        env->ReleaseByteArrayElements(srcByteArrayObj, p_srcByteArray, JNI_ABORT);
    }

    if (destByteArrayObj != nullptr && p_destByteArray != nullptr) {
        env->ReleaseByteArrayElements(destByteArrayObj, p_destByteArray, JNI_ABORT);
    }
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_JNITransDataTest_00024YuvDataTransfer_nativeUnInitialize(JNIEnv *env, jobject thiz, jlong pointer) {
    auto *p_yuvDataTransfer = (YuvDataTransfer *) pointer;
    delete p_yuvDataTransfer;
}