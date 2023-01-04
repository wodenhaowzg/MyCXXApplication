//
// Created by ZaneWang on 2020/7/26.
//

#include "TimeUtils.h"

long long TimeUtils::currentTimeMillis() {
    return ns2ms(systemTime(SYSTEM_TIME_REALTIME));
}

long long TimeUtils::nanoTime() {
    return systemTime(SYSTEM_TIME_MONOTONIC);
}

long long TimeUtils::uptimeMillis() {
    return ns2ms(systemTime(SYSTEM_TIME_MONOTONIC));
}


