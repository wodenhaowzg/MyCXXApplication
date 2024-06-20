//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALHOLDER_H
#define MYCXXAPPLICATION_RTCGLOBALHOLDER_H


#include <mutex>

class RtcGlobalHolder {

public:
    static RtcGlobalHolder *getInstance();

private:
    RtcGlobalHolder() {
    }

    static void initSingleton();

    // 声明对象实例，静态化
    static RtcGlobalHolder *instance_;
    // 声明锁，静态化
    static std::once_flag once_flag_;
    static std::mutex lock_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALHOLDER_H