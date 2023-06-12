//
// Created by ZaneWang on 2023/6/9.
//

#include "DreamHandler.h"
#include "DreamLooperRoster.h"

void DreamHandler::SetId(int32_t id) {
    m_id_ = id;
}

int32_t DreamHandler::GetId() const {
    return m_id_;
}

sp<DreamLooper> DreamHandler::GetLooper() {
    extern DreamLooperRoster gLooperRoster;
    return gLooperRoster.findLooper(GetId());
}

DreamHandler::DreamHandler() {

}
