//
// Created by ZaneWang on 2024/6/19.
//

#ifndef MYCXXAPPLICATION_RTCENGINEDEFINES_H
#define MYCXXAPPLICATION_RTCENGINEDEFINES_H

enum RtcChannelProfile {

    /**
    * 通信频道模式,申请发言服务器自动同意
    */
    CHANNEL_PROFILE_COMMUNICATION = 0,
    /**
     * 直播频道模式,申请发言主播需同意
     */
    CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
    /**
     * 游戏频道模式
     */
    CHANNEL_PROFILE_GAME_FREE_MODE = 2
};

#endif //MYCXXAPPLICATION_RTCENGINEDEFINES_H