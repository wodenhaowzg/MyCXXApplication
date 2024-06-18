#include <jni.h>
#include <sstream>
#include <android/log.h>
#include "TimeUtils.h"
#include "ThreadUtils.h"

//
// Created by ZaneWang on 2024/6/13.
//

void *runnable2(void *args);

void printLog1();

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_LogTestJni_nativeStartTest(JNIEnv *env, jobject thiz) {
    // 测试日志输出性能
    pthread_t tid;
    pthread_create(&tid, nullptr, runnable2, nullptr);
}

void *runnable2(void *args) {
    int test_count = 500;
    long long currentTimeMillis = TimeUtils::CurrentTimeMillis();
    while (test_count > 0) {
        printLog1();
        test_count--;
        ThreadUtils::Sleep(1);
        if (test_count % 500 == 0) {
            __android_log_print(ANDROID_LOG_INFO, "wzgtest", "测试进度：%d", test_count);
        }
    }
    long long currentTimeMillis2 = TimeUtils::CurrentTimeMillis();
    __android_log_print(ANDROID_LOG_INFO, "wzgtest", "测试完成，耗时：%lld", (currentTimeMillis2 - currentTimeMillis));
    return nullptr;
}

void printLog1() {
    std::stringstream ss;
    ss << "Log test, <" << "arg1" << 123 << ", arg2: " << 0.5 << ", arg3: " << "123123123" << ", arg4: " << false << ", arg5: " << "sssssss";
    const char* test = ss.str().c_str();
    __android_log_print(ANDROID_LOG_DEBUG, "wzgtest", "content: %s", test);
}
