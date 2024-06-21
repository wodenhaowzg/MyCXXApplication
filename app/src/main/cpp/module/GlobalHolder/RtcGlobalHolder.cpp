//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalHolder.h"

RtcGlobalHolder *RtcGlobalHolder::instance_ = nullptr;
std::once_flag RtcGlobalHolder::once_flag_;

RtcGlobalHolder *RtcGlobalHolder::GetInstance() {
    std::call_once(once_flag_, RtcGlobalHolder::initSingleton);
    return instance_;
}

std::string RtcGlobalHolder::GetAppId() const {
    return app_id_;
}

const RtcGlobalChannel &RtcGlobalHolder::getGlobalChannel() {
    return global_channel_;
}

const RtcGlobalAudio &RtcGlobalHolder::getGlobalAudio() {
    return global_audio_;
}

const RtcGlobalVideo &RtcGlobalHolder::getGlobalVideo() {
    return global_video_;
}

void RtcGlobalHolder::SetAppId(const std::string &app_id) {
    app_id_ = app_id;
}

void RtcGlobalHolder::initSingleton() {
    instance_ = new RtcGlobalHolder();
    instance_->Initialize();
}

void RtcGlobalHolder::Initialize() {
    global_video_.SetRtcGlobalChannel(global_channel_);
}