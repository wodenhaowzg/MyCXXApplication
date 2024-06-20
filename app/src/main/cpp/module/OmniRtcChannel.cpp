//
// Created by ZaneWang on 2024/6/19.
//

#include "OmniRtcChannel.h"

void OmniRtcChannel::setRtcChannelEventHandler(OmniRtcChannelEventHandler *eventHandler) {
    m_handler = eventHandler;
}

OmniRtcChannelEventHandler *OmniRtcChannel::getEventHandler() const {
    return m_handler;
}

int OmniRtcChannel::setClientRole(int role) {
    return 0;
}

int OmniRtcChannel::joinChannel(const char *token, long uid, const ChannelMediaOptions &options) {
    return 0;
}

int OmniRtcChannel::leaveChannel() {
    return 0;
}

int OmniRtcChannel::renewToken(const char *token) {
    return 0;
}

int OmniRtcChannel::createDataStream(bool reliable, bool ordered) {
    return 0;
}

int OmniRtcChannel::sendStreamMessage(int streamId, const std::vector<unsigned char> &message) {
    return 0;
}

const char *OmniRtcChannel::getChannelSessionId() const {
    return "";
}

int OmniRtcChannel::setDefaultMuteAllRemoteAudioStreams(bool muted) {
    return 0;
}

int OmniRtcChannel::muteLocalAudioStream(const char *mediaId, bool muted) {
    return 0;
}

int OmniRtcChannel::muteRemoteAudioStream(long uid, const char *mediaId, bool muted) {
    return 0;
}

int OmniRtcChannel::muteAllRemoteAudioStreams(bool muted) {
    return 0;
}

int OmniRtcChannel::setDefaultMuteAllRemoteVideoStreams(bool muted) {
    return 0;
}

int OmniRtcChannel::muteLocalVideoStream(const char *mediaId, bool muted) {
    return 0;
}

int OmniRtcChannel::muteRemoteVideoStream(long uid, const char *mediaId, bool muted) {
    return 0;
}

int OmniRtcChannel::muteAllRemoteVideoStreams(bool muted) {
    return 0;
}