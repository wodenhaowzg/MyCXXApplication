//
// Created by ZaneWang on 2020/7/22.
//

#include "BaseObject.h"

/**
 * 基类实现文件
 */

void transObject(BaseObject obj, BaseObject &obj2);

void BaseObject::toString() {
    LOGD_TWO(BASETAG, "BaseObject@%p", this);
}

void BaseObject::hashCode() {
    LOGD_TWO(BASETAG, "hashcode@%p", this);
}

void BaseObject::lifeTest() {
    {
        BaseObject obj("lifeTest");
    }
}

BaseObject m_transObj("2");

void BaseObject::transTest() {
    BaseObject obj("transObj");
    LOGD_TWO(BASETAG, "Create trans m_obj = %p, global m_obj = %p", &obj, &m_transObj);
    transObject(obj, obj);
}

const char *BaseObject::getName() const {
    return mName;
}


void transObject(BaseObject obj1, BaseObject &obj2) {
    LOGD_TWO(BASETAG, "Recv trans obj1 = %p, m_pObj = %p", &obj1, &obj2);
    LOGD_TWO(BASETAG, " 000 global m_obj = %p, name = %s", &m_transObj, m_transObj.getName());
    m_transObj = obj2;
    LOGD_TWO(BASETAG, "global m_obj = %p, name = %s", &m_transObj, m_transObj.getName());
}


//class Child {
//
//};
//
//class Object {
//private:
//    int m_a = 1;
//    int m_b = 2;
//    Child m_child;
//    Child* m_child2 = new Child();
//};


