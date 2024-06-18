//
// Created by ZaneWang on 2024/6/13.
//
#include "SingleInstance.h"

SingleInstance *SingleInstance::g_instance = nullptr;
std::once_flag SingleInstance::g_onceFlag;
std::mutex SingleInstance::g_lock_;

/**
 * 测试环境
 * 1、模拟 100 个线程
 * 2、每个线程循环 20000 次
 * 3、每次循环随机睡眠 1 - 10ms
 * 测试结果
 * 实现方式1: 7899ms
 * 实现方式2: 8268ms
 * @return
 */
SingleInstance *SingleInstance::getInstance() {
    // 实现方式1
    std::call_once(g_onceFlag, SingleInstance::initSingleton);

    // 实现方式2
//    if (g_instance == nullptr) {
//        LockUtils::AutoLock lock(g_lock_);
//        if (g_instance == nullptr) {
//            initSingleton();
//        }
//    }
    return g_instance;
}

void SingleInstance::initSingleton() {
    g_instance = new SingleInstance();
}

void SingleInstance::run() {
    LockUtils::AutoLock lock(m_lock_);
    m_count++;
    if (m_count % 200 == 0) {
        LOGI("测试进度：%d", m_count);
    }
//    LOGI("获取文本：%s，当前线程 ID：%d", m_text, ThreadUtils::GetCurrentThreadId());
}

SingleInstance::SingleInstance() {
    LOGI("Create SingleInstance!");
}