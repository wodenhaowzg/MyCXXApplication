//
// Created on 2024/6/22.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCUSERMANAGER_H
#define CORERTCPROJECT_RTCUSERMANAGER_H

#include "RtcBaseManager.h"
#include "RtcEngineDefines.h"
#include "optional.h"
#include <cstdint>

namespace RTCEngine {

struct RtcUser {
    public:
        std::string channel_name;
        int64_t user_id;
        RtcClientRole identity;
    
        bool is_link_anchor; // 跨房间连麦
        int64_t link_room_id; // 跨房间连麦
        bool cross_room_user; // 纯饮品跨房间连麦
    
        bool timestamp_trusted;
        bool video_first_report_decoded;
};

class RtcUserManager : public RtcBaseManager {
    public:
        RtcUserManager(std::string channelName);
        virtual ~RtcUserManager();
    
        int64_t GetOwnerId() { return owner_id_; }
        void SetOwnerId(int64_t ownerId) { owner_id_ = ownerId; }

        // RtcBaseManager
        virtual void ClearResource() override ;
    
        void PutOrUpdateUser(RtcUser &rtcUser);
        void DelUser(int64_t userId);
        Optional<RtcUser> GetUser(int64_t userId);
    
        // TODO : unused.
        std::vector<RtcUser> GetUsers();
    
        bool IsUserExists(int64_t userId);
    
        void UpdateRole(int64_t userId, RtcClientRole role);
        void UpdateVideoFirstReportDecoded(int64_t userId);
    
    private:
        int64_t owner_id_;
        std::unordered_map<int64_t, RtcUser> user_map_;
        std::mutex mutex_;
};

}

#endif //CORERTCPROJECT_RTCUSERMANAGER_H
