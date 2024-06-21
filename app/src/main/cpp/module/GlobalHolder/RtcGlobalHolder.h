//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALHOLDER_H
#define MYCXXAPPLICATION_RTCGLOBALHOLDER_H


#include <mutex>
#include "RtcEngineDefines.h"
#include "RtcGlobalChannel.h"
#include "RtcGlobalAudio.h"
#include "RtcGlobalVideo.h"

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
    std::string GetAppId() const;

    /**
     * 获取全局下频道相关数据/状态的持有者对象
     *
     * @return 返回持有者对象
     */
    const RtcGlobalChannel &getGlobalChannel();

    /**
     * 获取全局下音频相关数据/状态的持有者对象
     *
     * @return 返回持有者对象
     */
    const RtcGlobalAudio &getGlobalAudio();

    /**
     * 获取全局下视频相关数据/状态的持有者对象
     *
     * @return 返回持有者对象
     */
    const RtcGlobalVideo &getGlobalVideo();

    /**
     * 设置应用 APP ID
     */
    void SetAppId(const std::string &app_id);

private:
    static void initSingleton();

    void Initialize();

    RtcGlobalChannel global_channel_;
    RtcGlobalAudio global_audio_;
    RtcGlobalVideo global_video_;
    std::string app_id_;

    static RtcGlobalHolder *instance_;
    static std::once_flag once_flag_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALHOLDER_H