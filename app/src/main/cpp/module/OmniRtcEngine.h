//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_OMNIRTCENGINE_H
#define MYCXXAPPLICATION_OMNIRTCENGINE_H

#include <map>
#include <mutex>

#include "IOmniRtcEngine.h"
#include "RtcEngineDefines.h"

class OmniRtcEngine : IOmniRtcEngine {

private:
    static OmniRtcEngine *g_instance;
    static std::mutex g_instanceMutex;
    static const char *kLOG_TAG;

    OmniRtcEngineEventHandler *m_handler;
    RtcGlobalInfo m_rtcGlobalInfo;
    std::map<const char*, OmniRtcChannel*> m_channelMap;

    std::mutex m_rtcMutex;

    OmniRtcEngine(void *context, const char *appId, OmniRtcEngineEventHandler *handler) {
        m_handler = handler;
        m_rtcGlobalInfo.appId = appId;
    }

    ~OmniRtcEngine() {
    }

public:
    static IOmniRtcEngine *create(void *context, const char *appId, OmniRtcEngineEventHandler *handler);

    static void destroy();

    void setHandler(OmniRtcEngineEventHandler *engineEventHandler) override;

    OmniRtcChannel *createRtcChannel(const char *channelName) override;
    
    void destroyRtcChannel(const char *channelName) override;

    int setChannelProfile(int profile) override;

    void setServerIp(const char *ip, int port) override;

    int setBusinessUserRole(int role) override;

    int setSlbAddress(const char *slb, const char *slbBackup) override;

    int setServerLogAddress(const char *serverLogUrl) override;

    int setAppExtensionInfo(const char *jsonInfo) override;

    int setAudioProfile(int profile, int scenario) override;

    int setPreferAudioCodec(int codecType, int bitrate, int channels) override;

private:
    void reinitialize(void *context, const char *appId, OmniRtcEngineEventHandler *handler);

    void doDestroy();
};

#endif //MYCXXAPPLICATION_OMNIRTCENGINE_H