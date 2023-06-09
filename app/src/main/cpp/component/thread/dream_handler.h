//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAM_HANDLER_H
#define MYCXXAPPLICATION_DREAM_HANDLER_H


#include "dream_looper.h"

class dream_handler {


public:
    dream_handler(dream_looper *p_looper) {
        mp_looper = p_looper;
    }

    bool sendMessage(dream_message *p_message);

private:

    dream_looper *mp_looper = nullptr;
};


#endif //MYCXXAPPLICATION_DREAM_HANDLER_H
