//
// Created by ZaneWang on 2024/6/13.
//

#ifndef MYCXXAPPLICATION_REFUITLS_H
#define MYCXXAPPLICATION_REFUITLS_H

#include <memory>
#include <mutex>

namespace RefUtils {
    template<typename T>
    using sp = std::shared_ptr<T>;

    template<typename T, typename... Args>
    sp<T> make_sp(Args &&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using wp = std::weak_ptr<T>;

    template<typename T, typename... Args>
    sp<T> make_wp(Args &&... args) {
        return std::weak_ptr<T>(std::forward<Args>(args)...);
    }

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
        std::unique_lock <std::mutex> m_lock_ptr_;
    };
}

#endif //MYCXXAPPLICATION_REFUITLS_H
