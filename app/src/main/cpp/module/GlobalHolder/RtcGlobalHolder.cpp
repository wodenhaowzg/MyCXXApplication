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

RtcGlobalChannel *RtcGlobalHolder::getGlobalChannel() {
    return &global_channel_;
}

RtcGlobalAudio *RtcGlobalHolder::getGlobalAudio() {
    return &global_audio_;
}

RtcGlobalVideo *RtcGlobalHolder::getGlobalVideo() {
    return &global_video_;
}

RTCEngine::AVStreamPublishHandler &RtcGlobalHolder::getAVStreamPublishHandler() {
    return global_publish_handler_;
}

void RtcGlobalHolder::SetAppId(const std::string &app_id) {
    app_id_ = app_id;
}

void RtcGlobalHolder::SetChannelProfile(RtcChannelProfile &profile) {
    channel_profile_ = profile;
}

void RtcGlobalHolder::initSingleton() {
    instance_ = new RtcGlobalHolder();
    instance_->Initialize();
}

void RtcGlobalHolder::Initialize() {
    global_video_.SetRtcGlobalChannel(global_channel_);
}