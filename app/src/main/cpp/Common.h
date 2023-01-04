//
// Created by ZaneWang on 2020/7/26.
//

#ifndef MYCXXAPPLICATION_COMMON_H
#define MYCXXAPPLICATION_COMMON_H

#include <android/log.h>

#define BASETAG "wzgtest"

#define LOGI(...) __android_log_print(ANDROID_LOG_DEBUG, BASETAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, BASETAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, BASETAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, BASETAG, __VA_ARGS__)

#define LOGI_TWO(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGD_TWO(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGW_TWO(TAG, ...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE_TWO(TAG, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#endif //MYCXXAPPLICATION_COMMON_H
