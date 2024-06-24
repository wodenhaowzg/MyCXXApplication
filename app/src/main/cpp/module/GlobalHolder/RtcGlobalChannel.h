//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALCHANNEL_H
#define MYCXXAPPLICATION_RTCGLOBALCHANNEL_H


#include <mutex>
#include <map>
#include <string>

#include "IOmniRtcDefines.h"
#include "RtcChannelManager.h"

class RtcGlobalChannel {

public:
    /**
     * RTC 引擎销毁
     */
    void destroy();

    /**
     * 获取自己的 uid
     *
     * @return 返回自己的 uid
     */
    long long GetOwnerId();

    /**
     * 获取 ConnectId
     */
    std::string GetConnectId();

    /**
     * 判断是否已加入频道中
     *
     * @return true 代表已加入一个或多个频道，false 代表未加入任何频道
     */
    bool IsJoinedChannel();

    /**
     * 设置自己的 uid
     * @param owner_id 自己的 uid
     */
    void SetOwnerId(long long owner_id); // TODO 光哥，设置自己 uid

    /**
     * 设置哪个房间持有主播身份
     *
     * @param channelName 房间名
     * @param role 用户身份
     */
    int SetRoleForBroadcaster(std::string channel_name, RtcClientRole role);

    /**
     * 设置 ConnectId
     *
     * @param connectId 房间链路 ID
     */
    void SetConnectId(std::string &connect_id);

    /**
     * 创建一个新的频道对象
     *
     * @param channel_name 频道名称
     */
    IOmniRtcChannel *CreateRtcChannel(std::string channel_name);

    /**
     * 销毁指定的频道对象
     *
     * @param channel_name 频道名称
     */
    void DestroyRtcChannel(std::string channel_name);

private:
    std::map<std::string, RTCEngine::RtcChannelManager *> channel_map_;

    long long owner_id_;
    std::string connect_id_;
    std::string channel_name_hold_broadcaster_;

    std::mutex mutex_;
};

#endif // MYCXXAPPLICATION_RTCGLOBALCHANNEL_H