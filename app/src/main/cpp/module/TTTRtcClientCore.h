#ifndef __TTT_RTC_CLIENTCORE_H__
#define __TTT_RTC_CLIENTCORE_H__

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#include "TTTRtcExternalVideo.h"
#include "TTTRtcExternalAudio.h"

// #define TEST_CODE_FOR_ANALYZE // 2023/1/7 wangzhiwei12 - 用于分析线上卡死问题 - 未来TODO：回收废弃该代码

#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32)
#if defined(CLIENTCORE_SHARED) // 以动态库使用
#if defined(CLIENTCORE_EXPORT) // 设置导出标识， callee 编译时设置 RTCAUDIO_EXPORT 以使用 dllexport， caller 不需特别设置使用 dllimport
#define CLIENTCORE_API __declspec(dllexport)
#define CLIENTCORE_CAPI extern "C" __declspec(dllexport)
#else
#define CLIENTCORE_API __declspec(dllimport)
#define CLIENTCORE_CAPI extern "C" __declspec(dllimport)
#endif
#else  // 以静态库使用，静态库所有符号都是可以被直接链接的，不需要特别修饰
#define CLIENTCORE_API
#define CLIENTCORE_CAPI
#endif
#define CLIENTCORE_CALL __cdecl
#elif defined(__APPLE__)
#define CLIENTCORE_API __attribute__((visibility("default")))
#define CLIENTCORE_CAPI __attribute__((visibility("default"))) extern "C"
#define CLIENTCORE_CALL
#elif defined(__ANDROID__) || defined(__linux__)
// linux 默认导出所有符号
// 只有在编译时对 gcc 使用 -fvisibility=hidden 参数关掉默认导出全部符号的特性
// 下面这两行指明使用 RTCAUDIO_API/RTCAUDIO_CAPI 修改的符号是导出的，不受 -fvisibility=hidden 影响
#define CLIENTCORE_API __attribute__((visibility("default")))
#define CLIENTCORE_CAPI extern "C" __attribute__((visibility("default")))
#define CLIENTCORE_CALL
#else // 其它平台，避免符号为定义错误
#define CLIENTCORE_API
#define CLIENTCORE_CAPI extern "C"
#define CLIENTCORE_CALL
#endif

namespace TTTRtc {
	typedef struct {
		/* bytes -- accumulated */
		uint32_t txBytes;

		/* bytes -- accumulated */
		uint32_t rxBytes;

		/* kbps -- instantaneous value */
		uint16_t rxAudioKBitRate;

		/* kbps -- instantaneous value */
		uint16_t txAudioKBitRate;

		/* kbps -- instantaneous value */
		uint16_t rxVideoKBitRate;

		/* kbps -- instantaneous value */
		uint16_t txVideoKBitRate;
	} CoreStats;

	typedef struct MediaRelayInfo {
		const char* sRoomId; // 房间ID字符串,不能为 nullptr/NULL
		const char* sToken; // Token，不能为 nullptr/NULL
		long long Uid; // 用户ID
	} MediaRelayInfo;

	class IClientCoreEventHandler
	{
	public:
		virtual ~IClientCoreEventHandler() {}
		// = OnConnectIdReport
		virtual void OnUpdateConnectId(const char* szConnectId) = 0; // connectId from SignalModule
		virtual void OnEnterRoom(const char* sRoomID, int nJoinResult, int userRole, long long enter_start_ts_, int times_link_iploc,
			int times_link_gw, long long iploc_linked_ts, long long gw_linked_ts, long long iploc_send_ts, long long gw_send_ts,
			long long gw_enter_ts, long long gw_recv_proto_ts, char* gw_ip) = 0;
		virtual void OnEnterTimeout(const char* sRoomID, const char* connectId, long long enter_start_ts, int times_link_iploc, int times_link_gw,
			long long iploc_linked_ts, long long gw_linked_ts, long long iploc_send_ts, long long gw_send_ts,
			long long gw_enter_ts, char* gwIp) = 0;
		virtual void onLeaveRoom(const char* sRoomID) = 0;
		virtual void OnSendDataFail(const char* mediaID, int error, int type) = 0;
		virtual void OnAudioMsgLog(int type, long long timeStamp) = 0;
		virtual void OnEnterAuthed(int type) = 0;
		virtual void OnRoomMemberEnter(const char* sRoomID, long long nUserID, char* szUserInfos, int userRole, int speakStatus, bool timeStampTrusted, bool isOtherRoomUser) = 0;
		virtual void OnRoomMemberExit(const char* sRoomID, long long nUserID, int reason) = 0;
		virtual void OnKickRoom(const char* sRoomID, long long nSrcUserID, long long nDstUserID, int nReason, const char *uuid, int nKickTime) = 0;
		//virtual void OnGrantPermission(long long userid, int type, int status) = 0;
		virtual void OnRoomChairChanged(const char* sRoomID, long long chairid) = 0;
		virtual void OnSignalReconnecting(const char* uuid) = 0;
		virtual void OnSignalConnectionClosed(const char* uuid) = 0;
		virtual void OnSignalDisconnected(const char* uuid) = 0;
		virtual void OnSignalConnectSuccess() = 0;
		// android: OnRejoin
		virtual void OnSignalRejoin(const char* sRoomID, long long elapsed) = 0;
		virtual void OnUpdateDevParam(const char* devParam) = 0;
		virtual void OnUpdateRtmpStatus(const char* sRoomID, const char* szRtmpUrl, int nStatus, int nErrCode) = 0;
		virtual void OnRecvCmdMsg(const char* sRoomID, long long nUserID, const char* msg) = 0;
		virtual void OnGetMediaServerAddr(const char* aIp, const int aPort, const char* aServerId, const char* vIp, const int vPort, const char* vServerId) = 0;
		virtual void OnConnectionReconnecting(const char* ip) = 0;
		virtual void OnMediaReconnect(int type, char* ip) = 0;
		virtual void OnUpdateUserVideoDevice(const char* sRoomID, long long nUserID, char* szXmlData) = 0;
		virtual void OnUpdateUserAudioDevice(const char* sRoomID, long long nUserID, const char* sMediaID, const uint32_t ssrc, bool muted, int action, bool bDefault) = 0;
		virtual void OnAudioLevelReport(const char* sRoomID, long long nUserID, const char* sMediaID, int audioLevel, int audioLevelFullRange) = 0;
		virtual void OnMixAudioLevelReport(const char *nRoomID, long long nUserID, int mixAudioLevel, int mixAudioLevelFullRange) = 0;
		virtual void OnUpdateMediaChannelState(int32_t mediaType, int32_t mediaState, const char *mediaServerIp, int32_t mediaPort, int32_t mediaMode) = 0;
		virtual void OnRecvAudioMsg(const char* sRoomID, long long nUserID, int streamId,  const char* msg, int len ) = 0;
		virtual void OnRecvVideoMsg(const char* sRoomID, const char* msg) = 0;
		virtual void OnRemoteStreamSubscribeAdvice(const char* sRoomID, long long uid, const char* sMediaID, int currentStreamType, int suitableStreamType) = 0;
		virtual void OnVideoEncoderBSlicedThreads(int nBSlicedThreads) = 0;
		virtual void OnStartSendVideo(const char* sMediaID, bool bMute, bool bOpen) = 0;
		virtual void OnStopSendVideo(const char* sMediaID, int reason) = 0;
		virtual void OnStartSendAudio(const char* sRoomID, const char* sMediaID) = 0;
		virtual void OnStopSendAudio(const char* sRoomID, const char* sMediaID) = 0;
		virtual void OnUpdateAudioStatus(const char* sRoomID, long long nUserID, const char* sMediaID, bool speak, uint32_t ssrc, bool localMuted) = 0;
		virtual void OnRemoteAudioMuted(const char* sRoomID, long long nUserID, const char* sMediaID, bool muted) = 0;
		virtual void OnRemoteVideoMuted(const char* sRoomID, long long nUserID, const char* sMediaID, bool muted) = 0;
		virtual void OnUserRoleChanged(const char* sRoomID, long long nUserID, int userRole) = 0;
		virtual void OnFirstAudioSent() = 0;
		virtual void OnFirstVideoSent(const char* sMediaID) = 0;
		virtual void OnRtpRtcp(bool bClientRtpRtcp, bool bVideoRtpRtcp) = 0;
		virtual void OnConnect(char * uuid, char * ip, int port) = 0;
		virtual void OnConnectFail(char * uuid, char * ip, int port) = 0;
		virtual void OnConnectSuccess(char * uuid, char * ip, int port) = 0;
		virtual void OnReconnectTimeout() = 0;
		virtual void OnNotifyLog(char* sType, char* sConnect) = 0;
		virtual void OnReportEnterTimeStats(long long startTime, int timesOfLinkIploc, int timesOfLinkGW, long long linkIpLocTime, long long linkGWTime, long long sendIpLocTime, long long sendGWTime, long long sendEnterTime, long long recvGWProtoTime) = 0;
		virtual void OnReportFirstIFrameSent() = 0;
		virtual void OnSetAudioCodecParams(int codecType, int bitrate) = 0;
		virtual void OnMixerVideoCreate(const char* mediaID, const char* mediaURL) = 0;
		virtual void OnMixerVideoDestroy(const char* sRoomID, const char* mediaURL) = 0;
		virtual void OnConfRefreshToken(const char* sRoomID, const char* token, int code, int remain, int mask) = 0;
		virtual void OnSetSEI(const char* SEI) = 0;
		virtual void OnUpdateReportConfig(bool reportData, bool reportEvent, int interval) = 0;
		// android: OnGlobalSessionId
		virtual void OnGroupSessionID(const char* sRoomID, const char* sessionID) = 0;
		virtual void OnReceiveLyric(const char* sRoomID, long long nUserID, const char* lyric) = 0;
		virtual void OnRemoteAudioFirstFrame(const char* sRoomID, long long nUserID, const char* sMediaID) = 0;
		virtual void OnVideoBufferingStateChanged(const char* sRoomID, long long nUserID, const char* sMediaID, bool stat, int cartonMs, long long ts, long long ntp_ts, uint16_t firstSeq, uint16_t lastSeq, int frameJumpCount, int frameArraySize) = 0;
		virtual void onAudioFrozenStatReport(const char* sRoomID, long long nUserID, const char* sMediaID, bool stat, int cartonMs, long long ts) = 0;
		virtual void OnCheckNetQuality(int quality, int rttAvg, int dropNum) = 0;
		virtual void OnMediaDeviceRefresh(const char* name, int deviceType, int state) = 0;
		virtual void OnVideoDeviceErr(const char* deviceName, int error, const char* deviceId) = 0;
		virtual void OnReportLogEvent(long long tick) = 0;
		virtual void OnMutedRemoteAudio(const char* sRoomID, long long uid, const char* sMediaID, bool mute) = 0;
		virtual void OnMutedRemoteVideo(const char* sRoomID, long long uid, const char* sMediaID, bool mute) = 0;
		virtual void OnStartCaptureState(long long uid, const char* sMediaID, int error) = 0;
		// android: OnNetQuality
		virtual void OnNetQuality(int32_t rtt_avg, int32_t packet_loss_percent, int32_t quality) = 0;
		virtual void OnAudioUpstreamStatus(const char* sRoomID, long long nUserID, int status) = 0;
		virtual void OnGetMediaChannelState(int32_t mediaType, int32_t mediaState, const char* mediaServerIp, int32_t mediaPort, int32_t serverMode) = 0;
		// android: OnReportImageFireEvent
		virtual void onCaptureVideoFrameEvent() = 0;
		virtual void onFirstRemoteAudioFrameDecoded(const char* sRoomID, long long userId, const char* sMediaID) = 0;
		// android: OnNativeLog
		virtual void onLogReport(int level, const char* msg) = 0;
		virtual void onVideoEncStuckEvent(const char* sMediaID, bool bIsdual, bool isStuck, long long stuckDur, long long ts) = 0;
		// android: OnAudioSubscribeStateChanged
		virtual void onAudioSubscribeStateChange(const char* sRoomID, long long uid, const char* sMediaID, int oldState, int newState, int elapseSinceLastState) = 0;
		// android: OnVideoSubscribeStateChanged
		virtual void onVideoSubscribeStateChange(const char* sRoomID, long long uid, const char* mediaID, int oldState, int newState, int elapseSinceLastState) = 0;
		// android: OnAudioPublishStateChanged
		virtual void onAudioPublishStateChange(const char* sRoomID, const char* sMediaID, int oldState, int newState, int elapseSinceLastState) = 0;
		// android: OnVideoPublishStateChanged
		virtual void onVideoPublishStateChange(const char* sRoomID, const char* mediaID, int oldState, int newState, int elapseSinceLastState) = 0;
		virtual void onLocalVideoStateChanged(const char* sRoomID, const char* sMediaID, bool bAdd) = 0;
		virtual void onLocalAudioStateChanged(const char* sRoomID, bool bAdd) = 0;
		virtual void OnConnectServerResult(int result, const char* connectId, const char* gwIp, int gwPort, const char* sRoomID) = 0;
		virtual void OnSetVideoEncoderType(int encoderType, const char* wzLicense, int svcLayerNum) = 0;//0 H.264 1 H.265 2 wz264
		virtual void OnSysPolicy(const char* jsonStr) = 0;
		virtual void OnMediaRelayStateChanged(const char* relayId, const char* sRoomID, int state, int code) = 0;
		virtual void OnMediaRelayEvent(const char* relayId, const char* sRoomID, int event) = 0;
		virtual void OnMediaRelayModeUpdate(const int relayMode) = 0;
		virtual void OnSetVideoEncoderIPration(float IPration) = 0;
		virtual void OnSetVideoEncoderbitRateDiscount(float bitRateDiscount) = 0;
		virtual void OnSetVideoEncoderGopSpan(int gopSpan) = 0;
	};

	struct ClientCoreContext
	{
		IClientCoreEventHandler* eventHandler;
		ExternalVideoModuleDelegate* externalVideo;
		ExternalAudioModuleDelegate* externalAudio;
		char exePath[256] = { 0 };
		int logLevel;     /* 0~6  NULL/FATAL/ERROR/WARN/DEBUG/DEBUG_EXT */
		// 
		// 支持外部设置 slb、logServer
		char slbServer[256] = { 0 };
		char slbServer2[256] = { 0 };
		char logServer[256] = { 0 };
		// 
		// 支持外部设置 Image Report Api URL
		char imgReportApi[1024] = { 0 };

		ClientCoreContext()
			: eventHandler(NULL)
			, externalVideo(NULL)
			, externalAudio(NULL)
			, logLevel(1)    /* 0~6*/
		{}
	};

	class CLIENTCORE_API IClientCore
	{
	public:
		virtual ~IClientCore() {};

		static IClientCore *getInstance();
		static void release();

#if defined(TEST_CODE_FOR_ANALYZE) // 2023/1/7 wangzhiwei12
        virtual size_t GetEventQueSize(int id) = 0;
        virtual int GetEventQueLeadTaskId(int id) = 0;
        virtual int GetEventQueLastTaskId(int id) = 0;
#endif // TEST_CODE_FOR_ANALYZE

		virtual int initialize(const ClientCoreContext& context) = 0;
		virtual void setAutoReleaseSignalConn() = 0;
		
		virtual void setProductVersion(const char* szPublicVer, const char* szCommitID = "") = 0;
		virtual void setServerAddress(const char* szServerIP, int nPort) = 0;
		virtual void setSignalTimeout(unsigned int signalTimeout) = 0;

		virtual void AdjRemoteUserVolumeScale(long long nUserID, const char* sMediaID, double volumeScale) = 0;
		virtual void AdjSpeakerVolumeScale(double volumeScale) = 0;

		virtual void SetSandboxPath(const char* path) = 0;

		//virtual void enterRoom(const char *sAppID, long long nUserID, long long roomID, ROOM_USERROLE userRole,
		//	const char *sRtmpUrl, const char* sModel, const char *token, bool bSubRoom,
		//	bool isMediaRelay, long long srcChannelId) = 0;
		virtual void enterRoom(const char *sAppID, long long nUserID, const char* sRoomID, int/*ROOM_USERROLE*/ userRole,
			const char *sRtmpUrl, const char* sModel, const char *token, bool bSubRoom,
			bool isMediaRelay, const char* srcChannelId) = 0;
		virtual void exitRoom(const char* sRoomID) = 0;
		virtual void kickRoom(const char* sRoomID, long long nUserID) = 0;
		//virtual void applyForControlPermission() = 0;
		//virtual void releaseControlPermission() = 0;

		virtual void updateLocalVideoDesc(const char* videoDescXml) = 0;    //更新xml
		virtual void uploadVideo(const char* sRoomID, const char* mediaID, bool enable) = 0;    //创建视频c2s通道

		virtual void updateLocalAudioDesc() = 0;
		virtual void UpdateAudioUploadInfo() = 0;

		virtual void changeUserRole(const char* sRoomID, int userRole) = 0;
		//virtual void setRoomRequireChair(bool require) = 0;
		virtual void setSystemInfo(const char *os_ver_, const char *user_dev_info_, const char *sdk_pub_ver_) = 0;
		virtual void setAudioLevelReportInterval(int interval) = 0;
		virtual void setRoomCreateVideoMixer(bool create) = 0;
		virtual void openVideoDevice(const char* sRoomID, long long userID, const char *mediaID) = 0;
		virtual void closeVideoDevice(const char* sRoomID, long long userID, const char *mediaID) = 0;
		virtual void openMixerVideo(const char* sRoomID, const char *mediaID) = 0;
		virtual void closeMixerVideo(const char* sRoomID, const char *mediaID) = 0;

		virtual void openVideoDevice(const char* sRoomID, long long userID, int videoType) = 0;
		virtual void closeVideoDevice(const char* sRoomID, long long userID, int videoType) = 0;

		virtual void UpdateRtmpUrl(const char* sRoomID, const char* newRUL, const char* lastUrl) = 0;
		virtual void RtmpAddVideo(const char* sRoomID, long long nUserID, const char *mediaID, const char *sMixerURL) = 0;
		virtual void RtmpDelVideo(const char* sRoomID, long long nUserID, const char *mediaID, const char *sMixerURL) = 0;
		virtual void RtmpAddAudio(const char* sRoomID, long long nUserID, const char *mixerURL) = 0;
		virtual void RtmpDelAudio(const char* sRoomID, long long nUserID, const char *mixerURL) = 0;
		virtual void SetVideoMixerBackgroundImgUrl(const char* sRoomID, const char* url, const char *sMixerURL, int nX, int nY, int nW, int nH) = 0;
		virtual void setSEI(const char* sRoomID, const char *sei, const char *sei2, const char *sMixerURL) = 0;
		virtual int setVideoMixerParams(int32_t bitrate, int32_t fps, int32_t width, int32_t height, int32_t mode, int32_t gop) = 0;
		virtual int	setAudioMixerParams(int bitrate, int samplerate, int channels) = 0;
		virtual int	SetPreferAudioCodec(int audioCodec, int bitrate, int channels) = 0;
		virtual void muteLocalAudio(const char* sRoomID, const char* sMediaID, bool mute) = 0;
		virtual void muteLocalVideo(const char* sRoomID, const char* sMedidID, bool mute) = 0;

		virtual void setDefaultMuteAllRemoteAudio(const char* sRoomID, bool mute) = 0;
		virtual void muteAllRemoteAudio(bool mute, const char* sRoomID) = 0;
		virtual void MuteAllRoomRemoteVideo(bool mute) = 0;
		virtual void muteAllRemoteVideo(const char* sRoomID, bool mute) = 0;
		virtual void muteRemoteAudio(const char* sRoomID, long long nUserID, const char* sMediaID, bool mute) = 0;
		virtual void enableDualStream(bool enabled) = 0;
		virtual void setRemoteSubscribeFallbackOption(int option) = 0;
		virtual void setRemoteUserPriority(long long nUserID, int priority) = 0;
		virtual void setRemoteVideoStreamType(long long nUserID, const char* sMediaID, int streamType) = 0;

		virtual int64_t getVideoTotalSendBytes() = 0;
		virtual int64_t getVideoTotalRecvBytes() = 0;
		virtual int64_t getAudioTotalSendBytes() = 0;
		virtual int64_t getAudioTotalRecvBytes() = 0;
		virtual int64_t getEncodeDataSize() = 0;
		virtual int getRecvDataErrorTimes() =0;
		virtual void getRtcStat(CoreStats& stat, const char* sRoomID) = 0;
		virtual int getAudioUserErrorTimes() = 0;
		virtual long long getAudioMaxErrorUserid() = 0;
		virtual int getAudioRecvDataErrorTimes() =0;

		__attribute__((deprecated("This function is deprecated, please use ExternalAudioModule::isAllRemoteMuted() instead")))
		virtual int isAllRemoteAudioMuted() = 0;
		virtual int getRemoteAudioDelay(long long userID, const char* sMediaID) = 0;

		virtual VideoStatistics* getVideoStatistics2(int &count) = 0;
		virtual LocalVideoStatistics* getLocalVideoStatistics2(int &count) = 0;
		virtual int getBufferDuration(const char *mediaID) = 0;
		//virtual int getFlowCtrlBytes() = 0;
		virtual int getlastGwToUeID() = 0;
		virtual int getSignalReconnectTimes() = 0;
		virtual int getLastUeToGwID() = 0;
		virtual int getDynamicBitrate(const char *mediaID) = 0;

		//add by liy 20190101
		virtual int setHighQualityAudioParameters(bool enable) = 0;
		virtual void reportLogMsg(const char *msg, const char* appId) = 0;
		// LocalVideoStatechange Event回调 触发机制
		virtual void UpdateLocVideoDevid(const char* sRoomID, const char *sDstDevID, bool bAdd) = 0;
		virtual void UpdateLocAudioDevice(const char* sRoomID, bool bAdd) = 0;
		virtual void SetUUID(const char* uuid) = 0;
		virtual void UpdateRemoteDefaultVideoDevid(const char *sDstDevID, bool bAdd) = 0;
		//virtual void addPublishStreamUrl(const char* sMediaURL) = 0;
		virtual void addPublishStreamUrl(const char* sRoomID, const char* sMediaURL, bool bAudioOnly) = 0;
		virtual void delPublishStreamUrl(const char* sRoomID, const char* sMediaURL) = 0;
		virtual int renewToken(const char* sRoomID, const char *token) = 0;
		//virtual int SetToken(const char * token) = 0;

		virtual void SendCmdMsg(const char* sRoomID, long long nUserID, const char* sMsg) = 0;
		virtual void SendCustomizedVideoMsg(const char* sRoomID, const char* msg) = 0;
		virtual void SendCustomizedAudioMsg(const char* sRoomID, int streamID, const char* msg, int len) = 0;
		virtual void sendLyric(const char* sRoomID, const char* lyric) = 0;

		virtual void StartCheckNet(const char *appId, const char *connectId) = 0;
		virtual void StopCheckNet() = 0;
		virtual void notifyMediaDeviceChange(const char* deviceId, int deviceType, int state) = 0;
        virtual void notifyVideoDeviceError(const char* deviceName, int error, const char* deviceId) = 0;

		virtual int enableContentInspect(bool enable, int timeInterval) = 0;
		virtual int contentInspectExtra(const char* arg, int rate_array[], int array_cnt) = 0;
		virtual void reportLocalVideoFrameData(const char* data, int datalen) = 0;
		virtual void UpdateNetworkType(int type) = 0;
		virtual void SetVideoStuckIgnore(bool ignore) = 0;
		virtual void SetSlbAddress(const char* slb, const char* slbBackup) = 0;
		virtual void SetImageReportUrl(const char* url) = 0;
		virtual int setBusinessUserRole(int role) = 0;
		virtual int startMediaRelay(const char* relayId, const MediaRelayInfo* srcInfo, const int dstCount, const MediaRelayInfo* dstInfos) = 0;
		virtual int updateMediaRelay(const char* relayId, const MediaRelayInfo* srcInfo, const int dstCount, const MediaRelayInfo* dstInfos) = 0;
		virtual int pauseMediaRelay(const char* relayId) = 0;
		virtual int resumeMediaRelay(const char* relayId) = 0;
		virtual int stopMediaRelay(const char* relayId) = 0;
		virtual void makeLog(int logLevel, const char* logMsg) = 0;
		virtual int setAVSyncSource(const char* sRoomId, long long userId) = 0;
		virtual int setAppExtensionInfo(const char* jsonAppExtInfo) = 0;
	};
}

#endif
