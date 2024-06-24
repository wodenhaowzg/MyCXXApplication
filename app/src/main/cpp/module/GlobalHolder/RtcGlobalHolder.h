//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALHOLDER_H
#define MYCXXAPPLICATION_RTCGLOBALHOLDER_H


#include <mutex>
#include "IOmniRtcDefines.h"
#include "RtcGlobalChannel.h"
#include "RtcGlobalAudio.h"
#include "RtcGlobalVideo.h"
#include "AVStreamPublishHandler.h"

class RtcGlobalHolder {

private:
    RtcGlobalHolder() {
    }

public:
    static RtcGlobalHolder *GetInstance();

    /**
     * 获取应用 APP ID
     *
     * @return 返回 APP ID
     */
    const std::string &GetAppId() const;

    /**
     * 获取全局下频道相关数据/状态的持有者对象
     *
     * @return 返回持有者对象
     */
    RtcGlobalChannel *getGlobalChannel();

    /**
     * 获取全局下音频相关数据/状态的持有者对象
     *
     * @return 返回持有者对象
     */
    RtcGlobalAudio *getGlobalAudio();

    /**
     * 获取全局下视频相关数据/状态的持有者对象
     *
     * @return 返回持有者对象
     */
    RtcGlobalVideo *getGlobalVideo();

    RTCEngine::AVStreamPublishHandler &getAVStreamPublishHandler();

    /**
     * 设置应用 APP ID
     */
    void SetAppId(const std::string &app_id);

    /**
     * 设置频道模式
     */
    void SetChannelProfile(RtcChannelProfile &profile);

private:
    static void initSingleton();

    void Initialize();

    RtcGlobalChannel global_channel_;
    RtcGlobalAudio global_audio_;
    RtcGlobalVideo global_video_;
    RTCEngine::AVStreamPublishHandler global_publish_handler_;

    std::string app_id_;
    RtcChannelProfile channel_profile_;

    static RtcGlobalHolder *instance_;
    static std::once_flag once_flag_;
};

#endif // MYCXXAPPLICATION_RTCGLOBALHOLDER_H