//
// Created on 2024/6/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CORERTCPROJECT_MOCKOMNIRTCCHANNEL_H
#define CORERTCPROJECT_MOCKOMNIRTCCHANNEL_H

#include "IOmniRtcChannel.h"

class MockOmniRtcChannel : OmniRtcChannel {

public:
    void setRtcChannelEventHandler(OmniRtcChannelEventHandler *eventHandler) override;

    OmniRtcChannelEventHandler *getEventHandler() const override;

    int setClientRole(int role) override;

    int joinChannel(const std::string &token, long uid, const ChannelMediaOptions &options) override;

    int leaveChannel() override;

    int renewToken(const std::string &token) override;

    int createDataStream(bool reliable, bool ordered) override;

    int sendStreamMessage(int streamId, const std::vector<unsigned char> &message) override;

    std::string getChannelSessionId() const override;

    int setDefaultMuteAllRemoteAudioStreams(bool muted) override;

    int muteLocalAudioStream(const std::string &mediaId, bool muted) override;

    int muteRemoteAudioStream(long uid, const std::string &mediaId, bool muted) override;

    int muteAllRemoteAudioStreams(bool muted) override;

    int setDefaultMuteAllRemoteVideoStreams(bool muted) override;

    int muteLocalVideoStream(const std::string &mediaId, bool muted) override;

    int muteRemoteVideoStream(long uid, const std::string &mediaId, bool muted) override;

    int muteAllRemoteVideoStreams(bool muted) override;
};

#endif //CORERTCPROJECT_MOCKOMNIRTCCHANNEL_H
