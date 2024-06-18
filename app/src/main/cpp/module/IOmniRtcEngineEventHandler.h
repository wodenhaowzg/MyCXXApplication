//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_IOMNIRTCENGINEEVENTHANDLER_H
#define MYCXXAPPLICATION_IOMNIRTCENGINEEVENTHANDLER_H

#include "IOmniRtcDefines.h"

class OmniRtcEngineEventHandler {

public:

    virtual void onError(int errorType) = 0;

    virtual void onConnectionLost() = 0;

    virtual void onReconnectServerFailed() = 0;

    virtual void onReconnectServerSucceed() = 0;

    virtual void onReportPolicy() = 0;

    virtual void onRtcLogReport() = 0;

    virtual void onLocalAudioStats(const LocalAudioStats &stats) = 0;

    virtual void onLocalVideoStats(const LocalVideoStats &stats) = 0;

    virtual void onRtcStats(const RtcStats &stats) = 0;
};

#endif //MYCXXAPPLICATION_IOMNIRTCENGINEEVENTHANDLER_H