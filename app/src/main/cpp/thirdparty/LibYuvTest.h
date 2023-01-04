//
// Created by ZaneWang on 2023/1/2.
//

#ifndef MYCXXAPPLICATION_LIBYUVTEST_H
#define MYCXXAPPLICATION_LIBYUVTEST_H

#include <jni.h>
#include "libyuv.h"
#include <libyuv/rotate.h>
#include <libyuv/video_common.h>

class MyLibYuv {

public:

    MyLibYuv() {
    };

    ~MyLibYuv() {
        if (m_transformI420Buffer != nullptr) {
            free(m_transformI420Buffer);
            m_transformI420Buffer = nullptr;
        }

        if (m_I420ScaleBuffer != nullptr) {
            free(m_I420ScaleBuffer);
            m_I420ScaleBuffer = nullptr;
        }
    };


    struct JNIPixelFormatST {

        jfieldID srcPixelFormatFieldId;
        jfieldID destPixelFormatFieldId;
        jfieldID srcPixelByteArrayFieldId;
        jfieldID destPixelByteArrayFieldId;
        jfieldID widthFieldId;
        jfieldID heightFieldId;
        jfieldID cropXFieldId;
        jfieldID cropYFieldId;
        jfieldID cropWidthFieldId;
        jfieldID cropHeightFieldId;
        jfieldID scaleWidthFieldId;
        jfieldID scaleHeightFieldId;
        jfieldID rotateFieldId;
        jfieldID isMirrorFieldId;
    };


    JNIPixelFormatST m_jniPixelFormatST;
    JNIPixelFormatST m_jniOptionFormatST;

    uint8 *m_transformI420Buffer = nullptr;
    uint8 *m_I420ScaleBuffer = nullptr;
    int m_transformI420BufferLen = 0;
    int m_I420ScaleBufferLen = 0;

    static uint32 transformPixelFormatToLibYuvFormat(int format);

    static libyuv::RotationMode transformPixelRotateToLibYuvRotate(int rotate);
};

#endif //MYCXXAPPLICATION_LIBYUVTEST_H
