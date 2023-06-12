//
// Created by ZaneWang on 2023/6/9.
//

#include "DreamLooper.h"
#include "DreamLooperRoster.h"

DreamLooperRoster g_looperRoster;

DreamLooper::DreamLooper() {

}

void DreamLooper::SetThreadName(const char *thread_name) {
    m_thread_name_ = thread_name;
}

DreamLooper::HandlerId DreamLooper::RegisterHandler(const sp<DreamHandler> &handler) {
//    return g_looperRoster.registerHandler(shared_from_this(), handler);
    return 0;
}

void DreamLooper::Start() {
    auto_lock lock(m_lock_);
    if (m_thread_ != nullptr) {
        return;
    }
    const char *thread_name = m_thread_name_.empty() ? "dream_looper" : m_thread_name_.c_str();
    m_thread_ = new std::thread(thread_name, loop());
}

void DreamLooper::Stop() {
    auto_lock lock(m_lock_);
    if (m_thread_ == nullptr) {
        return;
    }
    m_exit_ = true;
    m_condition_.notify_one();
    m_thread_->join();
    m_thread_ = nullptr;
}

bool DreamLooper::PostEvent(const sp<DreamMessage> &message) {
    auto_lock lock(m_lock_);
    Event event;
    event.when_us = 0;
    event.message = message;
    m_event_list_.push_back(event);
    m_condition_.notify_one();
    return true;
}

void DreamLooper::loop() {
    while (true) {
        Event event;
        {
            auto_lock lock(m_lock_);
            if (m_exit_) {
                break;
            }

            if (m_event_list_.empty()) {
                m_condition_.wait(lock);
            }
            event = m_event_list_.front();
            m_event_list_.remove(event);
        }
        g_looperRoster.deliverMessage(event.message);
    }
}
