#include <jni.h>

//
// Created by ZaneWang on 2024/6/13.
//

#include "SingleInstanceTest.h"
#include <thread>

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_DesignTestJni_nativeStartTest(JNIEnv *env, jobject thiz) {
    SingleInstanceTest *singleInstanceTest = new SingleInstanceTest();
    singleInstanceTest->startTest();
}