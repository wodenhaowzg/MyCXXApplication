//
// Created on 2024/6/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "MockOmniRtcChannel.h"
#include <jni.h>
#include <android/log.h>


void MockOmniRtcChannel::setRtcChannelEventHandler(OmniRtcChannelEventHandler *eventHandler) {

}

OmniRtcChannelEventHandler *MockOmniRtcChannel::getEventHandler() const {
    return nullptr;
}

int MockOmniRtcChannel::setClientRole(int role) {
    return 0;
}

int MockOmniRtcChannel::joinChannel(const std::string &token, long uid, const ChannelMediaOptions &options) {
    return 0;
}

int MockOmniRtcChannel::leaveChannel() {
    __android_log_print(ANDROID_LOG_INFO, "MockOmniRtcChannel", "leaveChannel invoked.");
    return 0;
}

int MockOmniRtcChannel::renewToken(const std::string &token) {
    return 0;
}

int MockOmniRtcChannel::createDataStream(bool reliable, bool ordered) {
    return 0;
}

int MockOmniRtcChannel::sendStreamMessage(int streamId, const std::vector<unsigned char> &message) {
    return 0;
}

std::string MockOmniRtcChannel::getChannelSessionId() const {
    return std::string();
}

int MockOmniRtcChannel::setDefaultMuteAllRemoteAudioStreams(bool muted) {
    return 0;
}

int MockOmniRtcChannel::muteLocalAudioStream(const std::string &mediaId, bool muted) {
    return 0;
}

int MockOmniRtcChannel::muteRemoteAudioStream(long uid, const std::string &mediaId, bool muted) {
    return 0;
}

int MockOmniRtcChannel::muteAllRemoteAudioStreams(bool muted) {
    return 0;
}

int MockOmniRtcChannel::setDefaultMuteAllRemoteVideoStreams(bool muted) {
    return 0;
}

int MockOmniRtcChannel::muteLocalVideoStream(const std::string &mediaId, bool muted) {
    return 0;
}

int MockOmniRtcChannel::muteRemoteVideoStream(long uid, const std::string &mediaId, bool muted) {
    return 0;
}

int MockOmniRtcChannel::muteAllRemoteVideoStreams(bool muted) {
    return 0;
}