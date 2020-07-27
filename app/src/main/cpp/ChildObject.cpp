//
// Created by ZaneWang on 2020/7/22.
//

#include "ChildObject.h"
#include <android/log.h>

void ChildObject::printlnObjectName() {
    __android_log_print(ANDROID_LOG_DEBUG, "wzgtest", "i am ChildObject");
    BaseObject::printlnObjectName();
}
