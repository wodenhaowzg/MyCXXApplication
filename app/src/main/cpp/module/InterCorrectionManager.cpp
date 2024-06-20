//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#include "InterCorrectionManager.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace RTCEngine {

// Function to split a string based on a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void InterCorrectionManager::AddInterCorrection(InterCorrection &interCorrection) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (destroyed_) {
        return;
    }
    
    // TODO: log not implemented
    OmniLog.d(INTER_CORRECT_WATCH, TAG, "Add a new cache, bean = " + bean.toString());
    
    switch (interCorrection.type) {
        case INTER_CORRECT_TYPE_NORMAL: {
            action_map_.emplace(interCorrection.action, interCorrection);
            break;
        }
        case INTER_CORRECT_TYPE_USER: {
            handleUserMediaInterCorrection(interCorrection);
            break;
        }
        case INTER_CORRECT_TYPE_MEDIA: {
            handleUserMediaInterCorrection(interCorrection);
        }
    }
}

void InterCorrectionManager::handleUserInterCorrection(InterCorrection &interCorrection) {
    auto iter = user_map_.find(interCorrection.channel_name);
    if (iter == user_map_.end()) {
        ActionKeyMap actionMap;
        actionMap.emplace(interCorrection.action, interCorrection);
        
        std::unordered_map<int64_t, ActionKeyMap> userActionMap;
        userActionMap.emplace(interCorrection.user_id, actionMap);
        
        user_map_.emplace(interCorrection.channel_name, userActionMap);
    } else {
        auto iterUserAction = iter->second.find(interCorrection.user_id);
        if (iterUserAction == iter->second.end()) {
            ActionKeyMap actionMap;
            actionMap.emplace(interCorrection.action, interCorrection);
            
            iter->second.emplace(interCorrection.user_id, actionMap);
        } else {
            iterUserAction.emplace(interCorrection.action, interCorrection);
        }
    }
}

void InterCorrectionManager::handleUserMediaInterCorrection(InterCorrection &interCorrection) {
    auto iter = media_map_.find(interCorrection.channel_name);
    if (iter == media_map_.end()) {
        ActionKeyMap actionMap;
        actionMap.emplace(interCorrection.action, interCorrection);
        
        std::unordered_map<std::string, ActionKeyMap> mediaActionMap;
        mediaActionMap.emplace(interCorrection.media_id, actionMap);
        
        media_map_.emplace(interCorrection.channel_name, mediaActionMap);
    } else {
        auto iterMediaAction = iter->second.find(interCorrection.media_id);
        if (iterMediaAction == iter->second.end()) {
            ActionKeyMap actionMap;
            actionMap.emplace(interCorrection.action, interCorrection);
            
            iter->second.emplace(interCorrection.media_id, actionMap);
        } else {
            iterMediaAction.emplace(interCorrection.action, interCorrection);
        }
    }
}

Optional<InterCorrection> InterCorrectionManager::GetAndRemoveCachedInterCorrection(InterCorrection& interCorrection, bool remove) {
    // TODO: GlobalConfig should be defined somewhere
    // TODO: LocalSDKConstants should be defined somewhere
    std::lock_guard<std::mutex> lock(mutex_);
    std::string channelName = interCorrection.channel_name;
    if (channelName == GlobalConfig.local_room) {
        channelName = LocalSDKConstants.ENGINE_CHANNEL_ID;
    }
    
    ActionKeyMap actionMap;
    switch (interCorrection.type) { 
        case INTER_CORRECT_TYPE_NORMAL: {
            actionMap = action_map_;
            break;
        }
        case INTER_CORRECT_TYPE_USER: {
            auto iter = user_map_.find(interCorrection.channel_name);
            if (iter == user_map_.end()) {
                return Optional::nullopt;
            }
            
            auto iterActionMap = iter->second.find(interCorrection.user_id);
            if (iterActionMap == iter->second.end()) {
                return Optional::nullopt;
            }
            actionMap = iterActionMap->second;
            break;
        }
        case INTER_CORRECT_TYPE_MEDIA: {
            auto iter = media_map_.find(interCorrection.channel_name);
            if (iter == media_map_.end()) {
                return Optional::nullopt;
            }
            
            auto iterActionMap = iter->second.find(interCorrection.media_id);
            if (iterActionMap == iter->second.end()) {
                return Optional::nullopt;
            }
            actionMap = iterActionMap->second;
            break;
        }
    }
    
    Optional<InterCorrection> retVal = Optional::nullopt;
    auto item = actionMap.find(interCorrection.action);
    if (item != actionMap.end()) {
        retVal = item->second;
        if (remove) {
            actionMap.erase(item);
        }
    }
    
    return retVal;
}

Optional<InterCorrection> InterCorrectionManager::FindCachedInterCorrection(InterCorrection& interCorrection) {
    if (interCorrection.user_id <= 0) {
        // TODO: log not implemented
        OmniLog.w(INTER_CORRECT_WATCH, TAG, "Get inter cache bean failed, InterCorrectionEnum is null!");
        return Optional::nullopt;
    }
    
    std::lock_guard<std::mutex> lock(mutex_);
    if (interCorrection.type == INTER_CORRECT_TYPE_MEDIA) {
        auto iter = media_map_.find(interCorrection.channel_name);
        if (iter == media_map_.end()) {
            return Optional::nullopt;
        }
        
        std::string targetMediaId = "";
        for (const auto &pair : iter->second) {
            // TODO: split should be replaced with utility function
            std::vector<std::string> splitStr = split(pair.first, ':');
            if (splitStr.size < 2) {
                continue;
            }
            // TODO: stringToLL should be replaced with utility function
            int64_t userId = stringToLL(splitStr[0]);
            if (userId == InterCorrection.user_id) {
                targetMediaId = InterCorrection.media_id;
                break;
            }
        }
        
        if (!targetMediaId.empty()) {
            auto iterActionMap = iter->second.find(targetMediaId);
            if (iterActionMap == iter->second.end()) {
                return Optional::nullopt;
            } else {
                auto item = iterActionMap->second.find(interCorrection.action);
                if (item == iterActionMap->second.end()) {
                    return Optional::nullopt;
                } else {
                    return item->second;
                }
            }
        }
    }
    
    return Optional::nullopt;
}

void InterCorrectionManager::ClearResource(std::string channelName) {
    // TODO: log not implemented
    OmniLog.i(INTER_CORRECT_WATCH, TAG, "Clear channel resource, channelName = " + channelName);
    std::lock_guard<std::mutex> lock(mutex_);
    if (destroyed_) {
        return;
    }
    user_map_.erase(channelName);
    media_map_.erase(channelName);
}

void InterCorrectionManager::ClearAllResource() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (destroyed_) {
        return;
    }
    action_map_.clear();
    user_map_.clear();
    media_map_.clear();
}




}

