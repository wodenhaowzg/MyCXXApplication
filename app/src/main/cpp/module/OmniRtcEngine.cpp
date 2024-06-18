//
// Created by ZaneWang on 2024/6/18.
//

#include "OmniRtcEngine.h"

static OmniRtcEngine *g_instance = nullptr;
static std::mutex g_instanceMutex;
static const char* kLOG_TAG = "sss";
