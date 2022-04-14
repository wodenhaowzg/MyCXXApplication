//
// Created by ZaneWang on 2020/7/22.
//

#ifndef MYCXXAPPLICATION_CHILDOBJECT_H
#define MYCXXAPPLICATION_CHILDOBJECT_H

#include "BaseObject.h"

/**
 * C++ 继承，有三种继承方式(JAVA不存在)，默认是 private 方式继承。
 *
 * 继承权限修饰符
 * public(公有继承)：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
 * protected(保护继承)：当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。
 * private(私有继承)：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。
 */
class ChildObject : protected BaseObject {

public:

    ChildObject(const char *name) : BaseObject(name) {

    }

    /**
     * 重写父类虚方法
     */
    void toString();

    /**
     * 重写父类非虚方法
     */
    void hashCode();
};

#endif //MYCXXAPPLICATION_CHILDOBJECT_H
