//
// Created on 2024/6/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CORERTCPROJECT_IOMNIRTCCHANNEL_H
#define CORERTCPROJECT_IOMNIRTCCHANNEL_H

#include "IOmniRtcChannelEventHandler.h"
#include "RtcEngineDefines.h"

struct ChannelMediaOptions {

    /**
     * 设置是否自动订阅所有音频流：true：自动订阅所有音频流。false：不自动订阅任何音频流。
     */
    bool auto_subscribe_audio = true;
    /**
     * 设置是否自动订阅所有视频流：true：自动订阅所有视频流。false：不自动订阅任何视频流。
     */
    bool auto_subscribe_video = true;
};

class IOmniRtcChannel {

public:
    /**
     * 设置频道事件句柄。
     * <p/>
     * 设置后，你可以通过 OmniRtcChannelEventHandler 回调监听对应频道内的事件、获取频道数据。
     *
     * @param eventHandler RtcChannel 对象的事件回调句柄。
     */
    virtual void SetRtcChannelEventHandler(OmniRtcChannelEventHandler *handler) = 0;

    /**
     * 获取频道事件句柄。
     * @return 返回频道事件句柄。
     */
    virtual OmniRtcChannelEventHandler *GetEventHandler() const = 0;

    /**
     * 设置用户角色。
     * <p/>
     * 该方法在加入频道前后均可调用。
     *
     * @param role 用户角色有两种：<br/>Constants.CLIENT_ROLE_ANCHOR 主播角色，可以发流也可以收流。<br/>Constants.CLIENT_ROLE_AUDIENCE 观众角色(默认)，只能收流不能发流。
     * <p/>
     * @return 返回 0 代表方法调用成功，返回其他数字代表调用失败。
     */
    virtual RtcStatus SetClientRole(RtcClientRole role) = 0;

    /**
     * 加入频道。
     * <p/>
     * 相比于 RtcEngine 类下的 joinChannel 方法，该方法支持通过创建多个 RtcChannel 对象，并调用相应对象的 joinChannel 方法，实现同时加入多个频道。
     * <p/>
     * 使用注意：<br/>
     * 1.使用不同 App ID 的 App 是不能互通的。<br/>
     * 2.如果已在通话中，用户必须调用 leaveChannel 退出当前通话，才能进入下一个频道。
     *
     * @param token 在服务端生成的用于鉴权的 Token。
     * @param uid 用户 ID。当前仅支持数字类型的字符串，数值范围为1-9，不支持任何特殊符号，英文字母，空格等，长度续保证为 Long 类型的最大值以内。
     * @param options 频道媒体设置选项。
     * <p/>
     * @return 返回 0 代表方法调用成功，返回其他数字代表调用失败。
     */
    virtual RtcStatus JoinChannel(std::string token, int64_t uid, const ChannelMediaOptions &options) = 0;

    /**
     * 离开当前频道。
     * <p/>
     * 成功调用该方法离开频道后，会触发如下回调，本地触发 onLeaveChannel 回调，远端触发 onUserOffline 回调。
     *
     * @return 返回 0 代表方法调用成功，返回其他数字代表调用失败。
     */
    virtual RtcStatus LeaveChannel() = 0;

    /**
     * 更新 Token。
     * <p/>
     * 需要重新在服务端重新获取 token，然后调用该方法更新 Token，否则 SDK 无法和服务器建立连接。
     *
     * @param token 新的 Token。
     * <p/>
     * @return 返回 0 代表方法调用成功，返回其他数字代表调用失败。
     */
    virtual RtcStatus RenewToken(std::string token) = 0;

    /**
     * 创建数据流
     * <p/>
     * 该方法用于创建数据流。RtcChannel 生命周期内，每个用户最多只能创建 5 个数据流。频道内数据通道最多允许数据延迟 5 秒，若超过 5 秒接收方尚未收到数据流，则数据通道会向 App 报错。
     * <p/>
     * 该方法需要在加入频道后调用。
     *
     * @param reliable 是否可靠。true: 接收方 5 秒内会收到发送方所发送的数据，否则会收到 onStreamMessageError 回调并获得相应报错信息(暂不支持)。false: 接收方不保证收到，就算数据丢失也不会报错。
     * @param ordered 是否有序。true: 接收方会按照发送方发送的顺序收到数据包。false: 接收方不保证按照发送方发送的顺序收到数据包。
     * <p/>
     * @return 0 代表方法调用成功，其他代表失败。
     */
    virtual RtcStatus CreateDataStream(bool reliable, bool ordered) = 0;

    /**
     * 发送自定义数据流
     * <p/>
     * 该方法发送数据流消息到频道内所有用户。SDK 对该方法的实现进行了如下限制：频道内每秒最多能发送 30 个包，且每个包最大为 1 KB。 每个客户端每秒最多能发送 6 KB 数据。频道内每人最多能同时有 5 个数据通道。
     *
     * @param streamId 数据流 ID，createDataStream 的返回值。
     * @param message 待发送的数据。
     * <p/>
     * @return 0 代表方法调用成功，其他代表失败。
     */
    virtual RtcStatus SendStreamMessage(int stream_id, const std::vector<unsigned char> &message) = 0;

    /**
     * 获取频道的 Session ID
     * <p/>
     * @return 返回频道的 Session ID
     */
    virtual std::string GetChannelSessionId() const = 0;

    // ------------------------ 音频相关 -----------------------

    /**
     * 默认取消或恢复订阅远端用户的音频流。
     * <p/>
     * 调用成功后，本地用户取消或恢复订阅调用时刻之后加入频道的远端用户。
     *
     * @param muted 是否默认取消订阅远端用户的音频流。true：默认取消订阅远端用户的音频流。false：（默认）默认订阅远端用户的音频流。
     * <p/>
     * @return 0 代表方法调用成功，其他代表失败。
     */
    virtual RtcStatus SetDefaultMuteAllRemoteAudioStreams(bool muted) = 0;

    /**
     * 停止/恢复发送本地音频流。
     * <p/>
     * 静音/取消静音。该 API 用于禁止/允许往网络发送本地音频流，不影响音频采集以及音频流的接收。
     * <p/>
     * 成功调用该方法后，频道内所有用户(包括自己)会触发 onUserMuteAudio 回调。
     * <p/>
     * 使用注意：<br/>
     * 1.该方法不影响录音状态，并没有禁用麦克风。
     *
     * @param muted true：停止发送本地音频流，false：继续发送本地音频流（默认）。
     * <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual RtcStatus MuteLocalAudioStream(std::string media_id, bool muted) = 0;

    /**
     * 停止/恢复接收指定用户的音频流。
     * <p/>
     * 如果之前有调用过 muteAllRemoteAudioStreams (true) 停止接收所有远端音频流，在调用本 API 之前请确保你已调用
     * muteAllRemoteAudioStreams (false)。muteAllRemoteAudioStreams 是全局控制，muteRemoteAudioStream 是精细控制。
     * <p/>
     * 使用注意：<br/>
     * 1.只有成功加入频道后调用有效，加入频道前调用无效。<br/>
     *
     * @param uid 指定的用户 ID <br/>
     * @param muted true：停止接收指定用户的音频流，false：继续接收指定用户的音频流（默认）。
     * <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual RtcStatus MuteRemoteAudioStream(int64_t uid, std::string media_id, bool muted) = 0;

    /**
     * 停止/恢复接收所有音频流。
     * <p/>
     * 不接收房间内所有的音频，不影响本地音频采集和音频流的发送。
     * <p/>
     * 使用注意：<br/>
     * 1.只有成功加入频道后调用有效，加入频道前调用无效。<br/>
     *
     * @param muted true：不接收所有远端音频流，false：接收所有远端音频流（默认）。
     * <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual RtcStatus MuteAllRemoteAudioStreams(bool muted) = 0;

    // ------------------------ 视频相关 -----------------------

    /**
     * 设置是否默认接收视频流。
     * <p/>
     * 该方法在加入频道前后都可调用。如果在加入频道后调用 setDefaultMuteAllRemoteVideoStreams(true)， 会接收不到后面加入频道的用户的视频流。
     * <p/>
     * 使用注意：<br/>
     * 1.停止接收视频流后，如果想要恢复接收，请调用 muteRemoteVideoStream(false)，并指定你想要接收的远端用户的 ID。<br/>
     * 2.如果想恢复接收多个用户的视频流，则需要多次调用 muteRemoteVideoStream。<br/>
     * 3.setDefaultMuteAllRemoteVideoStreams(false) 只能恢复接收设置后加入频道的用户的视频流。<br/>
     *
     * @param muted true ：默认不接收所有远端视频流。false ：默认继续接收所有远端视频流（默认）。
     * <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual RtcStatus SetDefaultMuteAllRemoteVideoStreams(bool muted) = 0;

    /**
     * 停止/恢复发送本地视频流。
     * <p/>
     * 成功调用该方法后，远端会触发 onUserMuteVideo 回调。
     * <p/>
     * 使用注意：<br/>
     * 1.调用该方法时，SDK 不再发送本地视频流，但摄像头仍然处于工作状态。相比于 enableLocalVideo (false) 用于控制本地视频流发送的方法，该方法响应速度更快。<br/>
     * 2.该方法不影响本地视频流获取，没有禁用摄像头。
     *
     * @param mediaId 本地用户视频流 ID。<br/>
     * @param muted true: 不发送本地视频流。false: （默认）发送本地视频流。
     * <p/>
     * @return 0 代表方法调用成功，其他代表失败。<br/>
     */
    virtual RtcStatus MuteLocalVideoStream(std::string media_id, bool muted) = 0;

    /**
     * 停止/恢复接收指定用户的视频流。
     * <p/>
     * 如果之前有调用过 muteAllRemoteVideoStreams (true) 停止接收所有远端视频流，在调用本 API 之前请确保你已调用
     * muteAllRemoteVideoStreams (false)。 muteAllRemoteVideoStreams 是全局控制，muteRemoteVideoStream 是精细控制。
     * <p/>
     * 使用注意：<br/>
     * 1.只有成功加入频道后调用有效，加入频道前调用无效。<br/>
     *
     * @param uid 指定的用户 ID 。<br/>
     * @param mediaId 指定的用户视频流 ID。<br/>
     * @param muted true ：停止接收指定用户的视频流。false ：继续接收指定用户的视频流（默认）。
     * <p/>
     * @return 0 代表方法调用成功，其他代表失败。<br/>
     */
    virtual RtcStatus MuteRemoteVideoStream(int64_t uid, std::string media_id, bool muted) = 0;

    /**
     * 停止/恢复接收所有视频流。
     * <p/>
     * 不接收房间内所有用户的视频流，不影响本地视频采集和视频流的发送。
     * <p/>
     * 使用注意：<br/>
     * 1.只有成功加入频道后调用有效，加入频道前调用无效。<br/>
     *
     * @param muted true: 停止接收所有远端视频流。false: 继续接收所有远端视频流（默认）。
     *              <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual RtcStatus MuteAllRemoteVideoStreams(bool muted) = 0;

    /**
     * 设置订阅的视频流类型。
     * <p/>
     * 如果发送端选择发送视频双流（大流或小流），接收端可以选择接收大流还是小流。其中大流可以理解为高分辨率高码率的视频流，小流则是低分辨率低码率的视频流。视频小流的分辨率默认为视频大流的一半。
     * <p/>
     * 使用注意：<br/>
     * 1.如果发送端用户未启用双流模式，SDK 默认接收大流。
     *
     * @param uid        指定的远端用户 ID。<br/>
     * @param media_id    指定的远端用户视频流 ID。<br/>
     * @param stream_type 设置视频流大小。视频流类型如下：1、VIDEO_STREAM_HIGH，视频大流，即高分辨率、高码率视频流。2、VIDEO_STREAM_LOW，视频小流，即低分辨率、低码率视频流。
     *                   <p/>
     * @return 返回 0 代表方法调用成功，返回其他数字代表调用失败。
     */
    virtual RtcStatus SetRemoteVideoStreamType(int64_t uid, std::string media_id, VideoStreamType stream_type) = 0;
};

#endif // CORERTCPROJECT_IOMNIRTCCHANNEL_H