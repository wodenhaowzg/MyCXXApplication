//
// Created by ZaneWang on 2020/7/22.
//

#include "BaseObject.h"
#include <android/log.h>

void BaseObject::printlnObjectName() {
    __android_log_print(ANDROID_LOG_DEBUG, "wzgtest", "i am BaseObject");
}
