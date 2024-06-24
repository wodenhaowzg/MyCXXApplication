//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCCHANNELMANAGER_H
#define CORERTCPROJECT_RTCCHANNELMANAGER_H

#include "IOmniRtcChannel.h"
#include "IOmniRtcDefines.h"
#include "RtcChannelInfoModel.h"
#include "RtcDeviceManager.h"
#include "RtcEngineDefines.h"
#include "RtcUserManager.h"
#include <cstdint>
#include <list>
#include <mutex>

namespace RTCEngine {

class RtcRequestServerManager;
class RtcChannelEventManager;
class RtcChannelAVManager;
class RtcTokenHandler;
class LocalRtcChannelNativeCallback;
class RtcEventReportLogger;
class RtcInterCallReportLogger;
class InterCorrectionManager;
class RtcDeviceManager;
class RtcPublishStreamManager;
class RtcUserManager;

class RtcChannelManager : IOmniRtcChannel{
    public:
        struct RtcChannelConfig {
        public:
            std::string app_id;
            std::string channel_token;
            int64_t user_id;
            std::string rtmp_url;
        
            bool auto_subscribe_audio = true;
            bool auto_subscribe_video = true;
        };
    
        RtcChannelManager(std::string channelName);
        virtual ~RtcChannelManager();
    
        void SetRtcChannelEventHandler(OmniRtcChannelEventHandler *eventHandler) override;
        OmniRtcChannelEventHandler *GetEventHandler() const override;
        
        int64_t GetChannelUserId() { return channel_info_model_.user_id; }
        std::string GetChannelSessionId() const { return channel_session_id_; }
    
        RtcStatus SetClientRole(RtcClientRole role) override;
        RtcStatus JoinChannel(std::string token, int64_t uid, const ChannelMediaOptions &options) override;
        RtcStatus LeaveChannel() override;
        RtcStatus RenewToken(std::string token) override;
    
        ConnectState GetConnectionState() { return channel_info_model_.connect_state; }
    
        RtcStatus MuteLocalAudioStream(std::string media_id, bool muted) override;
        RtcStatus MuteLocalVideoStream(std::string media_id, bool muted) override;
        RtcStatus MuteRemoteAudioStream(int64_t uid, std::string media_id, bool muted) override;
        RtcStatus MuteRemoteVideoStream(int64_t uid, std::string media_id, bool muted) override;
        RtcStatus MuteAllRemoteAudioStreams(bool muted) override;
        RtcStatus MuteAllRemoteVideoStreams(bool muted) override;
        RtcStatus SetRemoteVideoStreamType(int64_t uid, std::string media_id, VideoStreamType stream_type) override;
    
        RtcStatus SetDefaultMuteAllRemoteAudioStreams(bool muted) override;
        RtcStatus SetDefaultMuteAllRemoteVideoStreams(bool muted) override;
    
        RtcStatus CreateDataStream(bool reliable, bool ordered) override;
        RtcStatus SendStreamMessage(int stream_id, const std::vector<unsigned char> &message) override;
    
        RtcStatus AddPublishStreamUrl(std::string url, bool transcodingEnabled);
        RtcStatus RemovePublishStreamUrl(std::string url);

        bool IsJoinedChannel() { return channel_info_model_.channel_state == RTC_CHANNEL_JOINED; };

    private:
        void leaveChannelInternal();
    
        void setRoleInternal(std::string channelName, RtcClientRole role);
    
        void resetGlobalAVPushStatus();
    
        void configureLogReport(std::string connectId);
    
    private:
        //GlobalChannelConfig global_channel_config_;
    
        RtcChannelInfoModel channel_info_model_;
        RtcRequestServerManager* request_server_mgr_ = nullptr;
        RtcChannelEventManager* channel_event_mgr_ = nullptr;
        RtcTokenHandler* token_handler_ = nullptr;
        LocalRtcChannelNativeCallback* local_channel_native_callback_ = nullptr;
        RtcInterCallReportLogger* inter_call_report_logger_ = nullptr;
    
        std::shared_ptr<InterCorrectionManager> inter_correction_mgr_ = nullptr;
        std::unique_ptr<RtcChannelAVManager> channel_av_mgr_ = nullptr;
        std::unique_ptr<RtcDeviceManager> video_device_mgr_ = nullptr;
        std::unique_ptr<RtcPublishStreamManager> publish_stream_mgr_ = nullptr;
        std::unique_ptr<RtcUserManager> user_mgr_ = nullptr;
        std::unique_ptr<RtcEventReportLogger> event_report_logger_ = nullptr;
        
        std::list<std::string> rtmp_url_list_;
        std::string channel_session_id_;
        std::string audio_upload_media_id_;
        std::string video_upload_media_id_;
        bool report_enter_begin_event_ = true;
    
        std::mutex mutex_;
};

}

#endif //CORERTCPROJECT_RTCCHANNELMANAGER_H
