//
// Created by ZaneWang on 2020/7/26.
//

#include "TimeUtils.h"

#define TAG "TimeUtils"
long long TimeUtils::currentTimeMillis() {
    gettimeofday(&tv, NULL);
    long tv_sec = tv.tv_sec;  // 单位秒
    long tv_usec = tv.tv_usec; // 单位微妙
    LOGD(TAG, "currentTimeMillis tv_sec : %ld | tv_usec : %ld", tv_sec, tv_usec);
    // 转换为毫秒
    long long tv_sec_mill = (long long)tv_sec * 1000; // 这里要把 tv_sec 强制转换为 long long ，不然会溢出
    long long tv_usec_mill = tv_usec / 1000;
    LOGD(TAG, "currentTimeMillis tv_sec_mill : %lld | tv_usec_mill : %lld", tv_sec_mill, tv_usec_mill);
    long long milli = tv_sec_mill + tv_usec_mill;
    return milli;
}

long long TimeUtils::nanoTime() {
    // todo
}


