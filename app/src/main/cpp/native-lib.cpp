#include <jni.h>
#include <string>
#include <android/log.h>
#include "base/ChildObject.h"
#include "utils/TimeUtils.h"

#include <sys/sysinfo.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mycxxapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    TimeUtils::currentTimeMillis();
    TimeUtils::nanoTime();
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_mycxxapplication_MainActivity_testBase(JNIEnv *env, jobject thiz) {

    // 测试继承
    BaseObject* baseObject = new BaseObject();
    BaseObject* childObject = new ChildObject();

    baseObject->toString();
    baseObject->hashCode();
    childObject->hashCode();
    childObject->hashCode();
}