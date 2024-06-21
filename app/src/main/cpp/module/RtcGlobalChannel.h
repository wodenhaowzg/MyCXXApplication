//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALCHANNEL_H
#define MYCXXAPPLICATION_RTCGLOBALCHANNEL_H


class RtcGlobalChannel {

public:

    long long GetOwnerId();

    bool IsJoinedChannel();

private:
    long long owner_id_;
};

#endif //MYCXXAPPLICATION_RTCGLOBALCHANNEL_H