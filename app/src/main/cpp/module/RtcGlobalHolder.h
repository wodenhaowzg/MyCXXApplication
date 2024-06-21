//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALHOLDER_H
#define MYCXXAPPLICATION_RTCGLOBALHOLDER_H


#include <mutex>
#include "RtcEngineDefines.h"
#include "RtcGlobalChannel.h"
#include "RtcGlobalVideo.h"

class RtcGlobalHolder {

private:
    RtcGlobalHolder() {
    }

public:
    static RtcGlobalHolder *GetInstance();

    const std::string &GetAppId() const;

    const RtcGlobalChannel &getChannelManager();

    const RtcGlobalVideo &getVideoManager();

    void SetAppId(const std::string &app_id);

private:
    static void initSingleton();

    void Initialize();

    RtcGlobalChannel channel_manager_;
    RtcGlobalVideo video_manager_;
    std::string app_id_;

    static RtcGlobalHolder *instance_;
    static std::once_flag once_flag_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALHOLDER_H