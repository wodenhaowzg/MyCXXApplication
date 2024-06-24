//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalChannel.h"
#include "RtcEngineDefines.h"

void RtcGlobalChannel::destroy() {
    auto iterator = channel_map_.begin();
    while (iterator != channel_map_.end()) {
        RTCEngine::RtcChannelManager *rtcChannel = iterator->second;
        delete rtcChannel;
        iterator++;
    }
    channel_map_.clear();
}

bool RtcGlobalChannel::IsJoinedChannel() {
    bool is_joined_channel = false;
    auto iterator = channel_map_.begin();
    while (iterator != channel_map_.end()) {
        RTCEngine::RtcChannelManager *rtcChannel = iterator->second;
        if (rtcChannel->IsJoinedChannel()) {
            is_joined_channel = true;
            break;
        }
        iterator++;
    }
    return is_joined_channel;
}

long long RtcGlobalChannel::GetOwnerId() { return owner_id_; }

std::string RtcGlobalChannel::GetConnectId() {
    std::lock_guard<std::mutex> lock(mutex_);
    return connect_id_;
}

void RtcGlobalChannel::SetOwnerId(long long int owner_id) { owner_id_ = owner_id; }

int RtcGlobalChannel::SetRoleForBroadcaster(std::string channel_name, RtcClientRole role) {
    if (channel_name.empty()) {
        return -1;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    if (role == CLIENT_ROLE_BROADCASTER) {
        if (!channel_name_hold_broadcaster_.empty() && channel_name_hold_broadcaster_ != channel_name) {
            return -5;
        }
        // TODO : log not implemented
        // OmniLog.i3("The channel role change to broadcaster. channelName: " + channelName + "    logTag: " + CHANNEL_PUSH);
        channel_name_hold_broadcaster_ = channel_name;
    } else {
        if (!channel_name_hold_broadcaster_.empty()) {
            if (channel_name == channel_name_hold_broadcaster_) {
                // TODO : log not implemented
                // OmniLog.i3("The channel role change to audience. channelName: " + channelName + "    logTag: " + CHANNEL_PUSH);
                channel_name_hold_broadcaster_ = "";
            }
        }
    }
    return 0;
}

void RtcGlobalChannel::SetConnectId(std::string &connectId) {
    std::lock_guard<std::mutex> lock(mutex_);
    connect_id_ = connectId;
}

IOmniRtcChannel *RtcGlobalChannel::CreateRtcChannel(std::string channel_name) {
    RTCEngine::RtcChannelManager *rtcChannel = channel_map_[channel_name];
    if (rtcChannel == nullptr) {
        rtcChannel = new RTCEngine::RtcChannelManager(channel_name);
        channel_map_[channel_name] = rtcChannel;
    }
    return (IOmniRtcChannel *)rtcChannel;
}

void RtcGlobalChannel::DestroyRtcChannel(std::string channel_name) {
    RTCEngine::RtcChannelManager *rtcChannel = channel_map_.find(channel_name)->second;
    delete rtcChannel;
    channel_map_.erase(channel_name);
}