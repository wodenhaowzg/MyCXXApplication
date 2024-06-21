//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_OMNIRTCENGINE_H
#define MYCXXAPPLICATION_OMNIRTCENGINE_H

#include <map>
#include <mutex>

#include "IOmniRtcEngine.h"
#include "RtcEngineDefines.h"
#include "RtcGlobalHolder.h"

class OmniRtcEngine : IOmniRtcEngine {

private:
    OmniRtcEngine() {
    }

    ~OmniRtcEngine() {
    }

public:
    static IOmniRtcEngine *Create(void *context, std::string &app_id, OmniRtcEngineEventHandler *handler);

    static void Destroy();

    void SetHandler(OmniRtcEngineEventHandler *engine_handler) override;

    OmniRtcChannel *CreateRtcChannel(std::string &channel_name) override;

    void DestroyRtcChannel(std::string &channel_name) override;

    int SetChannelProfile(int profile) override;

    void SetServerIp(std::string &ip, int port) override;

    int SetBusinessUserRole(int role) override;

    int SetSlbAddress(std::string &slb, std::string &slb_backup) override;

    int SetServerLogAddress(std::string &server_url) override;

    int SetAppExtensionInfo(std::string &json) override;

    int SetAudioProfile(int profile, int scenario) override;

    int SetPreferAudioCodec(int codec_type, int bitrate, int channels) override;

    int EnableLocalVideo(std::string &media_id, bool enabled) override;

private:
    static OmniRtcEngine *g_instance;
    static std::mutex g_instanceMutex;
    static const char *LOG_TAG;

    OmniRtcEngineEventHandler *m_handler_;
    RtcGlobalHolder *global_holder_;
    RtcGlobalChannel channel_manager_;
    RtcGlobalVideo video_manager_;
    std::map<const char *, OmniRtcChannel *> channel_map_;
    std::mutex m_rtcMutex;

    void Initialize(void *context, std::string &appId, OmniRtcEngineEventHandler *handler);

    void Reinitialize(void *context, std::string &appId, OmniRtcEngineEventHandler *handler);

    void DoDestroy();
};

#endif //MYCXXAPPLICATION_OMNIRTCENGINE_H