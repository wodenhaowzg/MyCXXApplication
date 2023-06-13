//
// Created by ZaneWang on 2023/6/12.
//

#include <unistd.h>
#include "dream_handler_test.h"
#include "dream_looper.h"

void DreamHandlerTest::StartTest() {
    // 创建消息队列
    m_looper_ = std::make_shared<DreamLooper>();
    m_looper_->SetThreadName("aaa");
    m_looper_->RegisterHandler(shared_from_this());
    m_looper_->Start();
    // 发送3条消息测试
    sp<DreamMessage> message = std::make_shared<DreamMessage>(1, GetId());
    message->SetInt32("arg", 2);
    message->PostMessage(0);
    usleep(1 * 1000);
    sp<DreamMessage> message2 = std::make_shared<DreamMessage>(2, GetId());
    message2->SetInt32("arg", 4);
    message2->PostMessage(0);
    usleep(1 * 1000);
    sp<DreamMessage> message3 = std::make_shared<DreamMessage>(3, GetId());
    message3->SetInt32("arg", 5);
    message3->PostMessage(0);
    // 销毁消息队列
    m_looper_->UnregisterHandler(GetId());
    m_looper_->Stop();
}

void DreamHandlerTest::StopTest() {
// 销毁消息队列
    m_looper_->UnregisterHandler(GetId());
    m_looper_->Stop();
}

void DreamHandlerTest::OnMessageReceived(const sp<DreamMessage> &message) {
    if (message == nullptr || message.get() == nullptr) {
        return;
    }
    uint32_t what = message->GetWhat();
    switch (what) {
        case 1: {
            int a = 0;
            message->FindInt32("arg", &a);
            LOGI("Receive 1 message, arg: %d", a);
            break;
        }
        case 2: {
            int b = 0;
            message->FindInt32("arg", &b);
            LOGI("Receive 2 message, arg: %d", b);
            break;
        }
        case 3: {
            int c = 0;
            message->FindInt32("arg", &c);
            LOGI("Receive 3 message, arg: %d", c);
            break;
        }
    }
}
