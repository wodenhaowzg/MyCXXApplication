//
// Created on 2024/6/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CORERTCPROJECT_IOMNIRTCENGINE_H
#define CORERTCPROJECT_IOMNIRTCENGINE_H

#include <mutex>
#include <memory>
#include <string>

#include "IOmniRtcEngineEventHandler.h"
#include "IOmniRtcChannel.h"

extern class OmniRtcEngine;

class IOmniRtcEngine {

private:

public:
    static OmniRtcEngine *create(void *context, const std::string &appId, OmniRtcEngineEventHandler *handler) {
        return OmniRtcEngine::create(context, appId, handler);
    }

    static void destroy() {
        return OmniRtcEngine::destroy();
    }

    virtual void setHandler(OmniRtcEngineEventHandler *engineEventHandler) = 0;

    virtual OmniRtcChannel *createRtcChannel(const std::string &channelName) = 0;

//    virtual OmniAudioModule *getOmniAudioModule() = 0;

//    virtual OmniVideoModule *getOmniVideoModule() = 0;

    virtual int setChannelProfile(int profile) = 0;

    virtual void setServerIp(const std::string &ip, int port) = 0;

    virtual int setBusinessUserRole(int role) = 0;

    virtual int setSlbAddress(const std::string &slb, const std::string &slbBackup) = 0;

    virtual int setServerLogAddress(const std::string &serverLogUrl) = 0;

    virtual int setAppExtensionInfo(const std::string &jsonInfo) = 0;

    virtual int setAudioProfile(int profile, int scenario) = 0;

    virtual int setPreferAudioCodec(int codecType, int bitrate, int channels) = 0;
};

#endif //CORERTCPROJECT_IOMNIRTCENGINE_H
