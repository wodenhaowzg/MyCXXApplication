//
// Created by ZaneWang on 2/25/21.
//

#ifndef MYCXXAPPLICATION_BYTEBUFFERTEST_H
#define MYCXXAPPLICATION_BYTEBUFFERTEST_H

#include <jni.h>

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_ByteBufferTest_setByteBuffer(JNIEnv *env, jobject thiz, jobject buffer);

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_ByteBufferTest_renderBitmap(JNIEnv *env, jobject thiz, jobject surface, jint width, jint height, jint bufferLen);

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_ByteBufferTest_renderBitmap2(JNIEnv *env, jobject thiz, jbyteArray array, jobject surface, jint width, jint height, jint bufferLen);

#endif //MYCXXAPPLICATION_BYTEBUFFERTEST_H