//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALVIDEO_H
#define MYCXXAPPLICATION_RTCGLOBALVIDEO_H

#include <string>
#include "RtcGlobalChannel.h"

class RtcGlobalVideo {

public:
    std::string GetVideoUplinkMediaId();

    void SetRtcGlobalChannel(RtcGlobalChannel &channel);

    bool SetLocalEnabled(bool enabled);

    void SetVideoUplinkMediaId(std::string &mediaId);

private:
    RtcGlobalChannel channel_manager_;
    std::string video_uplink_media_id_;
    std::string video_default_uplink_media_id_;
    bool video_local_enabled_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALVIDEO_H