//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCCHANNELINFOMODEL_H
#define CORERTCPROJECT_RTCCHANNELINFOMODEL_H

#include "RtcEngineDefines.h"
#include <string>
#include <chrono>
#include <ctime>

namespace RTCEngine {

// TODO : should be replaced with utility function
int64_t getSystemTimestamp() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();
    
    // 转换为time_t类型（UNIX时间戳）
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // 将当前时间点转换为可以表示自纪元开始的持续时间
    auto duration = now.time_since_epoch();

    // 转换为毫秒数
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    return millis;
}

// TODO: should be defined somewhere
enum ConnectState {
    CONNECTION_STATE_DISCONNECTED = 1,  // 网络连接断开
    CONNECTION_STATE_CONNECTING = 2,    // 建立网络连接中
    CONNECTION_STATE_CONNECTED = 3,     // 网络已连接
    CONNECTION_STATE_RECONNECTING = 4,  // 重新建立网络连接中
    CONNECTION_STATE_FAILED = 5,        // 网络连接失败
};

enum RtcChannelState {
    RTC_CHANNEL_JOINING = 1,
    RTC_CHANNEL_JOINED = 2,
    RTC_CHANNEL_LEAVE = 3,
};

struct RtcChannelInfoModel {
    public:
        std::string channel_name;
        std::string app_id = "";
        std::string token;
        int64_t user_id;

        RtcChannelState channel_state = RTC_CHANNEL_LEAVE;
        RtcClientRole client_role = CLIENT_ROLE_AUDIENCE; // 对齐 agora 退房间不复位
        ConnectState connect_state = CONNECTION_STATE_DISCONNECTED;

        int64_t join_channel_timestamp;
        int64_t joined_channel_timestamp;
        
        RtcClientRole last_client_role;
        bool reset_role;
        
        bool auto_subscribe_audio = true;
        bool auto_subscribe_video = true;

        void SetRole(RtcClientRole role) {
            last_client_role = client_role;
            client_role = role;
        }

        void Reset() {
            channel_state = RTC_CHANNEL_LEAVE;
            token = "";
            user_id = 0;
            last_client_role = CLIENT_ROLE_AUDIENCE;
            reset_role = false;
            join_channel_timestamp = 0;
            joined_channel_timestamp = 0;
            auto_subscribe_audio = true;
            auto_subscribe_video = true;
            connect_state = CONNECTION_STATE_DISCONNECTED;
        }
};

}

#endif //CORERTCPROJECT_RTCCHANNELINFOMODEL_H
