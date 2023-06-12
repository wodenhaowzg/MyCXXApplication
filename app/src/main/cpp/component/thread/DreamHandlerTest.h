//
// Created by ZaneWang on 2023/6/12.
//

#ifndef MYCXXAPPLICATION_DREAMHANDLERTEST_H
#define MYCXXAPPLICATION_DREAMHANDLERTEST_H

#include "DreamHandler.h"

class DreamHandlerTest : DreamHandler {

public:

    void StartTest();

    void OnMessageReceived(DreamMessage &message);

private:

    sp<DreamLooper> m_looper_;
};


#endif //MYCXXAPPLICATION_DREAMHANDLERTEST_H
