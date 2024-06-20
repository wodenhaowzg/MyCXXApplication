//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalHolder.h"

RtcGlobalHolder *RtcGlobalHolder::instance_ = nullptr;
std::once_flag RtcGlobalHolder::once_flag_;

RtcGlobalHolder *RtcGlobalHolder::getInstance() {
    std::call_once(once_flag_, RtcGlobalHolder::initSingleton);
    return instance_;
}

void RtcGlobalHolder::initSingleton() {
    instance_ = new RtcGlobalHolder();
}
