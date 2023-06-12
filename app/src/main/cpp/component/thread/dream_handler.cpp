//
// Created by ZaneWang on 2023/6/9.
//

#include "dream_handler.h"

uint64_t dream_handler::getId() {
    return m_id;
}

void dream_handler::setId(uint64_t id) {
    m_id = id;
}

void dream_handler::SetLooper(dream_looper &p_looper) {
    mp_looper = p_looper;
}

bool dream_handler::SendMessage(dream_message &p_message) {
    if (mp_looper == nullptr) {
        return false;
    }
    return mp_looper->postEvent(p_message);
}