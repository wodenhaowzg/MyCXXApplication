//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCCHANNELAVMANAGER_H
#define CORERTCPROJECT_RTCCHANNELAVMANAGER_H

#include "RtcChannelInfoModel.h"
#include <list>

namespace RTCEngine {

class RtcChannelAVManager {
    public:
        RtcChannelAVManager(std::string channelName, std::string tag) { 
            channel_name_ = channelName; 
            log_tag_ = tag + "][" + "RtcChannelAVManager";
        };
        virtual ~RtcChannelAVManager() = default;
    
        void LeaveChannel();
    
        int MuteLocalAudioStream(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted);
        int MuteLocalVideoStream(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted);
    
        int MuteRemoteAudioStream(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted);
        int MuteRemoteVideoStream(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted);
    
        int MuteAllRemoteAudioStream(RtcChannelInfoModel &channelInfo, bool muted);
        int MuteAllRemoteVideoStream(RtcChannelInfoModel &channelInfo, bool muted);
    
        // TODO: renderMode, mirrorMode, streamType should be enumeration
        int SetRemoteRenderMode(RtcChannelInfoModel &channelInfo, int64_t userId, std::string mediaId, int renderMode, int mirrorMode);
        int SetRemoteVideoStreamType(RtcChannelInfoModel &channelInfo, int64_t userId, std::string mediaId, int streamType);
        
        int AdjustUserPlaybackSignalVolume(int64_t userId, std::string mediaId, int volume);
        
        int SetDefaultMuteAllRemoteAudioStreams(bool muted);
        int SetDefaultMuteAllRemoteVideoStreams(bool muted);
    
        /**
        * FIXME 子房间，缺少日志上报
        */
        void MixUserVideoStream(std::string channelName, int64_t userId, std::string deviceId, bool enabled);
    
    private:
        enum StreamType {
            STREAM_AUDIO,
            STREAM_VIDEO,
        };
    
        int muteLocalAudioStreamInternal(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted);
        int muteLocalVideoStreamInternal(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted);
    
        int muteRemoteStreamInternal(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted, StreamType streamType);
    
        void updateHeartbeatReporterAVStatus(bool localStreamEnabled, StreamType streamType);
    
    private:
        std::string channel_name_;
        std::string log_tag_;
    
        // 推流地址
        std::list<AVStreamConfig> stream_configs_;
    
        bool audio_muted_;
        bool video_muted_;
        bool default_all_remote_audio_muted_;
        bool default_all_remote_video_muted_;
    
        // 耳机监听是否已初始化 ??
        bool local_video_upload_;
};

}

#endif //CORERTCPROJECT_RTCCHANNELAVMANAGER_H
