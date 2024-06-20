//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_INTERCORRECTIONMANAGER_H
#define CORERTCPROJECT_INTERCORRECTIONMANAGER_H

#include <map>
#include <unordered_map>
#include <mutex>

namespace RTCEngine {

class InterCorrectionManager {
    public:
        enum InterCorrectionType {
            INTER_CORRECT_TYPE_NORMAL = 1,
            INTER_CORRECT_TYPE_USER = 2,
            INTER_CORRECT_TYPE_MEDIA = 3,
        };
    
        struct InterCorrection {
            public:
                int64_t user_id;
                std::string media_id;
                std::string channel_name;
                InterCorrectionType type;
                int action;
                void* info;
                int64_t timestamp;
        
                std::string toString() {
                    // TODO: unfinished
                    return "InterCorrectionBean{" +
                        "userId=" + user_id +
                        "MediaId=" + media_id +
                        "mChannelName=" + mChannelName +
                        ", mType=" + mType +
                        ", mAction=" + mAction +
                        ", mInfo=" + mInfo +
                        ", mTimestamp=" + mTimestamp +
                        '}';
                }
        };
    
        InterCorrectionManager() = default;
        virtual ~InterCorrectionManager() = default;
    
        void AddInterCorrection(InterCorrection &interCorrection);
    
        Optional<InterCorrection> GetAndRemoveCachedInterCorrection(InterCorrection& interCorrection, bool remove);
        Optional<InterCorrection> FindCachedInterCorrection(InterCorrection& interCorrection);
    
        void ClearResource(std::string channelName);
        void ClearAllResource();
    
    private:
        void handleUserInterCorrection(InterCorrection &interCorrection);
        void handleUserMediaInterCorrection(InterCorrection &interCorrection);
    
    private:
        typedef std::map<int, InterCorrection> ActionKeyMap;
        ActionKeyMap action_map_;
        std::unordered_map<std::string, std::unordered_map<int64_t, ActionKeyMap>> user_map_;
        std::unordered_map<std::string, std::unordered_map<std::string, ActionKeyMap>> media_map_;
    
        bool destroyed_ = false;
        std::mutex mutex_;
};

}

#endif //CORERTCPROJECT_INTERCORRECTIONMANAGER_H
