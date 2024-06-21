//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalVideo.h"
#include "OmniRtcEngine.h"

std::string RtcGlobalVideo::getVideoUplinkMediaId() {
    if (!video_uplink_media_id_.empty()) {
        return video_uplink_media_id_;
    }

    if (!video_default_uplink_media_id_.empty()) {
        return video_default_uplink_media_id_;
    }
    long long ownerId = rtc_engine_->GetRtcGlobalChannel().GetOwnerId();
    if (ownerId == 0) {
        return "";
    }
    video_default_uplink_media_id_ = ownerId + ":" + ownerId;
    video_uplink_media_id_ = video_default_uplink_media_id_;
    return video_uplink_media_id_;
}

void RtcGlobalVideo::setVideoUplinkMediaId(std::string &mediaId) {
    if (mediaId == video_uplink_media_id_) {
        return;
    }
    video_uplink_media_id_ = mediaId;
}