//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_IOMNIRTCDEFINES_H
#define MYCXXAPPLICATION_IOMNIRTCDEFINES_H


typedef struct AudioVolumeInfo {

    /**
     * 用户所属的频道名称。
     */
    const char *channelName = "";
    /**
     * 用户ID。
     */
    long long uid;
    /**
     * 用户的音频流 ID。
     */
    const char *mediaId = "";
    /**
     * 音量值，0 ～ 255
     */
    int volume;
    int vad; // 未用到
} AudioVolumeInfo;

typedef struct LocalAudioStats {
    /**
        * 用户 ID。
        */
    long long uid;
    /**
     * 用户的音频流 ID。
     */
    const char *mediaId = "";
    /**
     * 瞬时值，发送的码率(kbps)
     */
    int sentBitrate;
    /**
     * 瞬时值，本地音频流的上行丢包率(%)
     */
    int txPacketLossRate;
    /**
     * 瞬时值，本地音频流的端到端延迟(ms)
     */
    int audioDelay;
    /**
     * 上行 rtt。
     */
    int rtt;
    /**
     * 编码帧率。
     */
    int audioEncodeFps;
    /**
     * 采样率。
     */
    int sentSampleRate;
    /**
     * 声道数。
     */
    int numChannels;
    /**
     * 音量值。
     */
    int volume;

} LocalAudioStats;

typedef struct LocalVideoStats {
/**
     * 用户 ID。
     */
    long long uid;
    /**
     * 用户的视频流 ID。
     */
    const char *mediaId = "";
    /**
     * 编码宽度
     */
    int encodedFrameWidth;
    /**
     * 编码高度
     */
    int encodedFrameHeight;
    /**
     * 瞬时值，发送的码率(kbps)
     */
    int sentBitrate;
    /**
     * 瞬时值，发送的帧率(fps)
     */
    int sentFrameRate;
    /**
     * 瞬时值，期望的视频帧率(fps)
     */
    int videoTargetFps;
    /**
     * 瞬时值，期望的视频码率(kbps)
     */
    int videoTargetBps;
    /**
     * 瞬时值，本地视频上行丢包率(%)
     */
    int txPacketLossRate;
    /**
     * 本地视频上行缓冲区大小（单位毫秒数），KCP 的时候有值。
     */
    int videoBuffer;
    /**
     * 瞬时值，本地视频上行端到端延迟(ms)
     */
    int delay;
    /**
     * 视频上行 rtt
     */
    int rtt;

} LocalVideoStats;

typedef struct RemoteAudioStats {

    /**
     * 用户所属的频道名称。
     */
    const char *channelName;
    /**
     * 用户 ID，指定是哪个用户/主播的音频流。
     */
    long uid;
    /**
     * 用户的音频流 ID。
     */
    const char *mediaId;
    /**
     * 接收流在统计周期内的平均码率（Kbps）。
     */
    int receivedBitrate;
    /**
     * 统计周期内的远端音频流的丢帧率 (%)。
     */
    int audioLossRate;
    /**
     * 接收端到网络抖动缓冲的网络延迟 (ms)。
     */
    int jitterBufferDelay;
    /**
     * 音视频同步时间差。
     */
    int avDiff;
    /**
     * 音量值。
     */
    int audioVolume;
    /**
     * 解码帧率。
     */
    int audioDecFps;
    /**
     * 采样率。
     */
    int sampleRate;
    /**
     * 声道数。
     */
    int numChannels;
    /**
     * 本地播放缓冲区大小 ms
     */
    int jitter;
    /**
     * 频单帧解码时长，包含队列时间，单位 ms
     */
    int decodeDur;
    /**
     * rtt ms
     */
    int rtt;
} RemoteAudioStats;

typedef struct RemoteVideoStats {

    /**
     * 用户所属的频道名称。
     */
    const char *channelName;
    /**
     * 用户ID，指定是哪个用户的视频流。
     */
    long uid;
    /**
     * 用户的视频流 ID，用于多流视频源。
     */
    const char *mediaId;
    /**
     * 视频流宽度。
     */
    int width;
    /**
     * 视频流高度。
     */
    int height;
    /**
     * 接收码率，单位为 Kbps。
     */
    int receivedBitrate;
    /**
     * 远端视频解码器的输出帧率，单位为 fps。
     */
    int decoderOutputFrameRate;
    /**
     * 远端视频渲染器的输出帧率，单位为 fps。
     */
    int rendererOutputFrameRate;
    /**
     * 延迟，单位为毫秒。
     */
    int delay;
    /**
     * 远端视频在网络对抗之后的丢包率 (%)。
     */
    int packetLossRate;
    /**
     * 音视频同步时间差。
     */
    int avDiff;
    /**
     * 端到端延迟(ms)
     */
    int latency;
    /**
     * 接收缓冲区大小(ms)
     */
    int jitter;
    /**
     * 解码耗时(ms)
     */
    int decodeDur;
    /**
     * rtt(ms)
     */
    int rtt;
} RemoteVideoStats;

typedef struct RtcStats {

    /**
     * 频道名称
     */
    const char *channelName;
    /**
     * 通话时长(秒)，累计值
     */
    int totalDuration;
    /**
     * 发送字节数(bytes), 累计值
     */
    int txBytes;
    /**
     * 接收字节数(bytes)，累计值
     */
    int rxBytes;
    /**
     * 发送音频字节数（bytes），累计值。
     */
    int txAudioBytes;
    /**
     * 发送视频字节数（bytes），累计值。
     */
    int txVideoBytes;
    /**
     * 接收音频字节数（bytes），累计值。
     */
    int rxAudioBytes;
    /**
     * 接收视频字节数（bytes），累计值。
     */
    int rxVideoBytes;
    /**
     * 发送码率（Kbps），瞬时值。
     */
    int txKBitRate;
    /**
     * 接收码率（Kbps），瞬时值。
     */
    int rxKBitRate;
    /**
     * 发送音频码率(kbps)，瞬时值
     */
    int txAudioKBitRate;
    /**
     * 接受音频码率(kbps)，瞬时值
     */
    int rxAudioKBitRate;
    /**
     * 发送视频码率(kbps)，瞬时值
     */
    int txVideoKBitRate;
    /**
     * 接受视频码率(kbps)，瞬时值
     */
    int rxVideoKBitRate;
    /**
     * 客户端上行发送到服务器丢包率 (%)
     */
    int txPacketLossRate;
    /**
     * 服务器下行发送到客户端丢包率 (%)
     */
    int rxPacketLossRate;
    /**
     * 客户端-接入服务器延时 (毫秒)。
     */
    int lastmileDelay;
    /**
     * 客户端到本地路由器的往返时延 (ms)。
     */
    int gatewayRtt;
    /**
     * 当前 App 的内存占比 (%)。
     */
    double memoryAppUsageRatio;
    /**
     * 当前 App 的 CPU 使用率 (%)，自 Android 8.1 起，因系统限制，你无法通过该属性获取 CPU 使用率。
     */
    double cpuAppUsage;
    /**
     * 当前系统的 CPU 使用率 (%)，自 Android 8.1 起，因系统限制，你无法通过该属性获取 CPU 使用率。
     */
    double cpuTotalUsage;
} RtcStats;

#endif //MYCXXAPPLICATION_IOMNIRTCDEFINES_H
