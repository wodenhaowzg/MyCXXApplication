//
// Created by ZaneWang on 2023/6/9.
//

#include "dream_looper.h"
#include "dream_looper_roster.h"

DreamLooperRoster g_looper_roster;

DreamLooper::DreamLooper() = default;

void DreamLooper::SetThreadName(const char *thread_name) {
    m_thread_name_ = thread_name;
}

DreamLooper::HandlerId DreamLooper::RegisterHandler(const sp<DreamHandler> &handler) {
    return g_looper_roster.RegisterHandler(shared_from_this(), handler);
}

void DreamLooper::UnregisterHandler(const HandlerId handler_id) {
    g_looper_roster.UnregisterHandler(handler_id);
}

void DreamLooper::UnregisterHandlers() {
    g_looper_roster.UnregisterHandlers();
}

void DreamLooper::Start() {
    AutoLock lock(m_lock_);
    if (m_thread_ != nullptr) {
        return;
    }
    m_exit_ = false;
    m_thread_ = std::make_shared<std::thread>(&DreamLooper::loop, this);
    LOGI("The loop thread prepare to running.");
}

void DreamLooper::Stop() {
    AutoLock lock(m_lock_);
    if (m_thread_ == nullptr) {
        return;
    }
    m_exit_ = true;
    m_condition_.notify_one();
    m_thread_->join();
    m_thread_ = nullptr;
    UnregisterHandlers();
    LOGI("The loop thread exited.");
}

bool DreamLooper::PostEvent(const sp<DreamMessage> &message) {
    AutoLock lock(m_lock_);
    Event event;
    event.when_us = 0;
    event.message = message;
    m_event_list_.push_back(event);
    LOGI("Succeed in posting a new message. address: %p", message.get());
    m_condition_.notify_one();
    return true;
}

void DreamLooper::loop() {
    const char *thread_name = m_thread_name_.empty() ? "dream_looper" : m_thread_name_.c_str();
    pthread_setname_np(pthread_self(), thread_name);
    LOGI("The loop thread started.");
    while (true) {
        Event event;
        {
            AutoLock lock(m_lock_);
            if (m_exit_) {
                LOGI("The loop thread has been exited.");
                break;
            }

            if (m_event_list_.empty()) {
                LOGI("====== There are no more events to handle, going to wait state. ======");
                lock.wait(m_condition_);
            }
            auto front_event = m_event_list_.front();
            LOGI("Wake up, succeed in getting a new message.");
            m_event_list_.pop_front();
            event = front_event;
        }
        g_looper_roster.DeliverMessage(event.message);
    }
}
