//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#include "RtcChannelManager.h"

namespace RTCEngine {

RtcChannelManager::RtcChannelManager(std::string channelName) {
    std::string log_tag = "RtcChannelManager<" + channelName + ">";
    
    channel_info_model_.channel_name = channelName;
    
}

}