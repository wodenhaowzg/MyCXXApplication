//
// Created by ZaneWang on 2021/12/29.
//

#include "ObjectLifeTest.h"
#include "../../Common.h"

class LocalObj {

public:

    bool m_abool = false;

    LocalObj() {
        LOGD(BASETAG, "LocalObj created = %p", this);
    }

    ~LocalObj() {
        LOGD(BASETAG, "LocalObj destroyed = %p", this);
    }

    void func() {
        LOGD(BASETAG, "I am a function!");
    }
};

class LocalObj2 {

public:
    const char *m_name;

    LocalObj2(const char *name) {
        m_name = name;
        LOGD(BASETAG, "LocalObj2 created = %s", m_name);
    }

    ~LocalObj2() {
        LOGD(BASETAG, "LocalObj2 destroyed = %s", m_name);
    }

};

class LocalObj3 {

public:
    LocalObj2 m_obj; // 占 4 字节
    LocalObj2 *m_pObj; // 占 8 字节
    const char *m_name;

    LocalObj3(const char *name, const char *name2, const char *name3) : m_obj(name2) {
        LOGD(BASETAG, "LocalObj3 created = %s", name);
        m_name = name;
        m_pObj = new LocalObj2(name3);
    }

    ~LocalObj3() {
        LOGD(BASETAG, "LocalObj3 destroyed = %s", m_name);
    }
};

void ObjectLifeTest::startTest() {
    // 对象的创建有方式有两种。
    // 在栈空间创建
    LocalObj obj;
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj);
    // 在堆空间创建
    LocalObj *pObj = new LocalObj();
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", pObj);
    delete pObj;
    LOGD(BASETAG, "手动删除obj2，而obj1则不用管，超出作用域，系统会自动释放");
    LOGD(BASETAG, "================================================================");
    // 结论：一个空类大小为 1 ，类的成员变量占类的大小，但类的成员函数不占类的大小，因为成员函数是在代码区分配内存的。
    LocalObj obj2;
    LOGD(BASETAG, "对象的大小是 = %d", sizeof(obj2));
    LOGD(BASETAG, "================================================================");
    // 结论：如果对象是在栈上创建的，那么其内部对象类型的变量，像 m_obj 变量一样初始化，那这个子对象也是在栈上分配的内存，无须手动释放。
    test1();
    // 结论：如果对象是在堆上创建的，那么其内部对象类型的变量，像 m_obj 变量一样初始化，那这个子对象也是在堆上分配的内存，如果其父对象被 delete，会自动触发子对象的析构函数，无须手动执行 delete 。
    test2();
}

void ObjectLifeTest::test1() {
    LOGD(BASETAG, "================================================================");
    // 栈上创建一个 LocalObj3 对象，其生命周期系统管理。
    LocalObj3 localObj("111", "111-1", "111-2");
    // 打印内存地址
    LOGD(BASETAG, "栈上的 LocalObj3 对象内存地址 = %p", &localObj);
    // 打印成员变量 m_obj 内存地址
    LOGD(BASETAG, "栈上的 LocalObj3 对象的成员变量 m_obj 内存地址 = %p", &localObj.m_obj);
    // 打印成员变量指针 m_pObj 其指向的对象的内存地址 和 指针本身在栈上的内存地址
    LOGD(BASETAG, "栈上的 LocalObj3 对象的成员变量指针 m_pObj 其指向的对象的内存地址 = %p | 指针本身在栈上的内存地址 = %p", localObj.m_pObj, &localObj.m_pObj);
    // 成员变量 m_pObj 需要手动释放，根据 RAII 原则，最好是放在 localObj 对象的析构函数中执行 delete
    delete localObj.m_pObj;
}

void ObjectLifeTest::test2() {
    LOGD(BASETAG, "================================================================");
    // 栈上创建一个 LocalObj3 对象，其生命周期系统管理。
    LocalObj3 *localObj2 = new LocalObj3("222", "222-1", "222-2");
    // 打印内存地址
    LOGD(BASETAG, "堆上的 LocalObj3 对象，指针在栈上的内存地址 = %p ，指针指向堆上的内存地址 = %p", &localObj2, localObj2);
    // 打印成员变量 m_obj 内存地址
    LOGD(BASETAG, "堆上的 LocalObj3 对象的成员变量 m_obj 内存地址 = %p", &localObj2->m_obj);
    // 打印成员变量指针 m_pObj 其指向的对象的内存地址 和 指针本身在栈上的内存地址
    LOGD(BASETAG, "堆上的 LocalObj3 对象的成员变量指针 m_pObj 其指向的对象的内存地址 = %p | 指针本身在栈上的内存地址 = %p", localObj2->m_pObj, &localObj2->m_pObj);
    delete localObj2->m_pObj;
    delete localObj2;
}
