//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_OMNIRTCENGINE_H
#define MYCXXAPPLICATION_OMNIRTCENGINE_H

#include <mutex>
#include <memory>
#include <string>
#include <android/log.h>

#include "IOmniRtcEngine.h"

class OmniRtcEngine : IOmniRtcEngine {

private:
    static OmniRtcEngine *g_instance;
    static std::mutex g_instanceMutex;
    static const char *kLOG_TAG;

    OmniRtcEngine(void *context, const std::string &appId, OmniRtcEngineEventHandler *handler) {
        __android_log_print(ANDROID_LOG_INFO, kLOG_TAG, "The OmniRtcEngine created. address: %p", this);
    }

    ~OmniRtcEngine(void *context, const std::string &appId, OmniRtcEngineEventHandler *handler) {
        __android_log_print(ANDROID_LOG_INFO, kLOG_TAG, "The OmniRtcEngine destroyed. address: %p", this);
    }

public:
    static OmniRtcEngine *create(void *context, const std::string &appId, OmniRtcEngineEventHandler *handler) {
//        if (context == nullptr) {
//            return nullptr;
//        }
        std::lock_guard<std::mutex> lock(g_instanceMutex);
        if (g_instance == nullptr) {
            g_instance = new OmniRtcEngine(context, appId, handler);
        } else {
            g_instance->reinitialize(context, appId, handler);
        }
        return g_instance;
    }

    static destroy() {
        std::lock_guard<std::mutex> lock(g_instanceMutex);
        __android_log_print(ANDROID_LOG_INFO, kLOG_TAG, "destroy -> address: %p", this);
        delete g_instance;
    }

    void setHandler(OmniRtcEngineEventHandler *engineEventHandler) override {

    }

    OmniRtcChannel *createRtcChannel(const std::string &channelName) override {
        return nullptr;
    }

    int setChannelProfile(int profile) override {
        __android_log_print(ANDROID_LOG_INFO, kLOG_TAG, "setChannelProfile -> profile: %d", profile);
        return 0;
    }

    void setServerIp(const std::string &ip, int port) override {

    }

    int setBusinessUserRole(int role) override {
        return 0;
    }

    int setSlbAddress(const std::string &slb, const std::string &slbBackup) override {
        return 0;
    }

    int setServerLogAddress(const std::string &serverLogUrl) override {
        return 0;
    }

    int setAppExtensionInfo(const std::string &jsonInfo) override {
        return 0;
    }

    int setAudioProfile(int profile, int scenario) override {
        return 0;
    }

    int setPreferAudioCodec(int codecType, int bitrate, int channels) override {
        return 0;
    }

private:

    void reinitialize(void *context, const std::string &appId, OmniRtcEngineEventHandler *handler) override {

    }

    void logI(const char *message, ...);
};

#endif //MYCXXAPPLICATION_OMNIRTCENGINE_H
