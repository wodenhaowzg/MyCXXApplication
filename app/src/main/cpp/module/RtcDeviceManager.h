//
// Created on 2024/6/20.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCDEVICEMANAGER_H
#define CORERTCPROJECT_RTCDEVICEMANAGER_H

#include "RtcBaseManager.h"
#include <unordered_map>
#include <vector>

namespace RTCEngine {

// TODO: UserDeviceConfig should be defined somewhere
class RtcDeviceManager : public RtcBaseManager {
    public:
        RtcDeviceManager(std::string channelName);
        virtual ~RtcDeviceManager();
    
        // RtcBaseManager
        virtual void ClearResource() override;
    
        void ClearUserDevice(int64_t userId);
    
        void AddDevice(UserDeviceConfig& userDeviceConfig);
        void RemoveDevice(UserDeviceConfig& userDeviceConfig);
        
        std::vector<UserDeviceConfig> UpdateUserDevice(int64_t userId, std::vector<UserDeviceConfig> newUserDeviceConfigs);
    
    private:
        std::unordered_map<int64_t, std::vector<UserDeviceConfig>> user_device_map_;
};

}

#endif //CORERTCPROJECT_RTCDEVICEMANAGER_H
