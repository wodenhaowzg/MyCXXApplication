//
// Created by ZaneWang on 2023/6/9.
//

#include "dream_handler.h"

bool dream_handler::sendMessage(dream_message *p_message) {
    if (p_message == nullptr) {
        return false;
    }

    if (mp_looper == nullptr) {
        return false;
    }
    return mp_looper->postEvent(p_message);
}
