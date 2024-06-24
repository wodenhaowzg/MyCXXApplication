//
// Created on 2024/6/20.
// author : zhangguang@tal.com

#ifndef CORERTCPROJECT_RTCDEVICEMANAGER_H
#define CORERTCPROJECT_RTCDEVICEMANAGER_H

#include "RtcBaseManager.h"
#include "UserDeviceConfig.h"
#include "optional.h"

#include <cstdint>
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
        std::vector<UserDeviceConfig> ClearUserDeviceAvailableStatus(int64_t userId);
    
        bool UpdateDeviceOpenStatus(int64_t userId, std::string deviceId, bool bigOpened, bool smallOpened, int64_t openTimestamp);
    
        /**
         * 获取指定用户的默认设备信息对象。
         * <p/>
         * 该方法仅限于读取，返回的视频设备信息集合为拷贝副本，不能执行修改操作。
         *
         * @param userId 用户 ID。
         * @return 返回该用户的 UserDeviceConfig 拷贝对象。
         */
        Optional<UserDeviceConfig> GetDefaultDeviceConfig(int64_t userId);
    
        /**
         * 获取指定的用户设备信息对象集合。
         * <p/>
         * 该方法仅限于读取，返回的视频设备信息集合为拷贝副本，不能执行修改操作。
         *
         * @param userId 用户 ID。
         * @return 返回一个该用户所有的 UserDeviceConfig 对象拷贝集合。
         */
        std::vector<UserDeviceConfig> GetDeviceConfigsByUserId(int64_t userId);
    
        /**
         * 获取指定的用户设备信息对象。
         * <p/>
         * 该方法仅限于读取，返回的视频设备信息对象为拷贝副本，不能执行修改操作。
         *
         * @param userId    用户 ID。
         * @param deviceId  用户设备 ID。
         * @return 返回一个指定的用户设备信息拷贝对象。
         */
        Optional<UserDeviceConfig> GetDeviceConfigByDeviceId(int64_t userId, std::string deviceId);
    
        /**
         * 获取该频道内所有用户的所有设备信息。
         * <p/>
         * 该方法仅限于读取，返回的视频设备信息集合为拷贝副本，不能执行修改操作，并且比较耗时，避免频繁调用。
         *
         * @return 返回该频道内所有用户的所有视频设备信息集合的拷贝副本。
         */
        std::unordered_map<int64_t, std::vector<UserDeviceConfig>> GetDeviceConfigsForAll();
    
        /**
         * 更新指定的远端用户的音频流停止/接收状态。
         *
         * @param userId      远端用户 ID。
         * @param deviceId 远端用户音频流 ID。
         * @param muted    true 停止接收该音频流，false 恢复接收该音频流。
         */
        void UpdateAudioDeviceMuted(int64_t userId, std::string deviceId, bool muted);
    
        /**
         * 更新指定的远端用户的音频流播放音量。
         *
         * @param userId        远端用户 ID。
         * @param deviceId   远端用户音频流 ID。
         * @param audioLevel 当前接收该音频流的播放音量值，0 ~ 255。
         */
        void UpdateAudioDeviceVolume(int64_t userId, std::string deviceId, int audioLevel);
    
        /**
         * 更新指定的远端用户的音频流 jitter 缓冲区的最大值。
         *
         * @param userId      远端用户 ID。
         * @param deviceId  远端用户音频流 ID。
         * @param jitterMs 当前音频 jitter 缓冲区的最大值。
         */
        void UpdateAudioDeviceJitterMs(int64_t userId, std::string deviceId, int jitterMs);
    
        /**
         * 更新指定的远端音频流数据的第一帧的接收状态。
         *
         * @param userId        远端用户 ID。
         * @param deviceId   远端用户音频流 ID。
         * @param received true 已接收到该音频流的第一帧音频数据，false 未接收到该音频流的第一帧音频数据。
         */
        void UpdateAudioDeviceFirstAudioRecv(int64_t userId, std::string deviceId, bool received);
    
        /**
         * 更新本地用户主动停止/恢复接收指定的远端用户的视频流状态。
         * <p/>
         * 本地用户通过调用 {@link EnterConfApi#muteRemoteVideo(String, long, String, boolean)} 接口，实现停止/恢复接收该远端用户的视频流。
         *
         * @param uid      远端用户 ID。
         * @param deviceId 远端用户视频流 ID。
         * @param muted    true 停止接收该视频流，false 恢复接收该视频流。
         */
        void UpdateVideoDeviceMuteBySelf(int64_t userId, std::string deviceId, bool muted);
    
        /**
         * 更新指定的远端用户的视频流停止/恢复发送状态。
         * <p/>
         * 从底层接收该远端用户的视频流停止/恢复发送状态，对应回调为 RoomJni.OnRemoteVideoMuted(String channelName, long uid, String mediaId, boolean muted)。
         *
         * @param uid      远端用户 ID。
         * @param deviceId 远端用户视频流 ID。
         * @param muted    true 停止接收该视频流，false 恢复接收该视频流。
         */
        void UpdateVideoDeviceMuted(int64_t userId, std::string deviceId, bool muted);
    
    private:
        UserDeviceConfig* getDeviceInternal(int64_t userId, std::string deviceId);
    
    private:
        std::unordered_map<int64_t, std::vector<UserDeviceConfig>> user_device_map_;
};

}

#endif //CORERTCPROJECT_RTCDEVICEMANAGER_H
