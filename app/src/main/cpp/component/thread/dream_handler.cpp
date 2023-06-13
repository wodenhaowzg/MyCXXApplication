//
// Created by ZaneWang on 2023/6/9.
//

#include "dream_handler.h"
#include "dream_looper_roster.h"

DreamHandler::DreamHandler(int32_t id) : m_id_(id) {
}

void DreamHandler::SetId(int32_t id) {
    m_id_ = id;
}

int32_t DreamHandler::GetId() const {
    return m_id_;
}

sp<DreamLooper> DreamHandler::GetLooper() const {
    extern DreamLooperRoster g_looper_roster;
    return g_looper_roster.FindLooper(GetId());
}