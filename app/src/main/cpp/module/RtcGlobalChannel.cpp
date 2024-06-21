//
// Created by ZaneWang on 2024/6/20.
//

#include "RtcGlobalChannel.h"

bool RtcGlobalChannel::IsJoinedChannel() {
    return false;
}

long long RtcGlobalChannel::GetOwnerId() {
    return owner_id_;
}
