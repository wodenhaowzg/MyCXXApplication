//
// Created by ZaneWang on 2023/6/12.
//

#include "DreamHandlerTest.h"
#include "DreamLooper.h"

void DreamHandlerTest::StartTest() {
    m_looper_ = std::make_shared<DreamLooper>();
    DreamLooper *p_looper = m_looper_.get();
    p_looper->SetThreadName("aaa");
    p_looper->RegisterHandler(this);
    p_looper->Start();

    DreamMessage message;
    message.SetWhat(1);
    message.SetInt32("arg", 2);
    message.post(0);
}

void DreamHandlerTest::OnMessageReceived(DreamMessage &message) {
    uint32_t what = message.GetWhat();
    switch (what) {
        case 1:
            int a = 0;
            message.FindInt32("arg", &a);
            LOGI("Receive 1 message, arg: %d", a);
            break;
    }
}
