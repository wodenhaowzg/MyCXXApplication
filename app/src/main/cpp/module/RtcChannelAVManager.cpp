//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#include "RtcChannelAVManager.h"
#include "InterCorrectionManager.h"
#include "RtcDeviceManager.h"

namespace RTCEngine {

// TODO: should be defined somewhere
extern GlobalConfig globalConfig;

namespace {
constexpr bool CONFIG_AUDIO_LOCAL_MUTE = true;
constexpr bool CONFIG_VIDEO_LOCAL_MUTE = true;
}

RtcChannelAVManager::RtcChannelAVManager(std::string channelName, std::string tag)
: channel_name_(channelName)
, audio_muted_(CONFIG_AUDIO_LOCAL_MUTE) 
, video_muted_(CONFIG_VIDEO_LOCAL_MUTE) {
    log_tag_ = tag + "][" + "RtcChannelAVManager";
};

void RtcChannelAVManager::LeaveChannel() {
    local_video_upload_ = false;
    default_all_remote_audio_muted_ = false;
    default_all_remote_video_muted_ = false;
    audio_muted_ = true;
    video_muted_ = true;
}

int RtcChannelAVManager::MuteLocalAudioStream(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted) {
    if (!globalConfig.audio_enabled) {
        return -1;
    }
    
    if (muted == audio_muted_) {
        return 0;
    }
    
    audio_muted_ = muted;
    if (channelInfo.channel_stat != RTC_CHANNEL_JOINED) {
        return 0;
    }
    
    return muteLocalAudioStreamInternal(channelInfo, mediaId, muted);
}

int RtcChannelAVManager::MuteLocalVideoStream(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted) {
    if (muted == video_muted_) {
        return 0;
    }
    
    video_muted_ = muted;
    if (channelInfo.channel_stat != RTC_CHANNEL_JOINED) {
        return 0;
    }
    
    return muteLocalVideoStreamInternal(channelInfo, mediaId, muted);
}

int RtcChannelAVManager::muteLocalAudioStreamInternal(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted) {
    updateHeartbeatReporterAVStatus(!muted, STREAM_AUDIO);
    if (channelInfo.client_role == CLIENT_ROLE_AUDIENCE && !muted) {
        return 0;
    }
    
    // TODO: GlobalHolder should be defined somewhere
    if (mediaId.empty()) {
        GlobalAudioConfig* globalAudioConfig = GlobalHolder.getInstance().getGlobalAudioConfig();
        if (globalAudioConfig) {
            mediaId = globalAudioConfig->getUploadMediaId();
        }
    }
    
    // TODO: log not defined here
    if (mediaId.empty()) {
        logE("Failed to call <MuteLocalAudio> api, mediaId is empty! channelName: " + mChannelName + ", muted: " + muted);
        return -1;
    }
    
    // TODO: replace with native function
    RoomJni.getInstance().MuteLocalAudio(channel_name_, mediaId, muted);
    
    return 0;
}

int RtcChannelAVManager::muteLocalVideoStreamInternal(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted) {
    updateHeartbeatReporterAVStatus(!muted, STREAM_VIDEO);
    if (channelInfo.client_role == CLIENT_ROLE_AUDIENCE && !muted) {
        return 0;
    }
    
    // TODO: GlobalHolder should be defined somewhere
    if (mediaId.empty()) {
        GlobalVideoConfig* globalVideoConfig = GlobalHolder.getInstance().getGlobalVideoConfig();
        if (globalVideoConfig) {
            mediaId = globalVideoConfig->getVideoUploadMediaId();
        }
    }
    
    // TODO: log not defined here
    if (mediaId.empty()) {
        logE("Failed to call <MuteLocalVideo> api, mediaId is empty! channelName: " + mChannelName + ", muted: " + muted);
        return -1;
    }
    
    // TODO: replace with native function
    RoomJni.getInstance().MuteLocalVideo(channel_name_, mediaId, muted);
    
    updateLocalVideoInternal(mediaId, !muted);
    
    return 0;
}

int RtcChannelAVManager::muteRemoteStreamInternal(RtcChannelInfoModel &channelInfo, std::string mediaId, bool muted, StreamType streamType) {
    // TODO: GlobalHolder should be defined somewhere
    InterCorrectionManager* interCorrectionManager = GlobalHolder.getInstance().getInterCorrectionManager();
    if (interCorrectionManager == nullptr) {
        return -1;
    }
    
    std::string targetMediaId = "";
    std::string saveMediaId;
    InterCorrection interCorrection;
    std::string channelName = channelInfo.channel_name;
    if (mediaId.empty()) {
        
    } else {
        
    }
}

}
