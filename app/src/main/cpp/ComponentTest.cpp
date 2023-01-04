//
// Created by ZaneWang on 2022/4/16.
//

#include <jni.h>
#include "Common.h"
#include "TimeUtils.h"

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ComponentTest_testComponent(JNIEnv *env, jobject thiz) {

}
extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ComponentTest_nativeTestTimeComponent(JNIEnv *env, jobject thiz) {
    LOGI("native TimeUtils::currentTimeMillis = %lld", TimeUtils::currentTimeMillis());
    LOGD("native TimeUtils::nanoTime = %lld", TimeUtils::nanoTime());
    LOGD("native TimeUtils::uptimeMillis = %lld", TimeUtils::uptimeMillis());
}