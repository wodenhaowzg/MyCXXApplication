//
// Created by ZaneWang on 2023/6/12.
//

#ifndef MYCXXAPPLICATION_DREAM_LOOPER_ROSTER_H
#define MYCXXAPPLICATION_DREAM_LOOPER_ROSTER_H

#include "dream_looper.h"

class DreamLooperRoster {

public:
    DreamLooperRoster();

    DreamLooper::HandlerId RegisterHandler(const sp<DreamLooper> &looper, const sp<DreamHandler> &handler);

    void UnregisterHandler(DreamLooper::HandlerId handlerId);

    void UnregisterHandlers();

    int PostMessage(const sp<DreamMessage> &msg, int64_t delayUs = 0);

    void DeliverMessage(const sp<DreamMessage> &message);

    sp<DreamLooper> FindLooper(DreamLooper::HandlerId handlerID);

private:
    struct DreamHandlerInfo {
        wp<DreamLooper> wp_looper;
        wp<DreamHandler> wp_handler;
    };

    std::mutex m_lock_;
    std::map<DreamLooper::HandlerId, DreamHandlerInfo> m_handler_map_;
    DreamLooper::HandlerId m_next_handler_id_;
};


#endif //MYCXXAPPLICATION_DREAM_LOOPER_ROSTER_H
