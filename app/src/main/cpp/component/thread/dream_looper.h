//
// Created by ZaneWang on 2023/6/9.
//

#ifndef MYCXXAPPLICATION_DREAM_LOOPER_H
#define MYCXXAPPLICATION_DREAM_LOOPER_H

#include <list>
#include <mutex>
#include <iostream>
#include <thread>
#include "dream_message.h"
#include "dream_handler.h"

class dream_looper {

public:

    void registerHandler(dream_handler &handler);

    void start();

    void stop();

    bool postEvent(dream_message& pMessage);

private:
    typedef std::lock_guard<std::mutex> auto_lock;

    struct Event {
        int64_t when_us;
        dream_message *message;
    };

    std::list<Event *> m_event_list;
    std::mutex m_mutex;
    bool m_exit;

    void loop();
};


#endif //MYCXXAPPLICATION_DREAM_LOOPER_H
