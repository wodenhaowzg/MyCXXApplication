//
// Created on 2024/6/20.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_USERDEVICECONFIG_H
#define CORERTCPROJECT_USERDEVICECONFIG_H

#include "RtcEngineDefines.h"
#include <cstdint>
#include <string>

namespace RTCEngine {

enum DeviceType {
    DEVICE_TYPE_AUDIO = 1,
    DEVICE_TYPE_VIDEO = 2,
};

struct UserDeviceConfig {
    public:
        DeviceType device_type;
        std::string channel_name;
        int64_t user_id;
        std::string device_id;
        std::string dual_device_id = "";
        int width;
        int height;
        int video_type;
        int video_stream_type = VIDEO_STREAM_HIGH; // 大小流
        bool video_stream_enabled;  // 该设备大流是否启用，本地控制
        bool in_use; // 该设备大流是否启用，远端控制
        bool dual_in_use; 
        bool default_dev; // 该设备当前是否是用户的默认视频设备
        bool muted;
        bool muted_by_self; // 是否本地将此视频设备 mute 掉
        bool open_big_video; // 该设备大流的开/关标识
        bool open_small_video; // 该设备小流的开/关标识
        bool disappear; // 是否已经不存在，针对 pc 换视频设备，老的会直接没有
        int64_t dev_opened_ts; // 打开视频设备的时间戳
    
        // 音频相关字段
        bool audio_muted;
        int audio_level;
        int audio_full_range_level;
        int audio_jitter_ms;
        bool audio_first_pkt_received; // 是否接收到该用户的音频第一帧
    
        /**
         * 音频设备构造
         *
         * @param channelName 频道名。
         * @param uid         用户 ID。
         * @param deviceId    设备 ID。
         */
        UserDeviceConfig(std::string channelName, int64_t userId, std::string deviceId) {
            device_type = DEVICE_TYPE_AUDIO;
            channel_name = channelName;
            user_id = userId;
            in_use = true;
        }
    
        /**
         * 视频设备构造
         *
         * @param channelName   频道名。
         * @param uid           用户 ID。
         * @param deviceId      设备 ID。
         * @param deviceEnabled 是否启用。
         * @param isDefaultDev  是否默认设备。
         */
        UserDeviceConfig(std::string channelName, int64_t userId, std::string deviceId, bool deviceEnabled, bool isDefaultDev) {
            device_type = DEVICE_TYPE_VIDEO;
            channel_name = channelName;
            user_id = userId;
            device_id = deviceId;
            in_use = deviceEnabled;
            default_dev = isDefaultDev;
        }
    
        bool UpdateDevice(const UserDeviceConfig &other) {
            bool updated = false;
            if (in_use != other.in_use 
                || default_dev != other.default_dev 
                || width != other.width
                || height != other.height
                || video_type != other.video_type
                || (!other.dual_device_id.empty() && dual_device_id != other.dual_device_id)
                || dual_in_use != other.dual_in_use
                || dev_opened_ts != other.dev_opened_ts) {
            
                in_use = other.in_use;
                default_dev = other.default_dev;
                width = other.width;
                height = other.height;
                video_type = other.video_type;
                if (!other.dual_device_id.empty()) {
                    dual_device_id = other.dual_device_id;
                }
                dual_in_use = other.dual_in_use;
                dev_opened_ts = other.dev_opened_ts;
            
                updated = true;
            }
            return updated;
        }
    
        void UpdateDeviceOpenStatus(bool bigOpened, bool smallOpened, int64_t openedTimestamp) {
            open_big_video = bigOpened;
            open_small_video = smallOpened;
            dev_opened_ts = openedTimestamp;
        }
};

}

#endif //CORERTCPROJECT_USERDEVICECONFIG_H
