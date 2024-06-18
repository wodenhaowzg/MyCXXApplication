//
// Created by ZaneWang on 2024/6/13.
//

#ifndef MYCXXAPPLICATION_SINGLEINSTANCE_H
#define MYCXXAPPLICATION_SINGLEINSTANCE_H

#include <mutex>
#include "LogUtils.h"
#include "ThreadUtils.h"
#include "TimeUtils.h"
#include "LockUtils.h"

class SingleInstance {

private:
    // 声明对象实例，静态化
    static SingleInstance *g_instance;
    // 声明锁，静态化
    static std::once_flag g_onceFlag;
    static std::mutex g_lock_;

    std::mutex m_lock_;
    const char *m_text = "我是测试内容";
    int m_count = 0;

    // 私有化构造函数，防止外部 new
    SingleInstance();

    // 对象初始化方法
    static void initSingleton();

public:

    // 获取对象实例
    static SingleInstance *getInstance();

    // 测试方法
    void run();
};


#endif //MYCXXAPPLICATION_SINGLEINSTANCE_H
