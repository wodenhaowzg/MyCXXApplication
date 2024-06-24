//
// Created on 2024/6/20.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCBASEMANAGER_H
#define CORERTCPROJECT_RTCBASEMANAGER_H

#include <mutex>
#include <string>

namespace RTCEngine {

class RtcBaseManager {
    public:
        RtcBaseManager(std::string channelName) { channel_name_ = channelName; }
        std::string GetChannelName() { return channel_name_; }
    
        virtual void ClearResource() = 0;
    
    protected:
        std::string channel_name_;
        std::mutex mutex_;
};

}

#endif //CORERTCPROJECT_RTCBASEMANAGER_H
