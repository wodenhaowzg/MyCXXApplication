//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAMHANDLER_H
#define MYCXXAPPLICATION_DREAMHANDLER_H


#include "dream_base_utils.h"
#include "DreamLooper.h"
#include "DreamMessage.h"

class DreamHandler {

public:
    DreamHandler();

    void SetId(int32_t id);

    int32_t GetId() const;

    sp<DreamLooper> GetLooper();

    virtual void OnMessageReceived(DreamMessage &message) = 0;

private:

    friend class DreamLooperRoster;

    int32_t m_id_;
};


#endif //MYCXXAPPLICATION_DREAMHANDLER_H
