//
// Created by ZaneWang on 2024/6/18.
//

#include <string>
#include "OmniRtcEngine.h"
#include "RtcGlobalVideo.h"

OmniRtcEngine *OmniRtcEngine::g_instance = nullptr;
std::mutex  OmniRtcEngine::g_instanceMutex;
const char *OmniRtcEngine::LOG_TAG = "wzgtest";

IOmniRtcEngine *IOmniRtcEngine::Create(void *context, std::string &app_id, OmniRtcEngineEventHandler *handler) {
    return OmniRtcEngine::Create(context, app_id, handler);
}

void IOmniRtcEngine::Destroy() {
    OmniRtcEngine::Destroy();
}

IOmniRtcEngine *OmniRtcEngine::Create(void *context, std::string &app_id, OmniRtcEngineEventHandler *handler) {
    // TODO 增加参数 context、app_id 有效性判断
    std::lock_guard<std::mutex> lock(OmniRtcEngine::g_instanceMutex);
    if (g_instance == nullptr) {
        g_instance = new OmniRtcEngine();
        g_instance->Initialize(context, app_id, handler);
    } else {
        g_instance->Reinitialize(context, app_id, handler);
    }
    return g_instance;
}

void OmniRtcEngine::Destroy() {
    std::lock_guard<std::mutex> lock(g_instanceMutex);
    if (g_instance == nullptr) {
        return;
    }
    g_instance->DoDestroy();
    delete g_instance;
}

void OmniRtcEngine::SetHandler(OmniRtcEngineEventHandler *engine_handler) {
//    std::lock_guard<std::mutex> lock(m_rtcMutex);
    m_handler_ = engine_handler;
}

OmniRtcChannel *OmniRtcEngine::CreateRtcChannel(std::string &channel_name) {
    const char *c_channel_name = channel_name.c_str();
    OmniRtcChannel *rtcChannel = channel_map_[c_channel_name];
    if (rtcChannel == nullptr) {
        rtcChannel = new OmniRtcChannel();
        channel_map_[c_channel_name] = rtcChannel;
    }
    return rtcChannel;
}

void OmniRtcEngine::DestroyRtcChannel(std::string &channel_name) {
    const char *c_channel_name = channel_name.c_str();
    OmniRtcChannel *rtcChannel = channel_map_.find(c_channel_name)->second;
    delete rtcChannel;
    channel_map_.erase(c_channel_name);
}

int OmniRtcEngine::SetChannelProfile(int profile) {
    return 0;
}

void OmniRtcEngine::SetServerIp(std::string &ip, int port) {

}

int OmniRtcEngine::SetBusinessUserRole(int role) {
    return 0;
}

int OmniRtcEngine::SetSlbAddress(std::string &slb, std::string &slb_backup) {
    return 0;
}

int OmniRtcEngine::SetServerLogAddress(std::string &server_url) {
    return 0;
}

int OmniRtcEngine::SetAppExtensionInfo(std::string &json) {
    return 0;
}

int OmniRtcEngine::SetAudioProfile(int profile, int scenario) {
    return 0;
}

int OmniRtcEngine::SetPreferAudioCodec(int codec_type, int bitrate, int channels) {
    return 0;
}

int OmniRtcEngine::EnableLocalVideo(std::string &media_id, bool enabled) {
    std::string mediaId_string;
    // 更新视频上行流 ID
    if (media_id.empty()) {
        mediaId_string = video_manager_.GetVideoUplinkMediaId();
    } else {
        video_manager_.SetVideoUplinkMediaId(mediaId_string);
    }
    bool is_set_success = video_manager_.SetLocalEnabled(enabled);
    if (!is_set_success) {
        // 接口重复调用，终止流程
        return 0;
    }
    // 启用/停止视频采集
    // TODO IOmniVideo.EnableLocalVideo
    // 若未加入频道，终止流程
    bool is_joined = channel_manager_.IsJoinedChannel();
    if (!is_joined) {
        return 0;
    }
    // 更新视频设备 xml 信息
    // TODO VideoJni.getInstance().EnableVideoDev(media_id, enabled ? 1 : 0);
    // 上报 onLocalVideoStateChanged 回调状态变更
    // TODO onLocalVideoStateChanged
    return 0;
}

void OmniRtcEngine::Initialize(void *context, std::string &appId, OmniRtcEngineEventHandler *handler) {
    m_handler_ = handler;
    global_holder_ = RtcGlobalHolder::GetInstance();
    channel_manager_ = global_holder_->getChannelManager();
    video_manager_ = global_holder_->getVideoManager();
    global_holder_->SetAppId(appId);
}

void OmniRtcEngine::Reinitialize(void *context, std::string &appId, OmniRtcEngineEventHandler *handler) {
    m_handler_ = handler;
    global_holder_->SetAppId(appId);
}

void OmniRtcEngine::DoDestroy() {
    auto iterator = channel_map_.begin();
    while (iterator != channel_map_.end()) {
        OmniRtcChannel *rtcChannel = iterator->second;
        delete rtcChannel;
        iterator++;
    }
    channel_map_.clear();
    m_handler_ = nullptr;
}