//
// Created by ZaneWang on 2020/7/26.
//

#include "TimeUtils.h"

long long TimeUtils::CurrentTimeMillis() {
    return ns2ms(systemTime(SYSTEM_TIME_REALTIME));
}

long long TimeUtils::NanoTime() {
    return systemTime(SYSTEM_TIME_MONOTONIC);
}

long long TimeUtils::UptimeMillis() {
    return ns2ms(systemTime(SYSTEM_TIME_MONOTONIC));
}