//
// Created by ZaneWang on 2023/6/12.
//

#ifndef MYCXXAPPLICATION_DREAM_HANDLER_TEST_H
#define MYCXXAPPLICATION_DREAM_HANDLER_TEST_H

#include "dream_handler.h"

class DreamHandlerTest : public DreamHandler, public std::enable_shared_from_this<DreamHandlerTest> {

public:

    void StartTest();

    void StopTest();

    void OnMessageReceived(const sp<DreamMessage> &message);

private:

    sp<DreamLooper> m_looper_ = nullptr;
};


#endif //MYCXXAPPLICATION_DREAM_HANDLER_TEST_H
