//
// Created on 2024/6/19.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCCHANNELINFOMODEL_H
#define CORERTCPROJECT_RTCCHANNELINFOMODEL_H

#include <string>

namespace RTCEngine {

// TODO: should be defined somewhere
enum ClientRole {
    CLIENT_ROLE_NULL = 0,
    CLIENT_ROLE_BROADCASTER = 1,    // TAL version : 好未来用这个名字
    CLIENT_ROLE_AUDIENCE = 2,       // TAL version : 改成2了
    CLIENT_ROLE_BROADCASTER2 = 3,   // TAL version : 原来是2，这里先改个别的值，好未来不用
};

// TODO: should be defined somewhere
enum ConnectState {
    CONNECTION_STATE_DISCONNECTED = 1,  // 网络连接断开
    CONNECTION_STATE_CONNECTING = 2,    // 建立网络连接中
    CONNECTION_STATE_CONNECTED = 3,     // 网络已连接
    CONNECTION_STATE_RECONNECTING = 4,  // 重新建立网络连接中
    CONNECTION_STATE_FAILED = 5,        // 网络连接失败
};

enum RTCChannelState {
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

        RTCChannelState channel_state = RTC_CHANNEL_LEAVE;
        ClientRole client_role = CLIENT_ROLE_AUDIENCE; // 对齐 agora 退房间不复位
        ConnectState connect_state = CONNECTION_STATE_DISCONNECTED;

        int64_t join_channel_timestamp;
        int64_t joined_channel_timestamp;
        
        std::string src_channel_name = ""; // 转推功能，源频道名称
        bool is_media_relay;

        ClientRole last_client_role;
        bool reset_role;
        
        bool auto_subscribe_audio = true;
        bool auto_subscribe_video = true;

        void SetRole(ClientRole role) {
            last_client_role = client_role;
            client_role = role;
        }

        void Reset() {
            channel_state = RTC_CHANNEL_LEAVE;
            token = "";
            user_id = 0;
            last_client_role = CLIENT_ROLE_NULL;
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
