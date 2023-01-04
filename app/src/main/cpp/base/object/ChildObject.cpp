//
// Created by ZaneWang on 2020/7/22.
//

#include "ChildObject.h"

void ChildObject::toString() {
    LOGD_TWO(BASETAG, "i am ChildObject, call toString");
}

void ChildObject::hashCode() {
    LOGD_TWO(BASETAG, "i am ChildObject, call hashCode!");
}
