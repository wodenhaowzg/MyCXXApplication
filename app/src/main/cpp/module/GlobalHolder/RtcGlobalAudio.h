//
// Created by ZaneWang on 2024/6/20.
//

#ifndef MYCXXAPPLICATION_RTCGLOBALAUDIO_H
#define MYCXXAPPLICATION_RTCGLOBALAUDIO_H

#include <string>

class RtcGlobalAudio {

public:
    /**
     * 获取音频上行流 ID
     *
     * @return 返回音频上行流 ID
     */
    std::string GetAudioUplinkMediaId();
};

#endif // MYCXXAPPLICATION_RTCGLOBALAUDIO_H