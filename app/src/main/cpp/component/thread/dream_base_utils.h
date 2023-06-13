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

class AutoLock {
public:

    explicit inline AutoLock(std::mutex &mutex) : m_lock_(mutex) {
        m_lock_ptr_ = std::unique_lock<std::mutex>(m_lock_);
    }

    inline ~AutoLock() {
        m_lock_ptr_.unlock();
    }

    inline void wait(std::condition_variable &condition) { return condition.wait(m_lock_ptr_); }

private:
    std::mutex &m_lock_;
    std::unique_lock<std::mutex> m_lock_ptr_;
};

#define BASETAG "DREAM_LOOP"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, BASETAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_INFO, BASETAG, __VA_ARGS__)

#endif //MYCXXAPPLICATION_DREAM_BASE_UTILS_H
