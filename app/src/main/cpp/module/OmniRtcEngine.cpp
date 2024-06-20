//
// Created by ZaneWang on 2024/6/18.
//

#include "OmniRtcEngine.h"
#include "RtcGlobalVideo.h"

OmniRtcEngine *OmniRtcEngine::g_instance = nullptr;
std::mutex  OmniRtcEngine::g_instanceMutex;
const char *OmniRtcEngine::kLOG_TAG = "wzgtest";

IOmniRtcEngine *IOmniRtcEngine::create(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
    return OmniRtcEngine::create(context, appId, handler);
}

void IOmniRtcEngine::destroy() {
    OmniRtcEngine::destroy();
}

IOmniRtcEngine *OmniRtcEngine::create(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
    // TODO 增加参数 context、appId 有效性判断
    std::lock_guard<std::mutex> lock(OmniRtcEngine::g_instanceMutex);
    if (g_instance == nullptr) {
        g_instance = new OmniRtcEngine(context, appId, handler);
    } else {
        g_instance->reinitialize(context, appId, handler);
    }
    return g_instance;
}

void OmniRtcEngine::destroy() {
    std::lock_guard<std::mutex> lock(g_instanceMutex);
    if (g_instance == nullptr) {
        return;
    }
    g_instance->doDestroy();
    delete g_instance;
}

void OmniRtcEngine::setHandler(OmniRtcEngineEventHandler *engineEventHandler) {
//    std::lock_guard<std::mutex> lock(m_rtcMutex);
    m_handler = engineEventHandler;
}

OmniRtcChannel *OmniRtcEngine::createRtcChannel(const char *channelName) {
    OmniRtcChannel* rtcChannel = m_channelMap[channelName];
    if (rtcChannel == nullptr) {
        rtcChannel = new OmniRtcChannel();
        m_channelMap[channelName] = rtcChannel;
    }
    return rtcChannel;
}

void OmniRtcEngine::destroyRtcChannel(const char *channelName) {
    OmniRtcChannel* rtcChannel = m_channelMap.find(channelName)->second;
    delete rtcChannel;
    m_channelMap.erase(channelName);
}

int OmniRtcEngine::setChannelProfile(int profile) {
    m_rtcGlobalInfo.channelProfile = profile;
    m_handler->onError(0);
    return 0;
}

void OmniRtcEngine::setServerIp(const char *ip, int port) {

}

int OmniRtcEngine::setBusinessUserRole(int role) {
    return 0;
}

int OmniRtcEngine::setSlbAddress(const char *slb, const char *slbBackup) {
    return 0;
}

int OmniRtcEngine::setServerLogAddress(const char *serverLogUrl) {
    return 0;
}

int OmniRtcEngine::setAppExtensionInfo(const char *jsonInfo) {
    return 0;
}

int OmniRtcEngine::setAudioProfile(int profile, int scenario) {
    return 0;
}

int OmniRtcEngine::setPreferAudioCodec(int codecType, int bitrate, int channels) {
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

int OmniRtcEngine::EnableLocalVideo(bool enabled) {
    if (enabled == video_local_enabled_) {
        return 0;
    }
    video_local_enabled_ = enabled;


    return 0;
}
