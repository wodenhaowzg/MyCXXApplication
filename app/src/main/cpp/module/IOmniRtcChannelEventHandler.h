//
// Created on 2024/6/15.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CORERTCPROJECT_IOMNIRTCCHANNELEVENTHANDLER_H
#define CORERTCPROJECT_IOMNIRTCCHANNELEVENTHANDLER_H

#include <string>
#include <vector>

#include "IOmniRtcDefines.h"

class OmniRtcChannelEventHandler {

public:
    virtual ~OmniRtcChannelEventHandler() {}

    /**
     * 加入频道成功回调
     * <p/>
     * App 调用 joinChannel API 加入频道时，如果成功则触发此回调。
     * <p/>
     * 该回调表示 App 已经成功登入服务器，并且成功分配了频道 ID 和用户 ID。频道 ID 和用户 ID 分配是根据 joinChannel API 中指定的。
     *
     * @param channel 频道名称。
     * @param uid 用户ID。
     * @param elapsed 从 joinChannel 开始到发生此事件过去的时间（毫秒)。
     */
    virtual void onJoinChannelSuccess(const std::string &channel, long uid, int elapsed) = 0;

    /**
     * 成功重新加入频道回调。
     * <p/>
     * 有时候由于网络原因，客户端可能会和服务器失去连接，SDK 会进行自动重连，自动重连成功后触发此回调方法。
     *
     * @param channel 频道名。
     * @param uid 用户 ID。用户 ID 是 joinChannel API 中指定的。
     * @param elapsed 从开始重连到重连成功的时间（毫秒）。
     */
    virtual void onRejoinChannelSuccess(const std::string &channel, long uid, int elapsed) = 0;

    /**
     * 离开频道回调
     * <p/>
     * App 调用 leaveChannel API 离开频道，当离开频道完成时，触发此回调。
     * <p/>
     * 该回调表示已成功离开频道，在该回调中，App 可以得到此次通话的总通话时长、SDK 收发数据的流量等信息。
     *
     * @param stats 此次直播/通话相关的统计信息。
     */
    virtual void onLeaveChannel(const RtcStats &stats) = 0;

    /**
     * 本地用户角色切换回调
     * <p/>
     * 该回调由本地用户在加入频道成功后，调用 setClientRole 切换用户角色所触发，SDK 提示 App 本地用户的角色已切换完成，例如从 CLIENT_ROLE_BROADCASTER(观众) 切换为 CLIENT_ROLE_BROADCASTER(副播) ，或从副播身份切换为观众。
     * <p/>
     * 此时频道内的远端用户不会触发该回调，但可能会收到以下两个回调的其中一个：1、onUserJoined：本地角色由观众改变为副播。2、onUserOffline：本地角色由副播改变为观众。
     *
     * @param uid 本地用户ID。
     * @param userRole 切换后的角色。
     */
    virtual void onClientRoleChanged(long uid, int userRole) = 0;

    /**
     * Token 服务即将过期回调
     * <p/>
     * 在 App 调用 joinChannel 时如果指定了 Token 参数，由于 Token 具有一定的时效，在通话/直播过程中如果 Token 即将失效，SDK 会根据 Token 时效时间取六分之一的值(例如 Token 的时效性为 60 秒，则取 10 秒，最大值为 60 秒，最小值为 2 秒)，提前触发该回调，提醒 App 更新 Token。
     * <p/>
     * 当 App 收到该回调时，用户需要重新在服务端生成新的 Token，然后调用 renewToken(...) API 将新的 Token 传给 SDK 重新校验。
     */
    virtual void onTokenPrivilegeWillExpire() = 0;

    /**
     * Token 已过期
     */
    virtual void onRequestToken() = 0;

    /**
     * SDK 收到强制离开频道回调。
     * <p/>
     * 该回调表示服务器要求 SDK 将本地用户从当前频道中移除，SDK 不会主动调用 leaveChannel，需要 App 主动调用 leaveChannel 并提示用户已离开频道以及离开的原因。例如：CHANNEL_PROFILE_LIVE_BROADCASTING(直播模式) 下，主播有权限将频道内某个用户请离频道，此时被请离的用户会接收到该回调，原因为 ERROR_KICK_BY_HOST(101) 。
     * <p/>
     * 该回调触发的前提条件为本地用户加入频道成功后。
     *
     * @param uid 本地用户 ID。
     * @param reason 本地用户被服务器请出的原因，详细定义参考 Constants 类。
     */
    virtual void onUserKicked(long uid, int reason, int kickTime) = 0;

    /**
     * 用户加入频道回调
     * <p/>
     * 该回调表示有新的用户加入频道，并返回该用户的 ID 以及角色身份。在本地用户加入频道前，频道中已存在的主播或副播用户，本地用户在加入频道成功后也由该回调提示给 App。
     * <p/>
     * 该回调在以下情况下会被触发：1、远端用户(副播)调用 joinChannel 方法成功加入频道。2、远端用户(观众)加入频道后调用 setClientRole 将用户角色改变为副播。
     * <p/>
     * 使用注意：<br/>
     * 1、CLIENT_ROLE_AUDIENCE(观众) 对于频道内其他人来说是不可见，即以观众的身份加入频道，频道内其他用户不会触发 onUserJoined 回调。
     *
     * @param uid 加入频道的用户ID。
     * @param identity 加入频道的用户的身份，副播或观众。
     * @param elapsed 从 joinChannel 开始到发生此事件过去的时间（毫秒)。
     */
    virtual void onUserJoined(long uid, int identity, int elapsed) = 0;

    /**
     * 用户离开频道回调
     * <p/>
     * 该回调表示有用户离开频道，并返回该用户的 ID 以及离开的原因。
     * <p/>
     * 使用注意：<br/>
     * 1、CLIENT_ROLE_AUDIENCE(观众) 对于频道内其他人来说是不可见，即以观众的身份加入频道，离开频道时，频道内其他用户也不会触发 onUserOffline 。
     *
     * @param uid 离开频道的用户ID。
     * @param reason 用户离开频道的原因，有以下几种：1、USER_OFFLINE_NORMAL(201)：用户主动离开频道。2、USER_OFFLINE_TIMEOUT(202)：用户网络不好，超时离开。3、USER_OFFLINE_LINKCLOSE(203)：用户网络断线离开。
     */
    virtual void onUserOffline(long uid, int reason) = 0;

    /**
     * 该回调表示本地用户收到了远端用户调用 sendStreamMessage 方法发送的流消息。
     *
     * @param uid 发送消息的用户 ID。
     * @param streamId 接收到的消息的 Stream ID。
     * @param data 接收到的数据。
     */
    virtual void onStreamMessage(long uid, int streamId, const std::vector<unsigned char> &data) = 0;

    /**
     * 通话中每个用户的网络上下行 last mile 质量报告回调。
     * <p/>
     * 该回调描述每个用户在通话中的 last mile 网络状态，其中 last mile 是指设备到边缘服务器的网络状态。该回调每 2 秒触发一次。如果远端有多个用户，该回调每 2 秒会被触发多次。
     *
     * @param uid 用户 ID。表示该回调报告的是持有该 ID 的用户的网络质量。
     * @param txQuality 该用户的上行网络质量。
     * @param rxQuality 该用户的下行网络质量。
     */
    virtual void onNetworkQuality(long uid, int txQuality, int rxQuality) = 0;

    // ------------------------ 音频相关 --------------------

    /**
     * 已发布本地音频首帧回调。
     *
     * @param elapsed 从调用 joinChannel [2/2] 方法到触发该回调的时间间隔（毫秒）。
     */
    virtual void onFirstLocalAudioFrame(int elapsed) = 0;

    /**
     * 已接收远端音频首帧回调。
     *
     * @param uid 发送音频帧的远端用户的用户 ID。
     * @param mediaId 用户音频流 ID
     * @param elapsed 从本地用户调用 joinChannel [2/2] 直至该回调触发的延迟，单位为毫秒。
     */
    virtual void onFirstRemoteAudioFrame(long uid, const std::string &mediaId, int elapsed) = 0;

    /**
     * 音频订阅状态发生改变回调。
     *
     * @param uid 远端用户的 ID。
     * @param mediaId 用户音频流 ID。
     * @param oldState 之前的订阅状态。
     * @param newState 当前的订阅状态。
     * @param elapseSinceLastState 两次状态变化时间间隔（毫秒）。
     */
    virtual void onAudioSubscribeStateChanged(long uid, const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) = 0;

    /**
     * 音频发布状态改变回调。
     *
     * @param mediaId 用户音频流 ID。
     * @param oldState 之前的订阅状态。
     * @param newState 当前的订阅状态。
     * @param elapseSinceLastState 两次状态变化时间间隔（毫秒）。
     */
    virtual void onAudioPublishStateChanged(const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) = 0;

    /**
     * 通话/直播中远端音频流统计信息的回调
     * <p/>
     * 该回调描述远端用户在通话/直播中端到端的音频流统计信息，针对每个远端用户每 2 秒触发一次。如果远端同时存在多个，该回调每 2 秒会被触发多次。
     *
     * @param stats 远端音频相关的统计信息，主要的信息如下：1、mUid：远端用户的 ID ，描述音频流是对应哪个远端用户。2、mReceivedBitrate：下行的码率(kbps) 。3、mAudioLossRate：下行的丢包率(0.xx%) 。
     */
    virtual void onRemoteAudioStats(const RemoteAudioStats &stats) = 0;

    // ------------------------ 视频相关 --------------------

    /**
     * 已发布本地视频首帧回调。
     *
     * @param mediaId 本地用户视频流 ID。
     * @param elapsed 从本地用户调用 joinChannel 直至该回调触发的延迟，单位为毫秒。
     */
    virtual void onFirstLocalVideoFramePublished(const std::string &mediaId, int elapsed) = 0;

    /**
     * 本地/远端用户开/关视频模块的回调
     * <p/>
     * 该回调表示本地/远端用户调用 enableLocalVideo，enableVideo，disableVideo API 等打开/关闭本地视频功能。关闭视频功能是指该用户只能进行语音通话，不能显示、发送自己的视频。
     * <p/>
     * 使用注意：<br/>
     * 1、无需多视频源功能，可忽略此回调。
     *
     * @param uid 本地/远端用户 ID，提示是哪个用户的视频流。
     * @param mediaId 本地/远端用户的视频流 ID，提示是用户的哪个视频设备的视频流。
     * @param enabled true：代表用户启用了视频功能，false：代表用户关闭了视频功能
     */
    virtual void onUserEnableVideo(long uid, const std::string &mediaId, bool enabled) = 0;

    /**
     * 本地视频状态发生改变回调。
     * <p/>
     * 本地视频的状态发生改变时，SDK 会触发该回调返回当前的本地视频状态。你可以通过该回调了解当前视频的状态以及出现故障的原因，方便排查问题。
     *
     * @param mediaId 本地用户视频流 ID。
     * @param state {@link com.wushuangtech.expansion.api.Constants#LOCAL_VIDEO_STREAM_STATE_STOPPED}
     * @param error {@link com.wushuangtech.expansion.api.Constants#LOCAL_VIDEO_STREAM_ERROR_OK}
     */
    virtual void onLocalVideoStateChanged(const std::string &mediaId, int state, int error) = 0;

    /**
     * 远端视频状态发生改变回调。
     *
     * @param uid 发生视频状态改变的远端用户 ID。
     * @param mediaId 远端用户视频流 ID。
     * @param state 远端视频流状态。 {@link com.wushuangtech.expansion.api.Constants#REMOTE_VIDEO_STATE_STOPPED}
     * @param reason 远端视频流状态改变的具体原因。 {@link com.wushuangtech.expansion.api.Constants#REMOTE_VIDEO_STATE_REASON_INTERNAL}
     * @param elapsed 从本地用户调用 joinChannel 直至该回调触发的延迟，单位为毫秒。
     */
    virtual void onRemoteVideoStateChanged(long uid, const std::string &mediaId, int state, int reason, int elapsed) = 0;

    /**
     * 视频发布状态改变回调。
     *
     * @param mediaId 远端用户视频流 ID。
     * @param oldState 之前的发布状态。
     * @param newState 当前的发布状态。
     * @param elapseSinceLastState 两次状态变化时间间隔（毫秒）。
     */
    virtual void onVideoPublishStateChanged(const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) = 0;

    /**
     * 视频订阅状态改变回调。
     *
     * @param mediaId 远端用户视频流 ID。
     * @param oldState 之前的订阅状态。
     * @param newState 当前的订阅状态。
     * @param elapseSinceLastState 两次状态变化时间间隔（毫秒）。
     */
    virtual void onVideoSubscribeStateChanged(long uid, const std::string &mediaId, int oldState, int newState, int elapseSinceLastState) = 0;


    /**
     * 远端用户视频播放卡顿回调。
     * <p/>
     * SDK 会在收到两帧间隔大于500毫秒时触发该回调。
     *
     * @param uid 发送该帧视频的远端用户ID 。
     * @param state 0: 表示卡顿开始，1：表示卡顿结束。
     * @param timestampInMs 事件发生时的时间戳。
     */
    virtual void onVideoBufferingStateChanged(long uid, const std::string &mediaId, int state, long timestampInMs) = 0;

    /**
     * 通话/直播中远端视频流统计信息的回调，
     * <p/>
     * 该回调描述远端用户在通话/直播中端到端的视频流统计信息，针对每个远端用户每 2 秒触发一次。如果远端同时存在多个，该回调每 2 秒会被触发多次。
     *
     * @param stats 远端视频相关的统计信息。
     */
    virtual void onRemoteVideoStats(const RemoteVideoStats &stats) = 0;
};

#endif // CORERTCPROJECT_IOMNIRTCCHANNELEVENTHANDLER_H
