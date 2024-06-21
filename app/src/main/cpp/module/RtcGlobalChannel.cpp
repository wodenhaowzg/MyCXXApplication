//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalChannel.h"

bool RtcGlobalChannel::IsJoinedChannel() {
    return is_joined_channel_;
}

long long RtcGlobalChannel::GetOwnerId() {
    return owner_id_;
}

void RtcGlobalChannel::SetOwnerId(long long int owner_id) {
    owner_id_ = owner_id;
}

void RtcGlobalChannel::SetIsJoinedChannel(bool is_joined_channel) {
    is_joined_channel_ = is_joined_channel;
}