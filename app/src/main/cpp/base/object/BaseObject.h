//
// Created by ZaneWang on 2020/7/22.
//

#ifndef MYCXXAPPLICATION_BASEOBJECT_H
#define MYCXXAPPLICATION_BASEOBJECT_H

#include <jni.h>
#include "../../Common.h"

/**
 * 基类头文件
 */
class BaseObject {

private:
    const char* mName = nullptr;
    BaseObject* mObj;

public:

    BaseObject(const char* name){
        mName = name;
        LOGD("wzgtest", "Object Constructor! Address = %p, name = %s", this, name);
    }

    ~BaseObject(){
        LOGD("wzgtest", "Object Destructor! Address = %p, name = %s", this, mName);
    }

    /**
     * 虚方法，代表子类可以重写该方法，实现多态，如果不是方法，则调用该方法，只能执行父类的实现。
     */
    virtual void toString();

    /**
     * 非虚方法。
     */
    void hashCode();

    void lifeTest();

    void transTest();

    const char *getName() const;
};

#endif //MYCXXAPPLICATION_BASEOBJECT_H
