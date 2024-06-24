/**
 *  TTTRtcExternalAudio.h
 *  ClientCore
 *
 *  Created by apple on 16/6/23.
 *  Copyright © 2016年 rd. All rights reserved.
 */

#ifndef __EXTERNAL_AUDIO_MODULE_H__
#define __EXTERNAL_AUDIO_MODULE_H__

#include <stdint.h>

typedef enum AudioCodecType
{
    AudioCodec_ISAC_WB = 103,
    AudioCodec_ISAC_UWB = 104,
    AudioCodec_OPUS = 120,
    AudioCodec_AAC = 121,
    AudioCodec_HEAAC = 122,
    AudioCodec_OPUS_124 = 124,
} AudioCodecType;

// 
typedef enum _EAudioMediaStat
{
    E_AMS_IDLE = 0, // 链路已关闭
    E_AMS_CONNECTING = 1, // 连接中
    E_AMS_CONNECTED = 2, // 已连接
    E_AMS_CONNECT_FAILED = 3, // 连接失败
    E_AMS_CLOSE = 4 // 正在执行关闭链路
}EAudioMediaStat;

// 媒体链路服务器相关地址信息
typedef struct _AudioMediaServerInfo
{
    char msIp[20];
    int msPort;
    int msIOType;
    char msId[128];
    EAudioMediaStat msState; // 链接状态
}AudioMediaServerInfo;

class ExternalAudioModule;
class ExternalRtmpPushAudioModule;
/**
 * 外置音频模块代理，由sdk调用方实现，用于混音的实现
 */
class ExternalAudioPcmModuleDelegate
{
public:
    virtual void setExternalRtmpPushModule(ExternalRtmpPushAudioModule* pModule) = 0;
};
/**
 * 外置音频模块代理，由sdk调用方实现，用于混音的实现
 */
class ExternalAudioModuleDelegate
{
public:

    virtual int getNumOfAudioDevices(void) = 0;
    virtual int getAudioDeviceName(unsigned int index, char *mediaID, const int maxMediaIDLength, uint32_t &ssrc, int &mute) = 0;
    virtual bool getDefaultAudioDevice(char *mediaID, const int maxMediaIDLength) = 0;
    /**
     *  开始音频采集并编码，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool startSend(const char* roomId, const char* mediaId) = 0;

    /**
     *  停止音频采集并编码，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool stopSend(const char* roomId, const char* mediaId) = 0;

    /**
     *  开始播放音频，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool startPlay(const char* roomId, const long long &userId, const char* mediaId, const uint32_t ssrc) = 0;

    /**
     *  停止播放音频，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool stopPlay(const char* roomId, const long long &userId, const char* mediaId) = 0;

    /**
     *  接收音频数据，供解码播放使用，由sdk内部调用
     *
     *  @param data      音频数据
     *  @param len       音频数据长度
     */
    virtual bool receiveAudioData(const char* roomId, const long long &userId, const char* mediaId, const uint32_t &ssrc, const uint32_t &landSsrc, void* data, int len) = 0;
    virtual int recvRTCPMessage(const unsigned char* incomingRtcpPacket, unsigned int packetLength, const char* roomId, long long userId, uint32_t ssrc) =0;
    virtual void setExternalModule(ExternalAudioModule* pModule) = 0;
    virtual void setExternalRtmpPushModule(ExternalRtmpPushAudioModule* pModule) = 0;
    /**
     *  接收自定义音频消息
     *
     *  @param msg       自定义音频消息
     */
    //virtual void receiveCustomizedAudioMsg(const char* msg) = 0;

    virtual void setSendCodec(int codecType, int bitrate, int channel, bool inbandfec) = 0;
    virtual void setAudioProfileParams(int profile, int audioProcessSampleRate) = 0;
    virtual void setConfig(const char* key, const char* config) = 0;

    __attribute__((deprecated("This function is deprecated, No-calls")))
    virtual int getDelay(long long userId, const char* mediaId, uint32_t& estimateDelay, uint32_t& jitterMs, uint32_t& baseDelay) = 0;
    virtual unsigned int getDelayEstimate(long long userId, const char* mediaId) = 0;
    __attribute__((deprecated("This function is deprecated, No-calls")))
    virtual unsigned int getPlayoutTimestamp(long long userId, const char* mediaId) = 0;
    virtual bool setSleepMS(long long userId, const char* mediaId, unsigned int ts) = 0;

    // 2024/06/14: 接口通用目的 - 扩展参数 level, preLevel, afterLevel, mixLevel
    virtual int getSpeechInputAudioLevel(const char* mediaId, int* level, int* preLevel, int* afterLevel, int* mixLevel) = 0;
    // 2024/06/14: 接口通用目的 - 扩展参数 levelFullRange, preLevelFullRange, afterLevelFullRange, mixLevelFullRange
    virtual int getSpeechInputAudioLevelFullRange(const char* mediaId, int* levelFullRange, int* preLevelFullRange, int* afterLevelFullRange,int* mixLevelFullRange) = 0;
    virtual int getSpeechOutputAudioLevel(long long userId, const char* mediaId) = 0;
    virtual int getSpeechOutputAudioLevelFullRange(long long userId, const char* mediaId) = 0;

    virtual void muteLocal(bool mute, const char* mediaId) = 0;
    virtual bool isLocalMuted(const char* mediaId) = 0;
    // 2024/06/14: 接口通用目的 - 扩展参数 roomId
    virtual void muteRemote(bool mute, const char* roomId, long long userId, const char* mediaId) = 0;
    // 远端已静音
    // rename: from RemoteAudioMuted --> remoteAudioMuted
    virtual void remoteAudioMuted(bool muted, long long userId, const char* mediaId) = 0;
    virtual void adjRemoteUserVolumeScale(long long userId, const char *mediaId, float volumeScale) = 0;
    // 2024/06/14: 接口通用目的 - 注：目前 android实现流程如下：
    // App --> RoomJni --> call-clientcore --> call-ExternalAudioModule --> call-ExternalAudioModuleImpl
    virtual void adjSpeakerVolumeScale(float volumeScale) = 0;
    // 2024/06/14: 接口通用目的 - 注：目前 android 未用到该接口｜Android 是 Java 层直接调用的设备
    virtual void replayUsingVoip(bool useVoip) = 0;
    // rename: from SetMicVolume --> setMicVolume
    // 现状：setMicVolume 无调用者
    __attribute__((deprecated("This function is deprecated, No-calls")))
    virtual int setMicVolume(unsigned int volume, const char* mediaId) = 0;
    // rename: from SetBitrate --> setBitrate
    virtual void setBitrate(unsigned int sendBps) = 0;
    virtual void updateBandWidthState(bool state, int brandwidth) = 0;
    // deprecated 2020.09.30 zhjb
    __attribute__((deprecated("This function is deprecated, No-calls")))
    virtual void setCutTs(bool cutts) = 0;

    // 2024/06/17 接口统一：ohos
    virtual void onVideoPlayed(long long userid) = 0;
    virtual void onVideoClosed(long long userid) = 0;
	virtual void setAudioEngineMode(int mode) = 0;

    virtual void startDump(int duration) = 0;
    virtual void stopDump() = 0;

    virtual int getSpeechVADState(long long userId, const char* mediaId) = 0;
    virtual void recvRemoteAudioLevelInfo(long long userId, const char* mediaId, int level, int levelFullrange, int vad, int interval) = 0;
    virtual void onUserAudioMixPolicy(unsigned int mode, unsigned int maxnum, float increase, float decrease, int switchInterval) = 0;

    // end
    virtual void Terminate() = 0;
};

/**
 *  音频模块接口
 */
class ExternalAudioModule
{
public:
    /**
     *  获取接口对象，singleton
     *
     *  @return 接口对象
     */
    static ExternalAudioModule* sharedInstance();
    virtual ~ExternalAudioModule() {};

    /**
     *  设置外置音频模块代理
     *
     *  @param delegate 由sdk调用方实现的ExternalAudioModuleDelegate
     */
    virtual void setExternalAudioModuleDelegate(ExternalAudioModuleDelegate* pDelegate) = 0;

    /**
     *  获取当前播放的音频时间戳，用于进行音视频同步
     *
     *  @return 音频时间戳
     */
    virtual long long getAudioTimestamp(long long userId) = 0;

    /**
     * 获取发送音频数据的总字节数
     *
     * @return 字节数
     */
    virtual long long getTotalSendBytes() = 0;

    /**
     * 获取接收音频数据的总字节数
     *
     * @return 字节数
     */
    virtual long long getTotalRecvBytes() = 0;

    virtual int  getRecvBytes(const char* roomId, int64_t& rxBytes, int64_t& lastRx) = 0;

    /**
     * 获取音频编码帧率
     *
     * @return 编码帧率
     */
    virtual int64_t getEncodeFps() = 0;

    virtual int64_t getEncodeDataSize() = 0;

    /**
     * 获取缓冲区数据大小,单位ms
     *
     * @return 毫秒数
     */
    virtual int getBufferDuration() = 0;

    //virtual int getRTT() = 0;
    
    virtual int getTotalWannaSendBytes() = 0;
    
    virtual int getDelayMs(long long userId, const char* mediaId) = 0;

    virtual void updateRemoteLandSsrc(const char* roomId, const char* mediaId, long long userId, uint32_t ssrc) = 0;

    virtual void pushEncodedAudioData(void* data, int len) = 0;
    virtual void sendNACKData(void* data, int len, long long userId)= 0;
    virtual void sendRTCPData(void* data, int len, long long userId)=0;

    virtual void sendCustomizedAudioMsg(const char* roomId, int streamId, const char* msg, int len) = 0;

    // 
    // 返回值：是否成功获取到 info
    virtual bool getMediaServerInfo(AudioMediaServerInfo& info) = 0;

    // for stats
    virtual int getUserErrorTimes() = 0;
    virtual int getDataErrorTimes() = 0;
    virtual long long getMaxErrorUserid() = 0;

    virtual void remoteAudioMuted(bool muted, long long userid, const char *mediaId) = 0;
    virtual void adjRemoteUserVolumeScale(long long userid, const char *mediaId, float volumeScale) = 0;

    // android: setFractionLost
    virtual void onUplinkFractionLost(const uint8_t fractionLost) = 0;
    virtual int GetFractionLost() = 0;
    virtual void OnFirstAudioFrameDecoded(const long long& userId, const char* mediaId) = 0;
    virtual void onAudioStuckEnd(const long long& userId, const char* mediaId, int period, const long long& ts) = 0;
    virtual void onAudioStuckBegin(const long long& userId, const char* mediaId, const long long& ts) = 0;
    
    virtual bool remoteAudioMutedByMyself(long long userId, const char* mediaId) = 0;
    virtual bool isAllRemoteMuted() = 0;
};

/**
*  音频推流模块接口
*/
class ExternalRtmpPushAudioModule
{
public:
	/**
	 *  获取接口对象，singleton
	 *
	 *  @return 接口对象
	 */
	static ExternalRtmpPushAudioModule* sharedInstance();
	/**
	 *  设置外置音频模块代理
	 *
	 *  @param delegate 由sdk调用方实现的ExternalRtmpPushAudioModuleDelegate
	 */
	virtual void setExternalRtmpPushAudioModuleDelegate(ExternalAudioPcmModuleDelegate* pDelegate) = 0;

	virtual void pushPcmAudioData(void* data, int len, long long ts, int sampleRate) = 0;
};

#endif
