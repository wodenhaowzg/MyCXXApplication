//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAM_MESSAGE_H
#define MYCXXAPPLICATION_DREAM_MESSAGE_H


#include "dream_handler.h"

class dream_message {

public:

    dream_handler m_handler;

    uint64_t GetHandlerId();
};


#endif //MYCXXAPPLICATION_DREAM_MESSAGE_H
