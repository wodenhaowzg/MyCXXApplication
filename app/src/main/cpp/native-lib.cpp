#include <jni.h>
#include <string>
#include <android/log.h>
#include "base/ChildObject.h"
#include "utils/TimeUtils.h"

#include <sys/sysinfo.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mycxxapplication_ui_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_mycxxapplication_MainActivity_testBase(JNIEnv *env, jobject thiz) {

    // 测试继承
//    BaseObject *baseObject = new BaseObject();
//    BaseObject *childObject = new ChildObject();

//    baseObject->toString();
//    baseObject->hashCode();
//    childObject->hashCode();
//    childObject->hashCode();

    /**
     * 对象基本功能测试
     * 问题：对象函数传递，是引用传递还是值传递？
     * 答：默认是值传递，如果想引用传递，必须添加 & 符号。
     */
    BaseObject obj("BaseObject");
    obj.transTest();
}