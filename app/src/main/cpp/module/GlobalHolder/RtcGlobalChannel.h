//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALCHANNEL_H
#define MYCXXAPPLICATION_RTCGLOBALCHANNEL_H

#include <map>

class RtcGlobalChannel {

public:

    /**
     * 获取自己的 uid
     *
     * @return 返回自己的 uid
     */
    long long GetOwnerId();

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

private:
    long long owner_id_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALCHANNEL_H