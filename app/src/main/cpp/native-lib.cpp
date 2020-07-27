#include <jni.h>
#include <string>
#include <android/log.h>
#include "ChildObject.h"
#include "TimeUtils.h"

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
