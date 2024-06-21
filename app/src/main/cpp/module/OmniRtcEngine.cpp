//
// Created by ZaneWang on 2024/6/18.
//

#include "OmniRtcEngine.h"
#include "RtcGlobalVideo.h"

OmniRtcEngine *OmniRtcEngine::g_instance = nullptr;
std::mutex  OmniRtcEngine::g_instanceMutex;
const char *OmniRtcEngine::LOG_TAG = "wzgtest";

IOmniRtcEngine *IOmniRtcEngine::Create(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
    return OmniRtcEngine::Create(context, appId, handler);
}

void IOmniRtcEngine::Destroy() {
    OmniRtcEngine::Destroy();
}

IOmniRtcEngine *OmniRtcEngine::Create(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
    // TODO 增加参数 context、appId 有效性判断
    std::lock_guard<std::mutex> lock(OmniRtcEngine::g_instanceMutex);
    if (g_instance == nullptr) {
        g_instance = new OmniRtcEngine(context, appId, handler);
    } else {
        g_instance->reinitialize(context, appId, handler);
    }
    return g_instance;
}

void OmniRtcEngine::Destroy() {
    std::lock_guard<std::mutex> lock(g_instanceMutex);
    if (g_instance == nullptr) {
        return;
    }
    g_instance->doDestroy();
    delete g_instance;
}

void OmniRtcEngine::SetHandler(OmniRtcEngineEventHandler *engineEventHandler) {
//    std::lock_guard<std::mutex> lock(m_rtcMutex);
    m_handler = engineEventHandler;
}

OmniRtcChannel *OmniRtcEngine::CreateRtcChannel(const char *channelName) {
    OmniRtcChannel *rtcChannel = m_channelMap[channelName];
    if (rtcChannel == nullptr) {
        rtcChannel = new OmniRtcChannel();
        m_channelMap[channelName] = rtcChannel;
    }
    return rtcChannel;
}

void OmniRtcEngine::DestroyRtcChannel(const char *channelName) {
    OmniRtcChannel *rtcChannel = m_channelMap.find(channelName)->second;
    delete rtcChannel;
    m_channelMap.erase(channelName);
}

int OmniRtcEngine::SetChannelProfile(int profile) {
    m_rtcGlobalInfo.channelProfile = profile;
    m_handler->onError(0);
    return 0;
}

void OmniRtcEngine::SetServerIp(const char *ip, int port) {

}

int OmniRtcEngine::SetBusinessUserRole(int role) {
    return 0;
}

int OmniRtcEngine::SetSlbAddress(const char *slb, const char *slbBackup) {
    return 0;
}

int OmniRtcEngine::SetServerLogAddress(const char *serverLogUrl) {
    return 0;
}

int OmniRtcEngine::SetAppExtensionInfo(const char *jsonInfo) {
    return 0;
}

int OmniRtcEngine::SetAudioProfile(int profile, int scenario) {
    return 0;
}

int OmniRtcEngine::SetPreferAudioCodec(int codecType, int bitrate, int channels) {
    return 0;
}

void OmniRtcEngine::reinitialize(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
    m_handler = handler;
    m_rtcGlobalInfo.appId = appId;
}

void OmniRtcEngine::doDestroy() {
    auto iterator = m_channelMap.begin();
    while (iterator != m_channelMap.end()) {
        OmniRtcChannel *rtcChannel = iterator->second;
        delete rtcChannel;
        iterator++;
    }
    m_channelMap.clear();
    m_handler = nullptr;
}

int OmniRtcEngine::EnableLocalVideo(const char *mediaId, bool enabled) {
    // 更新视频上行流 ID
    if (mediaId == nullptr || mediaId == "") {
        mediaId = video_manager_.getVideoUplinkMediaId();
    } else {
        video_manager_.setVideoUplinkMediaId(mediaId);
    }
    // 接口重复调用，终止流程
    if (enabled == video_local_enabled_) {
        return 0;
    }
    video_local_enabled_ = enabled;
    // 启用/停止视频采集
    // TODO IOmniVideo.EnableLocalVideo
    // 若未加入频道，终止流程
    bool is_joined = channel_manager.IsJoinedChannel();
    if (!is_joined) {
        return 0;
    }
    // 更新视频设备 xml 信息
    // TODO VideoJni.getInstance().EnableVideoDev(mediaId, enabled ? 1 : 0);
    // 上报 onLocalVideoStateChanged 回调状态变更
    // TODO onLocalVideoStateChanged
    return 0;
}

RtcGlobalChannel OmniRtcEngine::GetRtcGlobalChannel() {
    return channel_manager;
}
