//
// Created by ZaneWang on 2024/6/18.
//

#include <string>
#include "OmniRtcEngine.h"
#include "../GlobalHolder/RtcGlobalVideo.h"
#include "RtcChannelManager.h"
#include "RtcEngineDefines.h"
#include "TTTRtcClientCore.h"

OmniRtcEngine *OmniRtcEngine::g_instance = nullptr;
std::mutex  OmniRtcEngine::g_instanceMutex;
const char *OmniRtcEngine::LOG_TAG = "wzgtest";

IOmniRtcEngine *IOmniRtcEngine::Create(void *context, const char *app_id, OmniRtcEngineEventHandler *handler) {
    return OmniRtcEngine::Create(context, app_id, handler);
}

void IOmniRtcEngine::Destroy() {
    OmniRtcEngine::Destroy();
}

IOmniRtcEngine *OmniRtcEngine::Create(void *context, const char *app_id, OmniRtcEngineEventHandler *handler) {
    if (context == nullptr) {
        return nullptr;
    }
    std::string app_id_str(app_id);
    if (app_id_str.empty()) {
        return nullptr;
    }
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
    m_handler_ = engine_handler;
}

IOmniRtcChannel *OmniRtcEngine::CreateRtcChannel(const char *channel_name) {
    return channel_manager_->CreateRtcChannel(channel_name);
}

void OmniRtcEngine::DestroyRtcChannel(const char *channel_name) {
    channel_manager_->DestroyRtcChannel(channel_name);
}

RtcStatus OmniRtcEngine::SetChannelProfile(RtcChannelProfile profile) {
    RtcGlobalHolder::GetInstance()->SetChannelProfile(profile);
    return FUNCTION_SUCCESS;
}

void OmniRtcEngine::SetServerIp(const char *ip, int port) {
    TTTRtc::IClientCore::getInstance()->setServerAddress(ip, port);
}

RtcStatus OmniRtcEngine::SetBusinessUserRole(BusinessRole role) {
    int ret = TTTRtc::IClientCore::getInstance()->setBusinessUserRole(role);
    return ret == 0 ? FUNCTION_SUCCESS : ERROR_FUNCTION_ERROR_FAILED;
}

void OmniRtcEngine::SetSlbAddress(const char *slb, const char *slb_backup) {
    TTTRtc::IClientCore::getInstance()->SetSlbAddress(slb, slb_backup);
}

void OmniRtcEngine::SetServerLogAddress(const char* server_url) {
//    TTTRtc::IClientCore::getInstance()-> // IClientCore 未实现接口
}

RtcStatus OmniRtcEngine::SetAppExtensionInfo(const char* json) {
    int ret = TTTRtc::IClientCore::getInstance()->setAppExtensionInfo(json);
    return ret == 0 ? FUNCTION_SUCCESS : ERROR_FUNCTION_ERROR_FAILED;
}

RtcStatus OmniRtcEngine::SetAudioProfile(int profile, int scenario) {
    return FUNCTION_SUCCESS;
}

RtcStatus OmniRtcEngine::SetPreferAudioCodec(int codec_type, int bitrate, int channels) {
    int ret = TTTRtc::IClientCore::getInstance()->SetPreferAudioCodec(codec_type, bitrate, channels);
    return ret == 0 ? FUNCTION_SUCCESS : ERROR_FUNCTION_ERROR_FAILED;
}

RtcStatus OmniRtcEngine::EnableLocalVideo(const char* media_id, bool enabled) {
    std::string src_mediaId_string(media_id);
    std::string mediaId_string;
    // 更新视频上行流 ID
    if (src_mediaId_string.empty()) {
        mediaId_string = video_manager_->GetVideoUplinkMediaId();
    } else {
        video_manager_->SetVideoUplinkMediaId(mediaId_string);
    }
    bool is_set_success = video_manager_->SetLocalEnabled(enabled);
    if (!is_set_success) {
        // 接口重复调用，终止流程
        return FUNCTION_SUCCESS;
    }
    // 启用/停止视频采集
    // TODO IOmniVideo.EnableLocalVideo
    // 若未加入频道，终止流程
    bool is_joined = channel_manager_->IsJoinedChannel();
    if (!is_joined) {
        return FUNCTION_SUCCESS;
    }
    // 更新视频设备 xml 信息
    // TODO VideoJni.getInstance().EnableVideoDev(media_id, enabled ? 1 : 0);
    // 上报 onLocalVideoStateChanged 回调状态变更
    // TODO onLocalVideoStateChanged
    return FUNCTION_SUCCESS;
}

OmniRtcEngine *OmniRtcEngine::GetInstance() {
    return (OmniRtcEngine *) g_instance;
}

void OmniRtcEngine::Initialize(void *context, const char* app_id, OmniRtcEngineEventHandler *handler) {
    m_handler_ = handler;
    global_holder_ = RtcGlobalHolder::GetInstance();
    channel_manager_ = global_holder_->getGlobalChannel();
    video_manager_ = global_holder_->getGlobalVideo();
    global_holder_->SetAppId(app_id);
    TTTRtc::IClientCore::getInstance()->initialize(client_core_context_);
}

void OmniRtcEngine::Reinitialize(void *context, const char* app_id, OmniRtcEngineEventHandler *handler) {
    m_handler_ = handler;
    global_holder_->SetAppId(app_id);
}

void OmniRtcEngine::DoDestroy() {
    channel_manager_->destroy();
    m_handler_ = nullptr;
}