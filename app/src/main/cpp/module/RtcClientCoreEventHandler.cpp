//
// Created by ZaneWang on 2024/6/24.
//

#include "RtcClientCoreEventHandler.h"

RtcClientCoreEventHandler::~RtcClientCoreEventHandler() {

}

void RtcClientCoreEventHandler::OnUpdateConnectId(const char *szConnectId) {

}

void
RtcClientCoreEventHandler::OnEnterRoom(const char *sRoomID, int nJoinResult, int userRole, long long int enter_start_ts_, int times_link_iploc, int times_link_gw, long long int iploc_linked_ts, long long int gw_linked_ts, long long int iploc_send_ts, long long int gw_send_ts, long long int gw_enter_ts, long long int gw_recv_proto_ts, char *gw_ip) {

}

void RtcClientCoreEventHandler::OnEnterTimeout(const char *sRoomID, const char *connectId, long long int enter_start_ts, int times_link_iploc, int times_link_gw, long long int iploc_linked_ts, long long int gw_linked_ts, long long int iploc_send_ts, long long int gw_send_ts, long long int gw_enter_ts, char *gwIp) {

}

void RtcClientCoreEventHandler::onLeaveRoom(const char *sRoomID) {

}

void RtcClientCoreEventHandler::OnSendDataFail(const char *mediaID, int error, int type) {

}

void RtcClientCoreEventHandler::OnAudioMsgLog(int type, long long int timeStamp) {

}

void RtcClientCoreEventHandler::OnEnterAuthed(int type) {

}

void RtcClientCoreEventHandler::OnRoomMemberEnter(const char *sRoomID, long long int nUserID, char *szUserInfos, int userRole, int speakStatus, bool timeStampTrusted, bool isOtherRoomUser) {

}

void RtcClientCoreEventHandler::OnRoomMemberExit(const char *sRoomID, long long int nUserID, int reason) {

}

void RtcClientCoreEventHandler::OnKickRoom(const char *sRoomID, long long int nSrcUserID, long long int nDstUserID, int nReason, const char *uuid, int nKickTime) {

}

void RtcClientCoreEventHandler::OnRoomChairChanged(const char *sRoomID, long long int chairid) {

}

void RtcClientCoreEventHandler::OnSignalReconnecting(const char *uuid) {

}

void RtcClientCoreEventHandler::OnSignalConnectionClosed(const char *uuid) {

}

void RtcClientCoreEventHandler::OnSignalDisconnected(const char *uuid) {

}

void RtcClientCoreEventHandler::OnSignalConnectSuccess() {

}

void RtcClientCoreEventHandler::OnSignalRejoin(const char *sRoomID, long long int elapsed) {

}

void RtcClientCoreEventHandler::OnUpdateDevParam(const char *devParam) {

}

void RtcClientCoreEventHandler::OnUpdateRtmpStatus(const char *sRoomID, const char *szRtmpUrl, int nStatus, int nErrCode) {

}

void RtcClientCoreEventHandler::OnRecvCmdMsg(const char *sRoomID, long long int nUserID, const char *msg) {

}

void RtcClientCoreEventHandler::OnGetMediaServerAddr(const char *aIp, const int aPort, const char *aServerId, const char *vIp, const int vPort, const char *vServerId) {

}

void RtcClientCoreEventHandler::OnConnectionReconnecting(const char *ip) {

}

void RtcClientCoreEventHandler::OnMediaReconnect(int type, char *ip) {

}

void RtcClientCoreEventHandler::OnUpdateUserVideoDevice(const char *sRoomID, long long int nUserID, char *szXmlData) {

}

void RtcClientCoreEventHandler::OnUpdateUserAudioDevice(const char *sRoomID, long long int nUserID, const char *sMediaID, const uint32_t ssrc, bool muted, int action, bool bDefault) {

}

void RtcClientCoreEventHandler::OnAudioLevelReport(const char *sRoomID, long long int nUserID, const char *sMediaID, int audioLevel, int audioLevelFullRange) {

}

void RtcClientCoreEventHandler::OnMixAudioLevelReport(const char *nRoomID, long long int nUserID, int mixAudioLevel, int mixAudioLevelFullRange) {

}

void RtcClientCoreEventHandler::OnUpdateMediaChannelState(int32_t mediaType, int32_t mediaState, const char *mediaServerIp, int32_t mediaPort, int32_t mediaMode) {

}

void RtcClientCoreEventHandler::OnRecvAudioMsg(const char *sRoomID, long long int nUserID, int streamId, const char *msg, int len) {

}

void RtcClientCoreEventHandler::OnRecvVideoMsg(const char *sRoomID, const char *msg) {

}

void RtcClientCoreEventHandler::OnRemoteStreamSubscribeAdvice(const char *sRoomID, long long int uid, const char *sMediaID, int currentStreamType, int suitableStreamType) {

}

void RtcClientCoreEventHandler::OnVideoEncoderBSlicedThreads(int nBSlicedThreads) {

}

void RtcClientCoreEventHandler::OnStartSendVideo(const char *sMediaID, bool bMute, bool bOpen) {

}

void RtcClientCoreEventHandler::OnStopSendVideo(const char *sMediaID, int reason) {

}

void RtcClientCoreEventHandler::OnStartSendAudio(const char *sRoomID, const char *sMediaID) {

}

void RtcClientCoreEventHandler::OnStopSendAudio(const char *sRoomID, const char *sMediaID) {

}

void RtcClientCoreEventHandler::OnUpdateAudioStatus(const char *sRoomID, long long int nUserID, const char *sMediaID, bool speak, uint32_t ssrc, bool localMuted) {

}

void RtcClientCoreEventHandler::OnRemoteAudioMuted(const char *sRoomID, long long int nUserID, const char *sMediaID, bool muted) {

}

void RtcClientCoreEventHandler::OnRemoteVideoMuted(const char *sRoomID, long long int nUserID, const char *sMediaID, bool muted) {

}

void RtcClientCoreEventHandler::OnUserRoleChanged(const char *sRoomID, long long int nUserID, int userRole) {

}

void RtcClientCoreEventHandler::OnFirstAudioSent() {

}

void RtcClientCoreEventHandler::OnFirstVideoSent(const char *sMediaID) {

}

void RtcClientCoreEventHandler::OnRtpRtcp(bool bClientRtpRtcp, bool bVideoRtpRtcp) {

}

void RtcClientCoreEventHandler::OnConnect(char *uuid, char *ip, int port) {

}

void RtcClientCoreEventHandler::OnConnectFail(char *uuid, char *ip, int port) {

}

void RtcClientCoreEventHandler::OnConnectSuccess(char *uuid, char *ip, int port) {

}

void RtcClientCoreEventHandler::OnReconnectTimeout() {

}

void RtcClientCoreEventHandler::OnNotifyLog(char *sType, char *sConnect) {

}

void RtcClientCoreEventHandler::OnReportEnterTimeStats(long long int startTime, int timesOfLinkIploc, int timesOfLinkGW, long long int linkIpLocTime, long long int linkGWTime, long long int sendIpLocTime, long long int sendGWTime, long long int sendEnterTime, long long int recvGWProtoTime) {

}

void RtcClientCoreEventHandler::OnReportFirstIFrameSent() {

}

void RtcClientCoreEventHandler::OnSetAudioCodecParams(int codecType, int bitrate) {

}

void RtcClientCoreEventHandler::OnMixerVideoCreate(const char *mediaID, const char *mediaURL) {

}

void RtcClientCoreEventHandler::OnMixerVideoDestroy(const char *sRoomID, const char *mediaURL) {

}

void RtcClientCoreEventHandler::OnConfRefreshToken(const char *sRoomID, const char *token, int code, int remain, int mask) {

}

void RtcClientCoreEventHandler::OnSetSEI(const char *SEI) {

}

void RtcClientCoreEventHandler::OnUpdateReportConfig(bool reportData, bool reportEvent, int interval) {

}

void RtcClientCoreEventHandler::OnGroupSessionID(const char *sRoomID, const char *sessionID) {

}

void RtcClientCoreEventHandler::OnReceiveLyric(const char *sRoomID, long long int nUserID, const char *lyric) {

}

void RtcClientCoreEventHandler::OnRemoteAudioFirstFrame(const char *sRoomID, long long int nUserID, const char *sMediaID) {

}

void RtcClientCoreEventHandler::OnVideoBufferingStateChanged(const char *sRoomID, long long int nUserID, const char *sMediaID, bool stat, int cartonMs, long long int ts, long long int ntp_ts, uint16_t firstSeq, uint16_t lastSeq, int frameJumpCount, int frameArraySize) {

}

void RtcClientCoreEventHandler::onAudioFrozenStatReport(const char *sRoomID, long long int nUserID, const char *sMediaID, bool stat, int cartonMs, long long int ts) {

}

void RtcClientCoreEventHandler::OnCheckNetQuality(int quality, int rttAvg, int dropNum) {

}

void RtcClientCoreEventHandler::OnMediaDeviceRefresh(const char *name, int deviceType, int state) {

}

void RtcClientCoreEventHandler::OnVideoDeviceErr(const char *deviceName, int error, const char *deviceId) {

}

void RtcClientCoreEventHandler::OnReportLogEvent(long long int tick) {

}

void RtcClientCoreEventHandler::OnMutedRemoteAudio(const char *sRoomID, long long int uid, const char *sMediaID, bool mute) {

}

void RtcClientCoreEventHandler::OnMutedRemoteVideo(const char *sRoomID, long long int uid, const char *sMediaID, bool mute) {

}

void RtcClientCoreEventHandler::OnStartCaptureState(long long int uid, const char *sMediaID, int error) {

}

void RtcClientCoreEventHandler::OnNetQuality(int32_t rtt_avg, int32_t packet_loss_percent, int32_t quality) {

}

void RtcClientCoreEventHandler::OnAudioUpstreamStatus(const char *sRoomID, long long int nUserID, int status) {

}

void RtcClientCoreEventHandler::OnGetMediaChannelState(int32_t mediaType, int32_t mediaState, const char *mediaServerIp, int32_t mediaPort, int32_t serverMode) {

}

void RtcClientCoreEventHandler::onCaptureVideoFrameEvent() {

}

void RtcClientCoreEventHandler::onFirstRemoteAudioFrameDecoded(const char *sRoomID, long long int userId, const char *sMediaID) {

}

void RtcClientCoreEventHandler::onLogReport(int level, const char *msg) {

}

void RtcClientCoreEventHandler::onVideoEncStuckEvent(const char *sMediaID, bool bIsdual, bool isStuck, long long int stuckDur, long long int ts) {

}

void RtcClientCoreEventHandler::onAudioSubscribeStateChange(const char *sRoomID, long long int uid, const char *sMediaID, int oldState, int newState, int elapseSinceLastState) {

}

void RtcClientCoreEventHandler::onVideoSubscribeStateChange(const char *sRoomID, long long int uid, const char *mediaID, int oldState, int newState, int elapseSinceLastState) {

}

void RtcClientCoreEventHandler::onAudioPublishStateChange(const char *sRoomID, const char *sMediaID, int oldState, int newState, int elapseSinceLastState) {

}

void RtcClientCoreEventHandler::onVideoPublishStateChange(const char *sRoomID, const char *mediaID, int oldState, int newState, int elapseSinceLastState) {

}

void RtcClientCoreEventHandler::onLocalVideoStateChanged(const char *sRoomID, const char *sMediaID, bool bAdd) {

}

void RtcClientCoreEventHandler::onLocalAudioStateChanged(const char *sRoomID, bool bAdd) {

}

void RtcClientCoreEventHandler::OnConnectServerResult(int result, const char *connectId, const char *gwIp, int gwPort, const char *sRoomID) {

}

void RtcClientCoreEventHandler::OnSetVideoEncoderType(int encoderType, const char *wzLicense, int svcLayerNum) {

}

void RtcClientCoreEventHandler::OnSysPolicy(const char *jsonStr) {

}

void RtcClientCoreEventHandler::OnMediaRelayStateChanged(const char *relayId, const char *sRoomID, int state, int code) {

}

void RtcClientCoreEventHandler::OnMediaRelayEvent(const char *relayId, const char *sRoomID, int event) {

}

void RtcClientCoreEventHandler::OnMediaRelayModeUpdate(const int relayMode) {

}

void RtcClientCoreEventHandler::OnSetVideoEncoderIPration(float IPration) {

}

void RtcClientCoreEventHandler::OnSetVideoEncoderbitRateDiscount(float bitRateDiscount) {

}

void RtcClientCoreEventHandler::OnSetVideoEncoderGopSpan(int gopSpan) {

}
