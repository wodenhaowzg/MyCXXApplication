//
// Created by ZaneWang on 2024/6/18.
//

#ifndef MYCXXAPPLICATION_IOMNIRTCENGINEEVENTHANDLER_H
#define MYCXXAPPLICATION_IOMNIRTCENGINEEVENTHANDLER_H

#include "IOmniRtcDefines.h"

class OmniRtcEngineEventHandler {

public:
    /**
     * SDK 发生错误回调
     * <p/>
     * 该回调表示 SDK 运行时出现了错误，无法自动恢复，需要 App 干预或提示用户。例如：直播模式下，以副播/观众身份加入一个不存在的频道，SDK 会上报 ERROR_ENTER_ROOM_NOEXIST(-6) 错误，App 可以提示用户加入频道失败，并再次尝试或检查频道名称是否正确。
     *
     * @param errorType 错误码，详细定义参考 Constants 类。
     */
    virtual void onError(int errorType) = 0;

    /**
     * 网络连接丢失
     * <p/>
     * 该回调表示当前网络状态不佳，SDK 与服务器断开了连接，并正在尝试重连，App 可无需关注此回调。
     */
    virtual void onConnectionLost() = 0;

    /**
     * 网络连接中断
     * <p/>
     * 当网络异常断开后，SDK 将主动尝试重连，若在限定时间之内(默认90秒，App 可通过 setSignalTimeout API 设置变更)无法重连上服务器，SDK 会触发此回调通知 App ，App 在收到此回调后应该调用 leaveChannel 离开频道，服务器将会把该用户置为离线状态，并通知给频道内其他用户。
     * <p/>
     * 使用注意：<br/>
     * 1、在直播模式下，如果主播离线，服务器将会把频道置为不可用状态，并通知给频道内其他用户，其他用户会收到 onUserKicked 回调，错误码为 ERROR_KICK_BY_MASTER_EXIT(104) 。
     */
    virtual void onReconnectServerFailed() = 0;

    /**
     * 网络连接重连成功
     * <p/>
     * 当网络连接丢失后，SDK 将主动尝试重连，若在限定时间之内(默认90秒，App 可通过 setSignalTimeout API 设置变更)重连上服务器，SDK 会触发此回调通知 App 网络恢复正常。
     */
    virtual void onReconnectServerSucceed() = 0;

    /**
     * 配置下发内容上抛
     *
     * @param policy 配置内容
     */
    virtual void onReportPolicy() = 0;

    /**
     * RTC 日志上报
     *
     * @param level 日志等级
     * @param msg   日志内容
     */
    virtual void onRtcLogReport() = 0;

    /**
     * 通话/直播中本地音频流统计信息的回调
     * <p/>
     * 该回调描述本地设备发送音频流的统计信息，每 2 秒触发一次。
     *
     * @param stats 本地音频相关的统计信息，主要的信息如下：1、mSentBitrate：上行的码率(kbps) 。2、mAudioLossRate：上行的丢包率(0.xx%) 。
     */
    virtual void onLocalAudioStats(const LocalAudioStats &stats) = 0;

    /**
     * 通话/直播中本地视频流统计信息的回调
     * <p/>
     * 该回调描述本地设备发送视频流的统计信息，每 2 秒触发一次。
     *
     * @param stats 本地视频相关的统计信息，主要的信息如下：1、mSentBitrate：上行的码率(kbps) 。2、mSentFrameRate：上行的帧率(fps) 。3、mVideoLossRate：上行的丢包率(0.xx%) 。
     */
    virtual void onLocalVideoStats(const LocalVideoStats &stats) = 0;

    /**
     * 通话/直播运行的状态统计回调
     * <p/>
     * 该回调描述 SDK 在通话/直播过程中的运行状态统计信息，每 2 秒触发一次。
     *
     * @param stats 通话/直播中相关的统计信息：1、mTotalDuration: 通话时长（秒），累计值。2、mTxBytes: 发送字节数（bytes), 累计值。3、mRxBytes: 接收字节数（bytes), 累计值。4、mTxAudioKBitRate: 发送音频码率（kbps), 瞬时值。5、mTxVideoKBitRate: 发送视频码率（kbps), 瞬时值。6、mRxAudioKBitRate: 接收音频码率（kbps), 瞬时值。7、mRxVideoKBitRate:
     * 接收视频码率（kbps), 瞬时值。
     */
    virtual void onRtcStats(const RtcStats &stats) = 0;
};

#endif // MYCXXAPPLICATION_IOMNIRTCENGINEEVENTHANDLER_H