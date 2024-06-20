//
// Created by ZaneWang on 2024/6/19.
//

#ifndef MYCXXAPPLICATION_OMNIRTCCHANNEL_H
#define MYCXXAPPLICATION_OMNIRTCCHANNEL_H

#include "IOmniRtcChannel.h"

class OmniRtcChannel : IOmniRtcChannel {

private:
    OmniRtcChannelEventHandler *m_handler;

public:
    OmniRtcChannel() {
    }

    ~OmniRtcChannel() {
    };

    void setRtcChannelEventHandler(OmniRtcChannelEventHandler *eventHandler) override;

    OmniRtcChannelEventHandler *getEventHandler() const override;

    int setClientRole(int role) override;

    int joinChannel(const char *token, long uid, const ChannelMediaOptions &options) override;

    int leaveChannel() override;

    int renewToken(const char *token) override;

    int createDataStream(bool reliable, bool ordered) override;

    int sendStreamMessage(int streamId, const std::vector<unsigned char> &message) override;

    const char *getChannelSessionId() const override;

    int setDefaultMuteAllRemoteAudioStreams(bool muted) override;

    int muteLocalAudioStream(const char *mediaId, bool muted) override;

    int muteRemoteAudioStream(long uid, const char *mediaId, bool muted) override;

    int muteAllRemoteAudioStreams(bool muted) override;

    int setDefaultMuteAllRemoteVideoStreams(bool muted) override;

    int muteLocalVideoStream(const char *mediaId, bool muted) override;

    int muteRemoteVideoStream(long uid, const char *mediaId, bool muted) override;

    int muteAllRemoteVideoStreams(bool muted) override;
};

#endif //MYCXXAPPLICATION_OMNIRTCCHANNEL_H