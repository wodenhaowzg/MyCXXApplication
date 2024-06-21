//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalVideo.h"

std::string RtcGlobalVideo::GetVideoUplinkMediaId() {
    if (!video_uplink_media_id_.empty()) {
        return video_uplink_media_id_;
    }

    if (!video_default_uplink_media_id_.empty()) {
        return video_default_uplink_media_id_;
    }
    long long ownerId = channel_manager_.GetOwnerId();
    if (ownerId == 0) {
        return "";
    }
    video_default_uplink_media_id_ = ownerId + ":" + ownerId;
    video_uplink_media_id_ = video_default_uplink_media_id_;
    return video_uplink_media_id_;
}

void RtcGlobalVideo::SetRtcGlobalChannel(RtcGlobalChannel &channel) {
    channel_manager_ = channel;
}

bool RtcGlobalVideo::SetLocalEnabled(bool enabled) {
    if (enabled == video_local_enabled_) {
        return false;
    }
    video_local_enabled_ = enabled;
    return true;
}

void RtcGlobalVideo::SetVideoUplinkMediaId(std::string &mediaId) {
    if (mediaId == video_uplink_media_id_) {
        return;
    }
    video_uplink_media_id_ = mediaId;
}
