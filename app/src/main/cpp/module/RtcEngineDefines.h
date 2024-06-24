//
// Created by ZaneWang on 2024/6/19.
//

#ifndef MYCXXAPPLICATION_RTCENGINEDEFINES_H
#define MYCXXAPPLICATION_RTCENGINEDEFINES_H

enum RtcStatus {
    /**
     * 接口调用成功。
     */
    FUNCTION_SUCCESS = 0,
    /**
     * 接口内部发送错误，出现空值，调用失败。
     */
    ERROR_FUNCTION_ERROR_EMPTY_VALUE = -1,
    /**
     * 接口请求过于频繁，已经在进行中。
     */
    ERROR_FUNCTION_BUSY = -2,
    /**
     * 接口已处于调用后的状态，无需再调用。
     */
    ERROR_FUNCTION_STATED = FUNCTION_SUCCESS,
    /**
     * 有两种原因。<br/>
     * 1.该接口的前置操作没做。<br/>
     * 2.由于前置操作的设置，导致当前方式调用该接口的行为不正确。<br/>
     */
    ERROR_FUNCTION_INVOKE_ERROR = -3,
    /**
     * SDK当前状态不支持此操作
     */
    ERROR_NOT_SUPPORTED = -4,
    /**
     * 接口所传递的参数有问题。
     */
    ERROR_FUNCTION_ERROR_ARGS = -5,
    /**
     * 接口调用失败，原因未知。
     */
    ERROR_FUNCTION_ERROR_FAILED = -6,
    /**
     * 接口调用失败，引擎还未创建。
     */
    ERROR_FUNCTION_RTC_ENGINE_EMPTY = -7,

    // channel 推流错误码
    /**
     * 当前有其他频道正在推流还未停止，当前频道不能进行推流。
     */
    ERROR_CHANNEL_PUSH_REPEAT = -5,
};

enum VideoRenderMode {
    /**
     * 如果视频尺寸与显示视窗尺寸不一致，则视频流会按照显示视窗的比例进行周边裁剪或图像拉伸后填满视窗。
     */
    RENDER_MODE_HIDDEN = 1,
    /**
     * 如果视频尺寸与显示视窗尺寸不一致，在保持长宽比的前提下，将视频进行缩放后填满视窗。
     */
    RENDER_MODE_FIT = 2,
    /**
     * 视频尺寸进行缩放和拉伸以充满显示视窗。
     */
    RENDER_MODE_FILL = 3,
};

enum VideoMirrorMode {
    /**
     * （默认）由 SDK 决定镜像模式。SDK 默认关闭视频编码的镜像模式。
     */
    VIDEO_MIRROR_MODE_AUTO = 160200,
    /**
     * 开启镜像模式。
     */
    VIDEO_MIRROR_MODE_ENABLED = 160201,
    /**
     * 关闭镜像模式。
     */
    VIDEO_MIRROR_MODE_DISABLED = 160202,
};
#endif //MYCXXAPPLICATION_RTCENGINEDEFINES_H