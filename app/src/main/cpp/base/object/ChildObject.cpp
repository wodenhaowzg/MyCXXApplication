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

std::string& ChildObject::getString() {
    return m_string_list[0];
}

void ChildObject::addString(std::string &text) {
    LOGD("address222222 %p", &text);
    m_string_list.push_back(text);
}
