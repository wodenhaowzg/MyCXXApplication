//
// Created by ZaneWang on 2023/6/12.
//

#ifndef MYCXXAPPLICATION_DREAMLOOPERROSTER_H
#define MYCXXAPPLICATION_DREAMLOOPERROSTER_H

#include "DreamLooper.h"
#include "dream_base_utils.h"

class DreamLooperRoster {

public:
    DreamLooperRoster();

    DreamLooper::HandlerId registerHandler(const sp<DreamLooper> &looper, const sp<DreamHandler> &handler);

    void unregisterHandler(DreamLooper::HandlerId handlerID);

    void unregisterStaleHandlers();

    int postMessage(const sp<DreamMessage> &msg, int64_t delayUs = 0);

    void deliverMessage(const sp<DreamMessage> &message);

    sp<DreamLooper> findLooper(DreamLooper::HandlerId handlerID);

private:
    struct DreamHandlerInfo {
        wp<DreamLooper> wp_looper;
        wp<DreamHandler> wp_handler;
    };

    std::mutex m_lock_;
    std::map<DreamLooper::HandlerId, DreamHandlerInfo> m_handler_map_;
    DreamLooper::HandlerId m_next_handler_id_;
    std::condition_variable mRepliesCondition;
};


#endif //MYCXXAPPLICATION_DREAMLOOPERROSTER_H
