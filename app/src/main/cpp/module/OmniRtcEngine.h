//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_OMNIRTCENGINE_H
#define MYCXXAPPLICATION_OMNIRTCENGINE_H

#include <map>
#include <mutex>

#include "IOmniRtcDefines.h"
#include "IOmniRtcEngine.h"
#include "RtcChannelManager.h"
#include "../GlobalHolder/RtcGlobalHolder.h"
#include "RtcEngineDefines.h"
#include "TTTRtcClientCore.h"

class OmniRtcEngine : IOmniRtcEngine {

private:
    OmniRtcEngine() {
    }

    ~OmniRtcEngine() {
    }

public:
    /****************************************** 面向上层调用 *************************************************/

    static IOmniRtcEngine *Create(void *context, const char *app_id, OmniRtcEngineEventHandler *handler);

    static void Destroy();

    /****************************************** 继承 IOmniRtcEngine *************************************************/

    void SetHandler(OmniRtcEngineEventHandler *engine_handler) override;

    IOmniRtcChannel *CreateRtcChannel(const char *channel_name) override;

    void DestroyRtcChannel(const char *channel_name) override;

    RtcStatus SetChannelProfile(RtcChannelProfile profile) override;

    void SetServerIp(const char *ip, int port) override;

    RtcStatus SetBusinessUserRole(BusinessRole role) override;

    void SetSlbAddress(const char *slb, const char *slb_backup) override;

    void SetServerLogAddress(const char *server_url) override;

    RtcStatus SetAppExtensionInfo(const char *json) override;

    RtcStatus SetAudioProfile(int profile, int scenario) override;

    RtcStatus SetPreferAudioCodec(int codec_type, int bitrate, int channels) override;

    RtcStatus EnableLocalVideo(const char *media_id, bool enabled) override;

    /****************************************** 自定义方法 *************************************************/

    static OmniRtcEngine *GetInstance();

private:
    static OmniRtcEngine *g_instance;
    static std::mutex g_instanceMutex;
    static const char *LOG_TAG;

    OmniRtcEngineEventHandler *m_handler_;
    RtcGlobalHolder *global_holder_;
    RtcGlobalChannel* channel_manager_;
    RtcGlobalVideo* video_manager_;
    TTTRtc::ClientCoreContext client_core_context_;
    std::mutex m_rtcMutex;

    void Initialize(void *context, const char * app_id, OmniRtcEngineEventHandler *handler);

    void Reinitialize(void *context, const char * app_id, OmniRtcEngineEventHandler *handler);

    void DoDestroy();
};

#endif // MYCXXAPPLICATION_OMNIRTCENGINE_H