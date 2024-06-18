//
// Created by ZaneWang on 2024/6/13.
//

#include "SingleInstanceTest.h"

long long g_total_elapsed = 0;
std::mutex g_lock;

void *runnable(void *args);

void SingleInstanceTest::startTest() {
    // 测试对象是否能 new 出来
//    SingleInstance *singleInstance = new SingleInstance();
//    singleInstance->run();

    // 测试正常调用
//    SingleInstance::getInstance()->run();

    // 测试多线程下调用，以及每个实现方案的性能
    int count = 100;
    while (count > 0) {
        pthread_t tid = 0;
        pthread_create(&tid, nullptr, runnable, nullptr);
        count--;
    }
}

void *runnable(void *args) {
    int count = 20000;
    while (count > 0) {
        long long currentTimeMillis = TimeUtils::CurrentTimeMillis();
        SingleInstance *singleInstance = SingleInstance::getInstance();
        long long currentTimeMillis2 = TimeUtils::CurrentTimeMillis();
        long long elapsed = currentTimeMillis2 - currentTimeMillis;
        if (elapsed > 0) {
            LockUtils::AutoLock lock(g_lock);
            g_total_elapsed += elapsed;
            LOGI("total elapsed: %lld", g_total_elapsed);
        }
        singleInstance->run();
        count--;
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<> dis(1, 10);
        int randomNum = dis(generator);
//        LOGI("randomNum: %d", randomNum); // 观察产生的随机性
        ThreadUtils::Sleep(randomNum);
    }
    return nullptr;
}
