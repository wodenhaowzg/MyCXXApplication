//
// Created by ZaneWang on 2020/7/26.
//

#ifndef MYCXXAPPLICATION_COMMON_H
#define MYCXXAPPLICATION_COMMON_H

#include <android/log.h>
#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <cstdint>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGW(TAG, ...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#define BASETAG "WZGTEST"

#endif //MYCXXAPPLICATION_COMMON_H
