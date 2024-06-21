//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_OMNIRTCENGINE_H
#define MYCXXAPPLICATION_OMNIRTCENGINE_H

#include <map>
#include <mutex>

#include "IOmniRtcEngine.h"
#include "RtcEngineDefines.h"
#include "RtcGlobalVideo.h"
#include "RtcGlobalChannel.h"

class OmniRtcEngine : IOmniRtcEngine {

private:
    OmniRtcEngine(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
        m_handler = handler;
        m_rtcGlobalInfo.appId = appId;
    }

    ~OmniRtcEngine() {
    }

public:
    static IOmniRtcEngine *Create(void *context, const char *appId, OmniRtcEngineEventHandler *handler);

    static void Destroy();

    RtcGlobalChannel GetRtcGlobalChannel();

    void SetHandler(OmniRtcEngineEventHandler *engineEventHandler) override;

    OmniRtcChannel *CreateRtcChannel(const char *channelName) override;

    void DestroyRtcChannel(const char *channelName) override;

    int SetChannelProfile(int profile) override;

    void SetServerIp(const char *ip, int port) override;

    int SetBusinessUserRole(int role) override;

    int SetSlbAddress(const char *slb, const char *slbBackup) override;

    int SetServerLogAddress(const char *serverLogUrl) override;

    int SetAppExtensionInfo(const char *jsonInfo) override;

    int SetAudioProfile(int profile, int scenario) override;

    int SetPreferAudioCodec(int codecType, int bitrate, int channels) override;

    int EnableLocalVideo(const char *mediaId, bool enabled) override;

private:
    static OmniRtcEngine *g_instance;
    static std::mutex g_instanceMutex;
    static const char *LOG_TAG;

    OmniRtcEngineEventHandler *m_handler;
    RtcGlobalInfo m_rtcGlobalInfo;
    RtcGlobalChannel channel_manager;
    RtcGlobalVideo video_manager_;
    std::map<const char *, OmniRtcChannel *> m_channelMap;
    std::mutex m_rtcMutex;
    /**
     * 本地视频是否启用
     */
    bool video_local_enabled_;

    void reinitialize(void *context, const char *appId, OmniRtcEngineEventHandler *handler);

    void doDestroy();
};

#endif //MYCXXAPPLICATION_OMNIRTCENGINE_H