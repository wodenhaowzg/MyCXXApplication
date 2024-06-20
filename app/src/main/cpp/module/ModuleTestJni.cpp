//
// Created by ZaneWang on 2024/6/17.
//

#include <jni.h>
#include <android/log.h>
#include "OmniRtcEngine.h"
#include "OmniRtcChannel.h"

class LocalOmniRtcEngineEventHandler : public OmniRtcEngineEventHandler {

    void onError(int errorType) override {
        __android_log_print(ANDROID_LOG_INFO, "wzgtest", "onError type: %d", errorType);
    }

    void onConnectionLost() override {

    }

    void onReconnectServerFailed() override {

    }

    void onReconnectServerSucceed() override {

    }

    void onReportPolicy() override {

    }

    void onRtcLogReport() override {

    }

    void onLocalAudioStats(const LocalAudioStats &stats) override {

    }

    void onLocalVideoStats(const LocalVideoStats &stats) override {

    }

    void onRtcStats(const RtcStats &stats) override {

    }
};

class LocalOmniRtcChannelEventHandler : public OmniRtcChannelEventHandler {

public:
    void onJoinChannelSuccess(const std::string &channel, long uid, int elapsed) override {

    }

    void onRejoinChannelSuccess(const std::string &channel, long uid, int elapsed) override {

    }

    void onLeaveChannel(const RtcStats &stats) override {

    }

    void onClientRoleChanged(long uid, int userRole) override {

    }

    void onTokenPrivilegeWillExpire() override {

    }

    void onRequestToken() override {

    }

    void onUserKicked(long uid, int reason, int kickTime) override {

    }

    void onUserJoined(long uid, int identity, int elapsed) override {

    }

    void onUserOffline(long uid, int reason) override {

    }

    void onStreamMessage(long uid, int streamId, const std::vector<unsigned char> &data) override {

    }

    void onNetworkQuality(long uid, int txQuality, int rxQuality) override {

    }

    void onFirstLocalAudioFrame(int elapsed) override {

    }

    void onFirstRemoteAudioFrame(long uid, const std::string &mediaId, int elapsed) override {

    }

    void onAudioSubscribeStateChanged(long uid, const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) override {

    }

    void onAudioPublishStateChanged(const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) override {

    }

    void onRemoteAudioStats(const RemoteAudioStats &stats) override {

    }

    void onFirstLocalVideoFramePublished(const std::string &mediaId, int elapsed) override {

    }

    void onUserEnableVideo(long uid, const std::string &mediaId, bool enabled) override {

    }

    void onLocalVideoStateChanged(const std::string &mediaId, int state, int error) override {

    }

    void onRemoteVideoStateChanged(long uid, const std::string &mediaId, int state, int reason, int elapsed) override {

    }

    void onVideoPublishStateChanged(const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) override {

    }

    void onVideoSubscribeStateChanged(long uid, const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) override {

    }

    void onVideoBufferingStateChanged(long uid, const std::string &mediaId, int state, long timestampInMs) override {

    }

    void onRemoteVideoStats(const RemoteVideoStats &stats) override {

    }
};

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ModuleJniTest_nativeStartTest(JNIEnv *env, jobject thiz) {
    LocalOmniRtcEngineEventHandler handler;
    IOmniRtcEngine *rtcEngine = IOmniRtcEngine::create(nullptr, "sss", &handler);
//    rtcEngine->setChannelProfile(2);
//    LocalOmniRtcChannelEventHandler channelEventHandler;
//    OmniRtcChannel *channel = rtcEngine->createRtcChannel("333");
//    channel->setRtcChannelEventHandler(&channelEventHandler);
//    IOmniRtcEngine::destroy();

    OmniRtcChannel *rtcChannel = rtcEngine->createRtcChannel("111");
    OmniRtcChannel *rtcChannel2 = rtcEngine->createRtcChannel("222");
    OmniRtcChannel *rtcChannel3 = rtcEngine->createRtcChannel("333");

    rtcEngine->destroyRtcChannel("111");
    rtcEngine->destroyRtcChannel("222");
    rtcEngine->destroyRtcChannel("333");
    rtcEngine->destroyRtcChannel("444");

}