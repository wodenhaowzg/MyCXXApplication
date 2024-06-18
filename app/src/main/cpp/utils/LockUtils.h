//
// Created by ZaneWang on 2024/6/13.
//

#ifndef MYCXXAPPLICATION_LOCKUTILS_H
#define MYCXXAPPLICATION_LOCKUTILS_H

#include <memory>
#include <mutex>

namespace LockUtils {
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
}

#endif //MYCXXAPPLICATION_LOCKUTILS_H