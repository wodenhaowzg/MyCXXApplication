//
// Created by ZaneWang on 2020/7/26.
//

#include "ThreadUtils.h"
#include "../Common.h"
#include <thread>
#include <chrono> // c++11 提供的时间管理类

using namespace std;

void ThreadUtils::sleep() {
    // 获取当前时间戳，now 默认是微妙
    chrono::system_clock::time_point startTimeStamp = chrono::system_clock::now();
    LOGD("wzg", "calcFunction -> startTimeStamp %lld", startTimeStamp);
    // 线程睡眠 500ms
    std::chrono::milliseconds timespan(500);
    std::this_thread::sleep_for(timespan);
    chrono::system_clock::time_point endTimeStamp = chrono::system_clock::now();
    LOGD("wzg", "calcFunction -> endTimeStamp %lld", endTimeStamp);
    // 计算耗时，注意这里相减，单位必须是 double，不然得到的是0
    chrono::duration<double, milli> spendTime = chrono::duration_cast<chrono::duration<double>>(
            endTimeStamp - startTimeStamp);
    LOGD("wzg", "calcFunction -> spendTime %ld", static_cast<long>(spendTime.count()));

}
