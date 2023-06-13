//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAM_LOOPER_H
#define MYCXXAPPLICATION_DREAM_LOOPER_H

#include <list>
#include <map>
#include <mutex>
#include <iostream>
#include <thread>
#include "dream_base_utils.h"

class DreamMessage;

class DreamHandler;

class DreamLooper : public std::enable_shared_from_this<DreamLooper> {

public:
    typedef int32_t EventId;
    typedef int32_t HandlerId;

    DreamLooper();

    void SetThreadName(const char *thread_name);

    HandlerId RegisterHandler(const sp<DreamHandler> &handler);

    void UnregisterHandler(const HandlerId handler_id);

    void UnregisterHandlers();

    void Start();

    void Stop();

    bool PostEvent(const sp<DreamMessage> &message);

private:

    struct Event {
        int64_t when_us;
        sp<DreamMessage> message;
    };

    std::list<Event> m_event_list_;
    sp<std::thread> m_thread_ = nullptr;
    std::string m_thread_name_;
    bool m_exit_{};

    std::mutex m_lock_;
    std::condition_variable m_condition_;

    void loop();
};


#endif //MYCXXAPPLICATION_DREAM_LOOPER_H
