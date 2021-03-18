//
// Created by ZaneWang on 2/25/21.
//

#include <unistd.h>
#include <android/log.h>
#include <android/native_window_jni.h>
#include "ByteBufferTest.h"

unsigned char *m_pBuffer;

jboolean renderYuvDecodedFrame(JNIEnv *env, jobject thiz, unsigned char *yuvFrame, jint width, jint height, jobject surface, jint bufferLen);

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_ByteBufferTest_setByteBuffer(JNIEnv *env, jobject thiz, jobject buffer) {
    m_pBuffer = static_cast<unsigned char *>(env->GetDirectBufferAddress(buffer));
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_ByteBufferTest_renderBitmap(JNIEnv *env, jobject thiz, jobject surface, jint width, jint height, jint bufferLen) {
    renderYuvDecodedFrame(env, thiz, m_pBuffer, width, height, surface, bufferLen);
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_ByteBufferTest_renderBitmap2(JNIEnv *env, jobject thiz, jbyteArray array, jobject surface, jint width, jint height, jint bufferLen) {
    auto *buf = reinterpret_cast<unsigned char *>(env->GetByteArrayElements(array, nullptr));
    renderYuvDecodedFrame(env, thiz, buf, width, height, surface, bufferLen);
    env->ReleaseByteArrayElements(array, reinterpret_cast<jbyte *>(buf), 0);
}

jboolean renderYuvDecodedFrame(JNIEnv *env, jobject thiz, unsigned char *yuvFrame, jint width, jint height, jobject surface, jint bufferLen) {
    ANativeWindow_Buffer buffer;
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    if (window == nullptr) {
//        LOGE("test", "create ANativeWindow failed!");
        return static_cast<jboolean>(false);
    }
    ANativeWindow_setBuffersGeometry(window, width, height, WINDOW_FORMAT_RGBA_8888);
    int32_t lockRet = ANativeWindow_lock(window, &buffer, nullptr);
    if (lockRet != 0) {
        ANativeWindow_release(window);
//        LOGE("test", "lock ANativeWindow failed!");
        return static_cast<jboolean>(false);
    }

    auto *pSrc = (uint8_t *) buffer.bits;
    memcpy(pSrc, yuvFrame, bufferLen);

//    auto *pDst = (uint8_t *) buffer.bits;
//    auto *pSrc = (uint8_t *) yuvFrame;
//    for (int i = 0; i < buffer.height; i++) {
//        memcpy(pDst + width * 4 * i, pSrc + buffer.stride * 4 * i, width * 4);
//    }

//    int32_t *bitmapPixes = (int32_t *) yuvFrame;
//    uint32_t *line = (uint32_t *) buffer.bits;
//    for (int y = 0; y < buffer.height; y++) {
//        for (int x = 0; x < buffer.width; x++) {
//            line[x] = bitmapPixes[buffer.height * y + x];
//        }
//        line = line + buffer.stride;
//    }


    ANativeWindow_unlockAndPost(window);
    ANativeWindow_release(window);
    return static_cast<jboolean>(true);
}
