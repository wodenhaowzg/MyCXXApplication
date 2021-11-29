//
// Created by ZaneWang on 2020/7/22.
//

#include "BaseObject.h"

/**
 * 基类实现文件
 */

void transObject(BaseObject obj, BaseObject &obj2);

void BaseObject::toString() {
    LOGD(BASETAG, "BaseObject@%p", this);
}

void BaseObject::hashCode() {
    LOGD(BASETAG, "hashcode@%p", this);
}

void BaseObject::lifeTest() {
    {
        BaseObject obj("lifeTest");
    }
}

BaseObject m_transObj("2") ;

void BaseObject::transTest() {
    BaseObject obj("transObj");
    LOGD(BASETAG, "Create trans obj = %p, global obj = %p", &obj, &m_transObj);
    transObject(obj, obj);
}

const char *BaseObject::getName() const {
    return mName;
}


void transObject(BaseObject obj1, BaseObject &obj2) {
    LOGD(BASETAG, "Recv trans obj1 = %p, obj2 = %p", &obj1, &obj2);
    LOGD(BASETAG, " 000 global obj = %p, name = %s", &m_transObj, m_transObj.getName());
    m_transObj = obj2;
    LOGD(BASETAG, "global obj = %p, name = %s", &m_transObj, m_transObj.getName());
}


