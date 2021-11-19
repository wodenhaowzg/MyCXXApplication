//
// Created by ZaneWang on 2020/7/22.
//

#include "BaseObject.h"

/**
 * 基类实现文件
 */

void BaseObject::toString() {
    LOGD(BASETAG, "BaseObject@%p", this);
}

void BaseObject::hashCode() {
    LOGD(BASETAG, "hashcode@%p", this);
}
