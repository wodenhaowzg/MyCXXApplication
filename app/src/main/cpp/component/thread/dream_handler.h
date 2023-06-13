//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAM_HANDLER_H
#define MYCXXAPPLICATION_DREAM_HANDLER_H


#include "dream_base_utils.h"
#include "dream_looper.h"
#include "dream_message.h"

class DreamHandler {

public:
    DreamHandler(int32_t id = 0);

    void SetId(int32_t id);

    int32_t GetId() const;

    sp<DreamLooper> GetLooper() const;

    virtual void OnMessageReceived(const sp<DreamMessage> &message) = 0;

private:

    friend class DreamLooperRoster;

    int32_t m_id_;
};


#endif //MYCXXAPPLICATION_DREAM_HANDLER_H
