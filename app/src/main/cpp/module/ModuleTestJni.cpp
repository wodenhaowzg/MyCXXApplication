//
// Created by ZaneWang on 2024/6/17.
//

#include <jni.h>
#include "MockOmniRtcChannel.h"
#include "OmniRtcEngine.h"

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ModuleJniTest_nativeStartTest(JNIEnv *env, jobject thiz) {
    OmniRtcEngine* rtcEngine = OmniRtcEngine::create(nullptr, "sss", nullptr);
    rtcEngine->setChannelProfile(2);
    rtcEngine->destroy();
    delete rtcEngine;
//    MockOmniRtcChannel* channel = new MockOmniRtcChannel();
//    channel->leaveChannel();
//    delete channel;
}