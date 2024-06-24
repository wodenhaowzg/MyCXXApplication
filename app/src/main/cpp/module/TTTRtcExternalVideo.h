#ifndef __EXTERNAL_VIDEO_MODULE_H__
#define __EXTERNAL_VIDEO_MODULE_H__
//#include <stdio.h>
//#include <stdint.h>
#include <vector>
#include <memory>
/**
 视频帧类型
 */
enum {
    T_H264_NAL_SLICE           = 1,
    T_H264_NAL_DPA             = 2,
    T_H264_NAL_DPB             = 3,
    T_H264_NAL_DPC             = 4,
    T_H264_NAL_IDR_SLICE       = 5,
    T_H264_NAL_SEI             = 6,
    T_H264_NAL_SPS             = 7,
    T_H264_NAL_PPS             = 8,
    T_H264_NAL_AUD             = 9,
    T_H264_NAL_END_SEQUENCE    = 10,
    T_H264_NAL_END_STREAM      = 11,
    T_H264_NAL_FILLER_DATA     = 12,
    T_H264_NAL_SPS_EXT         = 13,
    T_H264_NAL_AUXILIARY_SLICE = 19,
};

// 
typedef enum _EVideoMediaStat
{
    E_VMS_IDLE = 0, // 链路已关闭
    E_VMS_CONNECTING = 1, // 连接中
    E_VMS_CONNECTED = 2, // 已连接
    E_VMS_CONNECT_FAILED = 3, // 连接失败
    E_VMS_CLOSE = 4 // 正在执行关闭链路
}EVideoMediaStat;

// 媒体链路服务器相关地址信息
typedef struct _VideoMediaServerInfo
{
    char msIp[20];
    int msPort;
    int msIOType;
    char msId[128];
    int msState; // 链接状态 -- EVideoMediaStat
}VideoMediaServerInfo;
typedef enum VideoFrameType
{
    FRAMETYPE_INVALID,
    FRAMETYPE_SPS_PPS,
    FRAMETYPE_I,
    FRAMETYPE_P
} VideoFrameType;

typedef struct _VideoFrameDescEx
{
    long long picture_id = -1;// kNoPictureId;
    long long first_packet_received_time = 0;
    long long last_packet_received_time = 0;
    long long assemble_time = 0;
    uint32_t timestamp_rtp = 0;
    bool is_keyframe = 0;
    long long ts = 0; // 视频时间戳
    int width = 0; // 宽
    int height = 0; // 高
    VideoFrameType frameType = FRAMETYPE_INVALID; // 帧类型：FRAMETYPE_INVALID - 无效数据 FRAMETYPE_SPS_PPS - sps&pps FRAMETYPE_I - I帧 FRAMETYPE_P - P帧
}VideoFrameDescEx;

typedef struct VideoStatistics
{
    char roomid[256];
    long long userid;               // 用户id
    char devId[256];                // 设备id
    int ssrc;                       // ssrc
    long long recv_data_size;             // 接收字节数
    int recv_frame_count;           // 接收帧数
    int lost_frame_count;           // 丢失帧数
    int recv_bitrate;               // 接收码率
    int decode_bitrate;             // 解码码率
    int recv_fps;                   // 接收帧率
    int decode_fps;					// 解码帧率
    int render_fps;					// 渲染帧率
    int buffer_duration;            // ？？？
    int delay_ms;                   // 端到端延迟
    int recv_pkts;                  // 接收数据包个数
    int recvFecPkts;                // 接收FEC数据包个数
    int fraction_lost;              // 接收丢包率（网络）
    int rtt;                        // rtt
    int lost_rate;                  // 实际丢包率
    int jitter_in_ms;               // 接收缓冲区大小
    int r_delay;                    // 小卡顿
    int lost_delay;                 // 大卡顿
    int r_delay_fraction;           // r_delay in 2s
    int lost_delay_fraction;        // lost_delay in 2s
    int width;                      // 视频宽
    int height;                     // 视频高

    long long av_sync_diff;         //音视频同步时间差
    int v_target_vbr;               //目标码率
    int e2e_fraction_lost;          //端到端丢包

    // 
    int64_t frame_cached_ms;     // 视频帧缓存时长 - 来自于 RtpVideoStreamReceiver::frame_buffer_
    size_t frame_cached_size;    // 视频帧缓存帧数 - 来自于 RtpVideoStreamReceiver::frame_buffer_
    size_t decode_pending_size;  // 视频帧解码排队数 - 来自于 RtpVideoStreamReceiver::decode_queue_

    // 
    VideoMediaServerInfo vmsInfo;   // 媒体链路信息
    // 
    bool isValid; // 是否有效信息（如果底层该链路已不存在，则 isValid 将为 false）
} VideoStatistics;

typedef struct LocalVideoStatistics
{
    char roomID[256];
    long long userID;
    int V_SSRC;
    int V_VBR;
    int V_RBR;
    int V_FBR;
    int V_FPS;
    long long V_SENDBYTES;
    int V_SENDCOUNT;
    int V_SENDFECCOUNT;
    int V_SENDPADDINGCOUNT;
    int V_SENDFRACTIONLOST;
    int V_RTT;
    long long TS;
    int V_BUFDURATION;
    int V_ERRORTIMES;
    char devId[128];
    // 
    VideoMediaServerInfo vmsInfo;   // 媒体链路信息
    // 
    bool isValid; // 是否有效信息（如果底层该链路已不存在，则 isValid 将为 false）
} LocalVideoStatistics;

typedef struct VideoRecvLenStatistics
{
    char roomid[256];
    long long userid;
    int recvLen;
    int udpRecvLen;
    int fecVecSize;
} VideoRecvLenStatistics;

struct H264_Nal
{
    unsigned char* payload;
    int payload_len;
};

class TTTEncodedVideoFrame
{
public:
    TTTEncodedVideoFrame(const char* mediaid, VideoFrameType frameType, int width, int height, long long pts, int layer, bool svcEnable, int tempolayer);
    virtual ~TTTEncodedVideoFrame();
    void pushNal(const char* nal, int nalLen);
    void pushNals(H264_Nal nals[], int nalSize);
    
    VideoFrameType frameType();
    const char* mediaId();

    int width();
    int height();
    long long pts();
    int layer();
    int temporalLayer();
    bool svcEnable();
    std::vector<H264_Nal> nals();
    
private:
    char mediaid_[256];
    VideoFrameType frameType_;
    int width_;
    int height_;
    long long pts_;
    int layerId = 0;
    int temporalLayer_ = 0;
    bool svcEnable_ = false;
    std::vector<H264_Nal> nals_;
};

typedef struct VideoSendStreamInfo
{
    bool sending;
    bool dynamicEncoding;
    bool isDual;
    int layerid;
    int qualityid;
    int maxFps;
    int maxBitrate;
    int estimatedBitrate;
    int width;
    int height;
    int encErrs;
    int encFrames;
    long long encSize;
    void *videoFrameSpliter; // for VideoFrameSpliter
    char devId[256];
    long long last_adjust_tick;
} VideoSendStreamInfo;

typedef struct GSVideoLayerInfo
{
	int layerId;
	int qualityId;
	int width;
	int height;
	int bitrate;
} GSVideoLayerInfo;

typedef struct VideoCodecFeedback
{
	char* mediaId;
	long long timestamp;
	GSVideoLayerInfo* layerInfos;
	int layers_;

	VideoCodecFeedback(const char* mid, int layer_size, long long ts)
	{
		mediaId = NULL;
		layerInfos = NULL;
		timestamp = ts;
		layers_ = layer_size;

		if (mid)
		{
			mediaId = new char[strlen(mid) + 1];
			strcpy(mediaId, mid);
		}

		if (layers_ > 0)
		{
			layerInfos = new GSVideoLayerInfo[layers_];
		}
	}

	~VideoCodecFeedback()
	{
		if (mediaId)
		{
			delete[] mediaId;
		}
		if (layerInfos)
		{
			delete[] layerInfos;
		}
	}
} VideoCodecFeedback;


class ExternalVideoModule;

/**
 *  外置视频模块代理，由sdk调用方实现，提供输出编码后的视频数据，以及接收视频数据并播放的功能
 */
class ExternalVideoModuleDelegate
{
public:

    /**
     *  开始视频采集并编码，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool startSend(const char* mediaId, int& error) = 0;
    
    /**
     *  停止视频采集并编码，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool stopSend(const char* mediaId) = 0;

	/**
	 *  开始小流视频采集并编码，由sdk内部调用
	 *
	 *  @return true-成功 false-失败
	 */
	virtual bool startDualSend(const char* mediaId, int layer) = 0;

	/**
	 *  停止小流视频采集并编码，由sdk内部调用
	 *
	 *  @return true-成功 false-失败
	 */
	virtual bool stopDualSend(const char* mediaId) = 0;

    /**
     * 申请产生I帧
     */
    virtual void requestIFrame() = 0;
    /**
     * 在第二路（小流）上申请产生I帧
     */
    virtual void requestDualIFrame() = 0;

	/**
	 *  开始视频采集并编码，由sdk内部调用
	 *
	 *  @return true-成功 false-失败
	 */
	virtual bool startPlay(const char* mediaId) = 0;

    /**
     *  停止视频采集并编码，由sdk内部调用
     *
     *  @return true-成功 false-失败
     */
    virtual bool stopPlay(const char* mediaId) = 0;
	/**
	*  获取该设备允许的最大编码帧率
	*
	*  @return true-成功 false-失败
	*/
	virtual int maxFps(const char* mediaId, int layer = 1) = 0;
	/**
	*  获取该设备允许的最大编码码率
	*
	*  @return true-成功 false-失败
	*/
	virtual int maxBitrate(const char* mediaId, int layer) = 0;
    /**
     * 请求改变编码参数 （for momo)
     */
	virtual bool changeEncParam(const char* mediaId, unsigned int bitrate, int layerId = 0) = 0;
    /**
    *  获取相应 layer 在 media 上码率占比
    *  @return 百分比的分子部分 - 如 10%，则返回 10
    */
    virtual float bitrateRatio(const char* mediaId, int layer) = 0;

    // TODO(jove) 2024/03/22: deprecate
	virtual int targetBps(const char* mediaId) = 0;
    // 
    virtual int targetBps(const char* mediaId, int layer) = 0;
    
    // TODO(jove) 2024/03/22: deprecate
    virtual int targetFps(const char* mediaId) = 0;

    virtual int targetFps(const char* mediaId, int layer) = 0;

    // TODO(jove) 2024/03/22: deprecate
    virtual int dynamicBps(const char* mediaId) = 0;
    // 
    virtual int dynamicBps(const char* mediaId, int layer) = 0;

    /**
     *  接收视频数据，供解码播放使用，由sdk内部调用
     *
     *  @param data      视频数据
     *  @param len       视频数据长度
     *  @param channelId 房间id
     *  @param mediaId     媒体通道id
     *  @param frameDesc 视频帧描述信息
     */
    virtual void receiveVideoData(const char* data, int len, const char* channelId, const char* mediaId, const VideoFrameDescEx &frameDesc) = 0;

    virtual void receiveH264Sei(char* data, int len, long long userId, char* mediaId) = 0;

    virtual void setExternalModule(ExternalVideoModule* pModule) = 0;

	virtual int getDecodeFps(const char* devID) = 0;
	virtual int getDecodeInputFps(const char* devID) = 0;
	virtual int getDecodeFailFps(const char* devID) = 0;
	virtual int64_t	getDecFailCount(const char* devID) = 0;
	virtual int getAvgDecElapsed(const char* devID, int &avgMs, int &maxMs, int &minMs) = 0;
	virtual int getRenderFps(const char* devID) = 0;
	virtual int getDecOutputFps(const char* devID) = 0;

	virtual int getEncodeFps(const char* devID) = 0;
	virtual int getEncodeInputFps(const char* devID) = 0;
	virtual int getEncodeFailFps(const char* devID) = 0;
	virtual int getStreamEncodeBitrate(const char* devID) = 0;
	virtual int getSubStreamEncodeBitrate(const char* devID) = 0;
	virtual int getSubEncodeFps(const char* devID) = 0;

    virtual void onSignalDisconnect() = 0;
    virtual void OnVideoConnectFailed(char* szMediaID) = 0;

    virtual int getNumOfVideoDevices() = 0;
    virtual int getVideoDeviceName(unsigned int index, char* devID, const int maxDevIDLength, int& inuse, int& devType, int& mute) = 0;
    virtual int getVideoDeviceParameter(unsigned int index, int& width, int& height, int& framerate, int& bitrate) = 0;
    virtual bool getDefaultDevice(char* devID, const int maxDevIDLength) = 0;
};

/**
 *  视频模块接口
 */
class ExternalVideoModule
{
public:
    static ExternalVideoModule* sharedInstance();

    virtual ~ExternalVideoModule() {};
    /**
     *  设置外置视频模块代理
     *
     *  @param externalVideoModuleDelegate 由sdk调用方实现的ExternalVideoModuleDelegate
     */
    virtual void setExternalVideoModuleDelegate(ExternalVideoModuleDelegate* delegate) = 0;
    
    /**
     *  设置视频缓冲的buffer大小
     *
     *  @param duration buffer大小，单位ms
     */
    virtual void setMaxBufferDuration(int duration) = 0;
    
    /**
     *  获取视频缓冲的buffer大小
     *
     *  @return buffer大小，单位ms
     */
    virtual int getBufferDuration(const char *mediaID) = 0;

    /**
     * 获取发送视频数据的总帧数
     *
     * @return 帧数
     */
    virtual int getSentFrameCount() = 0;
    
    /**
     * 获取发送视频数据的总字节数
     *
     * @return 字节数
     */
    virtual long long getTotalSendBytes() = 0;

    /**
     * 获取接收视频数据的总字节数
     *
     * @return 字节数
     */
    virtual long long getTotalRecvBytes() = 0;

    virtual int getRecvDataErrorTimes() = 0;

    virtual LocalVideoStatistics* getLocalVideoStatistics(int &count) = 0;

    virtual int getRecvBytes(const char* channelId, int64_t& rxBytes, int64_t& lastRx) = 0;
    
    // TTTEncodedVideoFrame::layer 已涵盖了 主流 / 子流
    // 2024/06/14: 接口统一 - 通过 layer 参数 涵盖了 pushEncodedVideoFrame / pushDualEncodedVideoFrame
    virtual bool pushEncodedVideoFrame(std::shared_ptr<TTTEncodedVideoFrame> encodedFrame) = 0;
    // layer 参数 已涵盖了 主流 / 子流
    // 2024/06/14: 接口统一 - 通过 layer 参数 涵盖了 pushEncodedVideoData / pushDualEncodedVideoData
    virtual bool pushEncodedVideoData(const char *mediaId, H264_Nal nals[], int nalSize, VideoFrameType frameType, 
        int videoWidth, int videoHeight, unsigned long long timestamp, int layer, bool svcEnable, int tempolayer) = 0;

    virtual void addLocalVideo(const char *mediaID, int width, int height, int fps,int bitrate, float bitrateRatio, int layerId) = 0;//for local video frame spilter
    virtual void delLocalVideo(const char *mediaID) = 0;

    // 2024/06/14: 接口统一 - 来自于 Android
    virtual void insertH264SeiContent(char* data, int len) = 0;

    // android: updateMaxBitrateControlParam --> dynamicAdjBitrate & dynamicAdjFps
    // Notify videoNetEq for rate control(pacer / fec ...)
    virtual void dynamicAdjFps(const char* mediaID, int fps) = 0;
    virtual void dynamicAdjBitrate(const char* mediaID, int bitrate) = 0;

    // { Only for stats
    // 2024/06/14: 接口统一 - 来自于 Android
    virtual int getLastSliceQp() = 0;
    // 2024/06/14: 接口统一 - 来自于 Android
    virtual void getVideoStuckStats() = 0;
    // }
};

#endif
