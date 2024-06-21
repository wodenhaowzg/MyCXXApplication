//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalChannel.h"
#include "OmniRtcEngine.h"

bool RtcGlobalChannel::IsJoinedChannel() {
    return OmniRtcEngine::GetInstance()->IsJoinedChannel();
}

long long RtcGlobalChannel::GetOwnerId() {
    return owner_id_;
}

void RtcGlobalChannel::SetOwnerId(long long int owner_id) {
    owner_id_ = owner_id;
}