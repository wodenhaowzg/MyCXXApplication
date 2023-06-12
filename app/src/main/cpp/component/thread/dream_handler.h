//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAM_HANDLER_H
#define MYCXXAPPLICATION_DREAM_HANDLER_H


#include "dream_looper.h"

class dream_handler {

public:

    dream_handler(){

    }

    void setId(uint64_t id);

    void SetLooper(dream_looper &p_looper);

    uint64_t getId();

    bool SendMessage(dream_message &p_message);

    void onMessageReceived(dream_message &message) = 0;

private:

    uint64_t m_id;
    dream_looper mp_looper;
};


#endif //MYCXXAPPLICATION_DREAM_HANDLER_H
