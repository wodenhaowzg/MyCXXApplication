//
// Created by ZaneWang on 2023/6/9.
//

#include "dream_looper.h"


bool dream_looper::postEvent(dream_message *p_message) {
    auto_lock lock(m_mutex);
    auto *event = new Event();
    event->message = p_message;
    m_event_list.push_back(event);
    return true;
}

void dream_looper::loop() {

    while (true) {
        {
            auto_lock lock(m_mutex);
            if (m_exit) {
                break;
            }

            if ()
        }
    }
}
