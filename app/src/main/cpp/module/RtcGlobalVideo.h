//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALVIDEO_H
#define MYCXXAPPLICATION_RTCGLOBALVIDEO_H

#include "OmniRtcEngine.h"

class RtcGlobalVideo {

public:
    std::string getVideoUplinkMediaId();

    void setVideoUplinkMediaId(std::string &mediaId);

private:
    OmniRtcEngine* rtc_engine_;
    std::string video_uplink_media_id_;
    std::string video_default_uplink_media_id_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALVIDEO_H