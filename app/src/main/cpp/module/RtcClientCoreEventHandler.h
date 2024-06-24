//
// Created by ZaneWang on 2024/6/24.
//

#ifndef MYCXXAPPLICATION_RTCCLIENTCOREEVENTHANDLER_H
#define MYCXXAPPLICATION_RTCCLIENTCOREEVENTHANDLER_H

#include "TTTRtcClientCore.h"

class RtcClientCoreEventHandler : TTTRtc::IClientCoreEventHandler {

public:
    ~RtcClientCoreEventHandler() override;

    void OnUpdateConnectId(const char *szConnectId) override;

    void OnEnterRoom(const char *sRoomID, int nJoinResult, int userRole, long long int enter_start_ts_, int times_link_iploc, int times_link_gw, long long int iploc_linked_ts, long long int gw_linked_ts, long long int iploc_send_ts, long long int gw_send_ts, long long int gw_enter_ts, long long int gw_recv_proto_ts, char *gw_ip) override;

    void OnEnterTimeout(const char *sRoomID, const char *connectId, long long int enter_start_ts, int times_link_iploc, int times_link_gw, long long int iploc_linked_ts, long long int gw_linked_ts, long long int iploc_send_ts, long long int gw_send_ts, long long int gw_enter_ts, char *gwIp) override;

    void onLeaveRoom(const char *sRoomID) override;

    void OnSendDataFail(const char *mediaID, int error, int type) override;

    void OnAudioMsgLog(int type, long long int timeStamp) override;

    void OnEnterAuthed(int type) override;

    void OnRoomMemberEnter(const char *sRoomID, long long int nUserID, char *szUserInfos, int userRole, int speakStatus, bool timeStampTrusted, bool isOtherRoomUser) override;

    void OnRoomMemberExit(const char *sRoomID, long long int nUserID, int reason) override;

    void OnKickRoom(const char *sRoomID, long long int nSrcUserID, long long int nDstUserID, int nReason, const char *uuid, int nKickTime) override;

    void OnRoomChairChanged(const char *sRoomID, long long int chairid) override;

    void OnSignalReconnecting(const char *uuid) override;

    void OnSignalConnectionClosed(const char *uuid) override;

    void OnSignalDisconnected(const char *uuid) override;

    void OnSignalConnectSuccess() override;

    void OnSignalRejoin(const char *sRoomID, long long int elapsed) override;

    void OnUpdateDevParam(const char *devParam) override;

    void OnUpdateRtmpStatus(const char *sRoomID, const char *szRtmpUrl, int nStatus, int nErrCode) override;

    void OnRecvCmdMsg(const char *sRoomID, long long int nUserID, const char *msg) override;

    void OnGetMediaServerAddr(const char *aIp, const int aPort, const char *aServerId, const char *vIp, const int vPort, const char *vServerId) override;

    void OnConnectionReconnecting(const char *ip) override;

    void OnMediaReconnect(int type, char *ip) override;

    void OnUpdateUserVideoDevice(const char *sRoomID, long long int nUserID, char *szXmlData) override;

    void OnUpdateUserAudioDevice(const char *sRoomID, long long int nUserID, const char *sMediaID, const uint32_t ssrc, bool muted, int action, bool bDefault) override;

    void OnAudioLevelReport(const char *sRoomID, long long int nUserID, const char *sMediaID, int audioLevel, int audioLevelFullRange) override;

    void OnMixAudioLevelReport(const char *nRoomID, long long int nUserID, int mixAudioLevel, int mixAudioLevelFullRange) override;

    void OnUpdateMediaChannelState(int32_t mediaType, int32_t mediaState, const char *mediaServerIp, int32_t mediaPort, int32_t mediaMode) override;

    void OnRecvAudioMsg(const char *sRoomID, long long int nUserID, int streamId, const char *msg, int len) override;

    void OnRecvVideoMsg(const char *sRoomID, const char *msg) override;

    void OnRemoteStreamSubscribeAdvice(const char *sRoomID, long long int uid, const char *sMediaID, int currentStreamType, int suitableStreamType) override;

    void OnVideoEncoderBSlicedThreads(int nBSlicedThreads) override;

    void OnStartSendVideo(const char *sMediaID, bool bMute, bool bOpen) override;

    void OnStopSendVideo(const char *sMediaID, int reason) override;

    void OnStartSendAudio(const char *sRoomID, const char *sMediaID) override;

    void OnStopSendAudio(const char *sRoomID, const char *sMediaID) override;

    void OnUpdateAudioStatus(const char *sRoomID, long long int nUserID, const char *sMediaID, bool speak, uint32_t ssrc, bool localMuted) override;

    void OnRemoteAudioMuted(const char *sRoomID, long long int nUserID, const char *sMediaID, bool muted) override;

    void OnRemoteVideoMuted(const char *sRoomID, long long int nUserID, const char *sMediaID, bool muted) override;

    void OnUserRoleChanged(const char *sRoomID, long long int nUserID, int userRole) override;

    void OnFirstAudioSent() override;

    void OnFirstVideoSent(const char *sMediaID) override;

    void OnRtpRtcp(bool bClientRtpRtcp, bool bVideoRtpRtcp) override;

    void OnConnect(char *uuid, char *ip, int port) override;

    void OnConnectFail(char *uuid, char *ip, int port) override;

    void OnConnectSuccess(char *uuid, char *ip, int port) override;

    void OnReconnectTimeout() override;

    void OnNotifyLog(char *sType, char *sConnect) override;

    void OnReportEnterTimeStats(long long int startTime, int timesOfLinkIploc, int timesOfLinkGW, long long int linkIpLocTime, long long int linkGWTime, long long int sendIpLocTime, long long int sendGWTime, long long int sendEnterTime, long long int recvGWProtoTime) override;

    void OnReportFirstIFrameSent() override;

    void OnSetAudioCodecParams(int codecType, int bitrate) override;

    void OnMixerVideoCreate(const char *mediaID, const char *mediaURL) override;

    void OnMixerVideoDestroy(const char *sRoomID, const char *mediaURL) override;

    void OnConfRefreshToken(const char *sRoomID, const char *token, int code, int remain, int mask) override;

    void OnSetSEI(const char *SEI) override;

    void OnUpdateReportConfig(bool reportData, bool reportEvent, int interval) override;

    void OnGroupSessionID(const char *sRoomID, const char *sessionID) override;

    void OnReceiveLyric(const char *sRoomID, long long int nUserID, const char *lyric) override;

    void OnRemoteAudioFirstFrame(const char *sRoomID, long long int nUserID, const char *sMediaID) override;

    void OnVideoBufferingStateChanged(const char *sRoomID, long long int nUserID, const char *sMediaID, bool stat, int cartonMs, long long int ts, long long int ntp_ts, uint16_t firstSeq, uint16_t lastSeq, int frameJumpCount, int frameArraySize) override;

    void onAudioFrozenStatReport(const char *sRoomID, long long int nUserID, const char *sMediaID, bool stat, int cartonMs, long long int ts) override;

    void OnCheckNetQuality(int quality, int rttAvg, int dropNum) override;

    void OnMediaDeviceRefresh(const char *name, int deviceType, int state) override;

    void OnVideoDeviceErr(const char *deviceName, int error, const char *deviceId) override;

    void OnReportLogEvent(long long int tick) override;

    void OnMutedRemoteAudio(const char *sRoomID, long long int uid, const char *sMediaID, bool mute) override;

    void OnMutedRemoteVideo(const char *sRoomID, long long int uid, const char *sMediaID, bool mute) override;

    void OnStartCaptureState(long long int uid, const char *sMediaID, int error) override;

    void OnNetQuality(int32_t rtt_avg, int32_t packet_loss_percent, int32_t quality) override;

    void OnAudioUpstreamStatus(const char *sRoomID, long long int nUserID, int status) override;

    void OnGetMediaChannelState(int32_t mediaType, int32_t mediaState, const char *mediaServerIp, int32_t mediaPort, int32_t serverMode) override;

    void onCaptureVideoFrameEvent() override;

    void onFirstRemoteAudioFrameDecoded(const char *sRoomID, long long int userId, const char *sMediaID) override;

    void onLogReport(int level, const char *msg) override;

    void onVideoEncStuckEvent(const char *sMediaID, bool bIsdual, bool isStuck, long long int stuckDur, long long int ts) override;

    void onAudioSubscribeStateChange(const char *sRoomID, long long int uid, const char *sMediaID, int oldState, int newState, int elapseSinceLastState) override;

    void onVideoSubscribeStateChange(const char *sRoomID, long long int uid, const char *mediaID, int oldState, int newState, int elapseSinceLastState) override;

    void onAudioPublishStateChange(const char *sRoomID, const char *sMediaID, int oldState, int newState, int elapseSinceLastState) override;

    void onVideoPublishStateChange(const char *sRoomID, const char *mediaID, int oldState, int newState, int elapseSinceLastState) override;

    void onLocalVideoStateChanged(const char *sRoomID, const char *sMediaID, bool bAdd) override;

    void onLocalAudioStateChanged(const char *sRoomID, bool bAdd) override;

    void OnConnectServerResult(int result, const char *connectId, const char *gwIp, int gwPort, const char *sRoomID) override;

    void OnSetVideoEncoderType(int encoderType, const char *wzLicense, int svcLayerNum) override;

    void OnSysPolicy(const char *jsonStr) override;

    void OnMediaRelayStateChanged(const char *relayId, const char *sRoomID, int state, int code) override;

    void OnMediaRelayEvent(const char *relayId, const char *sRoomID, int event) override;

    void OnMediaRelayModeUpdate(const int relayMode) override;

    void OnSetVideoEncoderIPration(float IPration) override;

    void OnSetVideoEncoderbitRateDiscount(float bitRateDiscount) override;

    void OnSetVideoEncoderGopSpan(int gopSpan) override;
};


#endif //MYCXXAPPLICATION_RTCCLIENTCOREEVENTHANDLER_H
