//
// Created by ZaneWang on 2023/6/12.
//

#ifndef MYCXXAPPLICATION_DREAM_BASE_UTILS_H
#define MYCXXAPPLICATION_DREAM_BASE_UTILS_H

#include <memory>
#include <mutex>
#include <android/log.h>

template<typename T>
using sp = std::shared_ptr<T>;

template<typename T>
using wp = std::weak_ptr<T>;

typedef std::unique_lock<std::mutex> auto_lock;

#define BASETAG "wzgtest"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, BASETAG, __VA_ARGS__)

#endif //MYCXXAPPLICATION_DREAM_BASE_UTILS_H
