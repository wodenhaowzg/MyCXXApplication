//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCCHANNELMANAGER_H
#define CORERTCPROJECT_RTCCHANNELMANAGER_H

#include "RtcChannelInfoModel.h"
#include <list>

namespace RTCEngine {

class RtcRequestServerManager;
class RtcChannelEventManager;
class RtcChannelAVManager;
class RtcTokenHandler;
class AVStreamPublishHandler;
class LocalRtcChannelNativeCallback;
class RtcEventReportLogger;
class RtcInterCallReportLogger;

class RtcChannelManager {
    public:
        RtcChannelManager(std::string channelName);
        virtual ~RtcChannelManager();
    
    private:
        GlobalChannelConfig global_channel_config_;
        RtcRequestServerManager* request_server_mgr_ = nullptr;
        RtcChannelEventManager* channel_event_mgr_ = nullptr;
        RtcChannelAVManager* channel_av_mgr_ = nullptr;
        RtcTokenHandler* token_handler_ = nullptr;
        AVStreamPublishHandler* stream_publish_handler_ = nullptr;
        RtcChannelInfoModel channel_info_model_;
        LocalRtcChannelNativeCallback* local_channel_native_callback_ = nullptr;
        RtcEventReportLogger* event_report_logger_ = nullptr;
        RtcInterCallReportLogger* inter_call_report_logger_ = nullptr;
        
        std::list<std::string> rtmp_url_list_;
        std::string channel_session_id_;
        std::string audio_upload_media_id_;
        std::string video_upload_media_id_;
        bool report_enter_begin_event_ = true;
};

}

#endif //CORERTCPROJECT_RTCCHANNELMANAGER_H
