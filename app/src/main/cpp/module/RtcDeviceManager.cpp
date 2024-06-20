//
// Created on 2024/6/20.
// author : zhangguang@tal.com

#include "RtcDeviceManager.h"

namespace RTCEngine {

RtcDeviceManager::RtcDeviceManager(std::string channelName)
: RtcBaseManager(channelName) {
}

void RtcDeviceManager::ClearResource() {
    std::lock_guard<std::mutex> lock(mutex_);
    user_device_map_.clear();
}

void RtcDeviceManager::ClearUserDevice(int64_t userId) {
    std::lock_guard<std::mutex> lock(mutex_);
    user_device_map_.erase(userId);
}

void RtcDeviceManager::AddDevice(UserDeviceConfig& userDeviceConfig) {
    std::lock_guard<std::mutex> lock(mutex_);
    bool exists = false;
    auto iter = user_device_map_.find(userDeviceConfig.user_id);
    if (iter != user_device_map_.end()) {
        for (const auto & devConfig : iter->second) {
            if (devConfig.device_id == userDeviceConfig.device_id) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            iter->second.push_back(userDeviceConfig);
        }
    } else {
        std::vector<UserDeviceConfig> userDeviceVector;
        userDeviceVector.push_back(userDeviceConfig);
        user_device_map_.emplace(userDeviceConfig.user_id, userDeviceVector);
    }
}

void RtcDeviceManager::RemoveDevice(UserDeviceConfig& userDeviceConfig) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = user_device_map_.find(userDeviceConfig.user_id);
    if (iter != user_device_map_.end()) {
        iter->second.erase(std::remove_if(iter->second.begin(), 
                                        iter->second.end(), 
                                        [](UserDeviceConfig config) {
                                            if (config.device_id == userDeviceConfig.device_id) {
                                                // TODO: log not implemented
                                                OmniLog.i(USER_WATCH, TAG, "Remove audio device, id = " + config.getDeviceId());
                                                return true;
                                            }
                                            return false;
                                        }), 
                            iter->second.end());
    }
}

std::vector<UserDeviceConfig> RtcDeviceManager::UpdateUserDevice(int64_t userId, std::vector<UserDeviceConfig> newUserDeviceConfigs) {
    std::vector<UserDeviceConfig> result;
    if (newUserDeviceConfigs.size() == 0) {
        return result;
    }
    
    // 新的设备列表，去掉device_id == "0" 的项
    newUserDeviceConfigs.erase(std::remove_if(newUserDeviceConfigs.begin(), 
                                            newUserDeviceConfigs.end(), 
                                            [] (UserDeviceConfig config) {
                                                return config.device_id == "0";
                                            }),
                            newUserDeviceConfigs.end());
    
    // 过滤设备id为0之后，没有获取到真正到视频设备列表... 中断更新
    if (newUserDeviceConfigs.size() == 0) {
        // TODO: log not implemented
        OmniLog.w(USER_WATCH, TAG, "The new device list is empty... because device id is zero...");
        return result;
    }
    
    // 打印新的视频设备列表
    for (const auto devConfig : newUserDeviceConfigs) {
        // TODO: log not implemented
        OmniLog.i(USER_WATCH, TAG, "The new device list member = " + devConfig.device_id);
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = user_device_map_.find(userId);
    
    // 没有老的设备列表，保存新的列表并返回
    if (iter == user_device_map_.end() || iter->second.size() == 0) {
        // TODO: log not implemented
        OmniLog.i(USER_WATCH, TAG, "The old device list is null.");
        user_device_map_.emplace(userId, newUserDeviceConfigs);
        result.insert(result.end(), newUserDeviceConfigs.begin(), newUserDeviceConfigs.end());
        return result;
    }
    
    // 打印老的视频设备列表
    for (const auto &devConfig : iter->second) {
        // TODO: log not implemented
        OmniLog.i(USER_WATCH, TAG, "The old device list member : " + devConfig.device_id);
    }
    
    
}

}

