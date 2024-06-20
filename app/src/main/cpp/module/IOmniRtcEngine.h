//
// Created on 2024/6/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CORERTCPROJECT_IOMNIRTCENGINE_H
#define CORERTCPROJECT_IOMNIRTCENGINE_H

#include "IOmniRtcEngineEventHandler.h"
#include "OmniRtcChannel.h"

class IOmniRtcEngine {

public:
    /**
     * 初始化 SDK 引擎。
     * <p/>
     * 创建 SDK 引擎实例，目前 SDK 只支持一个 OmniRtcEngine 实例，即每个 App 仅可以创建一个 OmniRtcEngine 对象。在调用之前需要先获取 APPID 参数，申请地址 <a href="http://dashboard.3ttech.cn/index/register">http://dashboard.3ttech.cn/index/register</a> 。
     * <p/>
     * 接口的调用建议在同一个线程进行。接口的返回值分为两种，一种为 int 型的 API ，返回值 0 为调用成功，返回值小于 0 为调用失败；另一种为 boolean 型的 API ，true 为调用成功，false 为调用失败。
     * <p/>
     * 使用注意：<br/>
     * 1.同一个 APP ID 才能进入同一个频道实现通话或直播，不同的APP ID 无法实现互通。<br/>
     * 2.SDK 引擎同一时间只能持有一个 App ID。 如果 App 内存在多个 App ID，则需要再次调用 create 来切换 App ID ，此操作并不会再次创建一个新的实例对象。
     *
     * @param context 安卓APP(Android Application) 的上下文，而不是 Activity 的上下文。
     * @param appId   OMNI 为 App 开发者签发的 APP ID 。
     * @param handler OmniRtcEngineEventHandler 是一个提供了缺省实现的抽象类，SDK 通过该抽象类向 App 报告 SDK 运行时的各种事件。
     *                <p/>
     * @return OmniRtcEngine SDK 引擎对象。
     */
    static IOmniRtcEngine *create(void *context, const char *appId, OmniRtcEngineEventHandler *handler);

    /**
     * SDK 引擎的反初始化。
     */
    static void destroy();

    /**
     * 设置主回调事件。
     * <p/>
     * OmniRtcEngineEventHandler 接口类用于接收 SDK 向 App 发送回调事件通知，App 通过继承该接口类的方法获取 SDK 的事件通知。
     * <p/>
     * 接口类的所有方法都有缺省（空）实现，app 可以根据需要只继承关心的事件。在回调方法中，app 不应该做耗时或者调用可能会引起阻塞的 API（如 sendStreamMessage），否则可能影响 SDK 的运行。
     *
     * @param engineEventHandler 待添加的回调事件。
     */
    virtual void setHandler(OmniRtcEngineEventHandler *engineEventHandler) = 0;

    /**
     * 创建并获取一个 RtcChannel 对象。
     *
     * @param channelName 能标识频道的频道名，现只支持 64 字节的数值型字符串。
     *                    <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual OmniRtcChannel *createRtcChannel(const char *channelName) = 0;

    virtual void destroyRtcChannel(const char *channelName) = 0;

    //    virtual OmniAudioModule *getOmniAudioModule() = 0;

    //    virtual OmniVideoModule *getOmniVideoModule() = 0;

    /**
     * 设置频道模式。
     * <p/>
     * 在加入频道前，需要先设置频道的使用模式，SDK 需知道 App 的使用场景（例如通信模式或直播模式），从而使用不同的优化手段。
     * 通信模式(CHANNEL_PROFILE_COMMUNICATION)，常用于 1v1 音视频通话或群聊，其特点为：
     * 1.频道内的音视频交流，不能将音视频数据推送至 CDN 服务器。<br/>
     * 2.任何人均可创建频道。<br/>
     * 3.有两种角色可选，副播(CLIENT_ROLE_BROADCASTER)和观众(CLIENT_ROLE_AUDIENCE)，副播默认发送音视频数据，观众默认不发送，只听只看。<br/>
     * <p/>
     * 直播模式(CHANNEL_PROFILE_LIVE_BROADCASTING)，常用于泛娱乐直播，其特点为：<br/>
     * 1.可以设置推流地址，并将音视频数据推送至 CDN 服务器，用于第三方观众拉流观看。<br/>
     * 2.有三种角色可选，主播(CLIENT_ROLE_ANCHOR)、副播(CLIENT_ROLE_BROADCASTER)和观众(CLIENT_ROLE_AUDIENCE)，副播/观众和通信模式一样。<br/>
     * 3.主播可以创建直播频道，其他角色则不可创建，只能加入频道。<br/>
     * 4.频道没有被主播创建之前，其他副播/观众加入频道会失败。<br/>
     * 5.收发语音/视频流。<br/>
     * 6.有一些特殊功能，比如可以将某人请离房间。
     * <p/>
     * 游戏模式(CHANNEL_PROFILE_GAME_FREE_MODE)，与通信模式类似，但默认采用低功耗低码率的编解码。
     * <p/>
     * 使用注意：<br/>
     * 1.相同频道内的所有用户必须使用相同的频道模式，才能获得一致的使用体验，混用会出现一些不可控问题。<br/>
     * 2.必须在调用 joinChannel(加入频道) 接口之前调用和设置，加入频道后无法再设置。<br/>
     * 3.必须在调用 setClientRole(设置角色) 接口之前调用该接口，否则会影响 setClientRole 接口的生效。比如只有在直播模式下，
     * 才可以设置 CLIENT_ROLE_ANCHOR(主播) 角色。
     * 4.该接口为全局接口，退房间不会复位，不必每次进房间都设置，可以只在模式发生变化时调用。
     *
     * @param profile 频道模式，有三种：<br/> 1.CHANNEL_PROFILE_COMMUNICATION(通信模式)。<br/> 2.CHANNEL_PROFILE_LIVE_BROADCASTING(直播模式)。<br/> 3.CHANNEL_PROFILE_GAME_FREE_MODE(游戏模式)。
     *                <p/>
     * @return 0 代表方法调用成功，其他代表失败。<br/>
     */
    virtual int setChannelProfile(int profile) = 0;

    /**
     * 设置服务器地址
     * <p/>
     * 默认状态下 SDK 会自动寻找最合适的服务器地址，若 App 无特殊需求，无需调用此 API 。仅在加入频道前调用有效，频道内调用无效。
     *
     * @param ip   服务器的 IP 地址。
     * @param port 服务器的 IP 地址所对应的端口号。
     */
    virtual void setServerIp(const char *ip, int port) = 0;

    /**
     * 设置业务用户身份。
     *
     * @param role 用户身份，0 表示学生、1 表示老师、2 表示辅导老师。
     *             <p/>
     * @return 0 代表方法调用成功，其他代表失败
     */
    virtual int setBusinessUserRole(int role) = 0;

    /**
     * 设置 slb 地址。
     *
     * @param slb       slb 地址。
     * @param slbBackup slb 备用地址。
     *                  <p/>
     * @return 0 代表方法调用成功，其他代表失败
     */
    virtual int setSlbAddress(const char *slb, const char *slbBackup) = 0;

    /**
     * 设置 C++ 日志上传到服务器的地址。
     *
     * @param serverLogUrl 服务器地址。
     *                     <p/>
     * @return 0 代表方法调用成功，其他代表失败
     */
    virtual int setServerLogAddress(const char *serverLogUrl) = 0;

    /**
     * 设置业务直播形式
     *
     * @param jsonInfo 包含 livemode(业务直播模式) 和 planid(业务场景ID ) 两个子参数，参数示例 {"livemode":1,"planid":"1010"}
     * @return 0 代表方法调用成功，其他代表失败
     */
    virtual int setAppExtensionInfo(const char *jsonInfo) = 0;

    /**
     * 设置音频编码配置。
     * <p/>
     * 使用注意：<br/>
     * 1.该方法需要在 joinChannel 之前设置好，joinChannel 后设置不生效。<br/>
     * 2.通信和直播场景下，音质（码率）会有网络自适应的调整，通过该方法设置的是一个最高码率。
     *
     * @param profile 设置采样率，码率，编码模式和声道数，详见 AudioProfile。<br/>
     * @param scenario 设置音频应用场景，详见 AudioScenario。不同的音频场景下，设备的音量类型不同。详见如何区分媒体音量和通话音量。
     * <p/>
     * @return 0 代表方法调用成功，暂无错误返回。
     */
    virtual int setAudioProfile(int profile, int scenario) = 0;

    /**
     * 设置音频编码参数。
     * <p/>
     * 默认 SDK 的音频编码使用 ISAC 格式，适用于通话场景，而在对音质需求高的直播场景，推荐使用 AAC 或 OPUS 编码格式，需要显式调用该 API 变更。
     * <p/>
     * 使用注意：<br/>
     * 1.该方法需要在 joinChannel(加入频道) 之前设置好，joinChannel 后设置不生效。<br/>
     * 2.若使用 startRecordScreenAndSave(屏幕录制) 或 startRecordScreen(屏幕共享) API，则必须使用 AAC 。
     * <p/>
     *
     * @param codecType 音频编码格式，支持的类型如下：<br/> 1、Constants.AUDIO_CODEC_AAC。<br/> 2、Constants.AUDIO_CODEC_ISAC。<br/> 3、Constants.AUDIO_CODEC_OPUS。
     * @param bitrate 音频编码码率，范围如下：<br/> 1、Constants.AUDIO_CODEC_AAC，码率范围48kbps ~ 128kbps。<br/> 2、Constants.AUDIO_CODEC_ISAC，码率范围16kbps ~ 32kbps。<br/> 3、Constants.AUDIO_CODEC_OPUS，码率范围16kbps ~ 128kbps。
     * @param channels 声道数，支持单声道和双声道，参数范围是1 ~ 2
     * <p/>
     * @return 0 代表方法调用成功，其他代表失败。<br/>
     * -4 ：已加入频道，调用会失败。<br/>
     * -5 ：传递的参数有问题，比如所设置的音频编码格式、码率大小、或声道数不支持。
     */
    virtual int setPreferAudioCodec(int codecType, int bitrate, int channels) = 0;

    virtual int EnableLocalVideo(bool enabled) = 0;
};

#endif //CORERTCPROJECT_IOMNIRTCENGINE_H