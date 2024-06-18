//
// Created by ZaneWang on 2022/4/16.
//

#include <jni.h>
#include "LogUtils.h"
#include "TimeUtils.h"

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ComponentTest_testComponent(JNIEnv *env, jobject thiz) {

}
extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ComponentTest_nativeTestTimeComponent(JNIEnv *env, jobject thiz) {
    LOGI("native TimeUtils::CurrentTimeMillis = %lld", TimeUtils::CurrentTimeMillis());
    LOGD("native TimeUtils::NanoTime = %lld", TimeUtils::NanoTime());
    LOGD("native TimeUtils::UptimeMillis = %lld", TimeUtils::UptimeMillis());
}