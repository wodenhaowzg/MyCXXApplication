#include <jni.h>
#include <thread>
#include <unistd.h>

//
// Created by ZaneWang on 2023/4/17.
//

pthread_t m_pTestThread = 0;
//pthread_t* m_pTestThread2 = 0;
void* run(void* arg);

int calc();

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ThreadTest_nativeStartTest(JNIEnv *env, jobject thiz) {
    pthread_create(&m_pTestThread, nullptr, run, nullptr);
}

void* run(void* arg) {
//    pthread_create(m_pTestThread2, nullptr, run, nullptr);
    while (true) {
        int b = calc();
        usleep(100 * 1000);
    }
}

int calc() {
    int a = 100;
    for (int i = 0; i < 100000000000; ++i) {
        a = a + i;
    }
    return a;
}
