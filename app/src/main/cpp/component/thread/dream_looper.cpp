//
// Created by ZaneWang on 2023/6/9.
//

#include "dream_looper.h"


bool dream_looper::postEvent(dream_message &p_message) {
    auto_lock lock(m_mutex);
    auto *event = new Event();
    event->message = p_message;
    m_event_list.push_back(event);
    return true;
}

void dream_looper::loop() {
    while (true) {
        dream_message message;
        dream_handler handler;
        {
            auto_lock lock(m_mutex);
            if (m_exit) {
                break;
            }

            if (m_event_list.empty()) {
                m_condition.wait(lock);
            }
            auto *event = m_event_list.front();
            m_event_list.remove(event);
            message = event->message;

            auto iter = m_handler_map.find(message.GetHandlerId());
            if (iter == m_handler_map.end()){
                continue;
            }
            handler = iter->second;
        }
        handler.onMessageReceived(message);
    }
}

void dream_looper::start() {
    auto_lock lock(m_mutex);
    if (m_started) {
        return;
    }
    m_thread = new std::thread(loop());
    m_thread->join();
    m_started = true;
}

void dream_looper::stop() {
    auto_lock lock(m_mutex);
    if (!m_started) {
        return;
    }
    m_exit = true;
    m_started = false;
}

void dream_looper::registerHandler(dream_handler &handler) {
    handler.setId(1);

}
