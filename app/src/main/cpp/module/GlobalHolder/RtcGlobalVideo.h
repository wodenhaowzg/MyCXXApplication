//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALVIDEO_H
#define MYCXXAPPLICATION_RTCGLOBALVIDEO_H

#include <string>
#include "RtcGlobalChannel.h"

class RtcGlobalVideo {

public:
    void SetRtcGlobalChannel(RtcGlobalChannel &channel);

    /**
     * 获取视频上行流 ID
     *
     * @return 返回视频上行流 ID
     */
    std::string GetVideoUplinkMediaId();

    /**
     * 设置本地视频模块开/关
     *
     * @param enabled true 代表开启，false 代表关闭
     * @return true 代表状态更新成功，false 代表重复调用
     */
    bool SetLocalEnabled(bool enabled);

    /**
     * 设置视频上行流 ID
     *
     * @param mediaId 视频上行流 ID
     */
    void SetVideoUplinkMediaId(std::string &mediaId);

private:
    RtcGlobalChannel channel_manager_;
    std::string video_uplink_media_id_;
    std::string video_default_uplink_media_id_;
    bool video_local_enabled_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALVIDEO_H