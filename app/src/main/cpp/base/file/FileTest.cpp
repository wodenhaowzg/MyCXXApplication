//
// Created by ZaneWang on 2021/12/11.
//

#include <jni.h>

#include <fstream>

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_FileTest_nativeStartTest(JNIEnv *env, jobject thiz) {

    std::fstream fstream("1111");
//    fstream <<  "aaa" << endl
}