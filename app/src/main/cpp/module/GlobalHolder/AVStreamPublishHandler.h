//
// Created on 2024/6/22.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_AVSTREAMPUBLISHHANDLER_H
#define CORERTCPROJECT_AVSTREAMPUBLISHHANDLER_H

#include <mutex>
#include <string>
#include <unordered_map>
#include "RtcEngineDefines.h"

namespace RTCEngine {

class AVStreamPublishHandler {
    public:
        struct AVStreamPublishInfo {
        public:
            std::string channel_name = "";
            bool audio_muted = true;
            bool video_muted = true;
            RtcClientRole role = CLIENT_ROLE_AUDIENCE;
        
            void Reset() {
                channel_name = "";
                audio_muted = true;
                video_muted = true;
                role = CLIENT_ROLE_AUDIENCE;
            }
        
            std::string ToString() {
                return "";
                // TODO : not implemented
//                 return "AVStreamPublishBean{" +
//                 "mChannelName='" + mChannelName + '\'' +
//                 ", mAudioMuted=" + mAudioMuted +
//                 ", mVideoMuted=" + mVideoMuted +
//                 ", mRole=" + mRole +
//                 '}';
            }
        };
    
        AVStreamPublishHandler() = default;
        virtual ~AVStreamPublishHandler() = default;
    
        void ClearResource();
    
        void AddAVStreamPublishInfo(AVStreamPublishInfo& info);
        void RemoveAVStreamPublishInfo(std::string channelName);
    
        std::string GetAVUploadChannelName() { return av_upload_channel_name_; }
    
        bool IsPublishStats() {
            std::lock_guard<std::mutex> lock(mutex_);
            return published_;
        }
        bool IsPublishStats(std::string channelName);
    
        bool IsAudioMuted();
        bool IsVideoMuted();
        bool IsChannelAVUnmuted();
        bool FindVideoUnmuted();
        bool UpdateAudioMuted(std::string channelName, bool muted);
        bool UpdateVideoMuted(std::string channelName, bool muted);
    
        void UpdateRole(std::string channelName, RtcClientRole role);
    
        // TODO : should be removed??
        void UpdateEngineUploadChannelName(std::string channelName);
    
    private:
        void updatePublishStats(AVStreamPublishInfo &info);
        
    private:
        std::unordered_map<std::string, AVStreamPublishInfo> info_map_;
        AVStreamPublishInfo stream_publish_info_;
        std::string av_upload_channel_name_;
        bool published_;
        std::mutex mutex_;
};

}

#endif //CORERTCPROJECT_AVSTREAMPUBLISHHANDLER_H
