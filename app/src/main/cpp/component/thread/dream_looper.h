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
#include "dream_message.h"
#include "dream_handler.h"

typedef std::shared_ptr sp

class dream_looper {

public:

    void registerHandler(dream_handler &handler);

    void start();

    void stop();

    bool postEvent(dream_message &pMessage);

private:
    typedef std::unique_lock<std::mutex> auto_lock;

    struct Event {
        int64_t when_us;
        dream_message message;
    };

    std::list<Event *> m_event_list;
    std::map<uint64_t, dream_handler> m_handler_map;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_exit;
    bool m_started;
    std::thread *m_thread = nullptr;

    void &loop();
};


#endif //MYCXXAPPLICATION_DREAM_LOOPER_H
