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

const std::string &RtcGlobalHolder::GetAppId() const {
    return app_id_;
}

const RtcGlobalChannel &RtcGlobalHolder::getChannelManager() {
    return channel_manager_;
}

const RtcGlobalVideo &RtcGlobalHolder::getVideoManager() {
    return video_manager_;
}

void RtcGlobalHolder::SetAppId(const std::string &app_id) {
    app_id_ = app_id;
}

void RtcGlobalHolder::initSingleton() {
    instance_ = new RtcGlobalHolder();
    instance_->Initialize();
}

void RtcGlobalHolder::Initialize() {
    video_manager_.SetRtcGlobalChannel(channel_manager_);
}