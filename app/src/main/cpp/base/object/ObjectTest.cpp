//
// Created by ZaneWang on 6/2/21.
//
#include "BaseObject.h"


struct Game {

    char name = 'a';
    int number = 1;

private:
    short sex = 1;
};

struct Game2 {

    char name = 'b';
    int number = 2;

private:
    short sex = 2;

};

void createObject();

void transObject();

void transObj1(BaseObject object);

void transObj2(BaseObject *pObject);

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ObjectTest_structTest(JNIEnv *env, jobject thiz) {
    // 1、对象的创建和释放。
    createObject();
    LOGD(BASETAG, "========================================分隔符================================");
    // 2、对象的传递。
    transObject();
}

void createObject() {
    // 对象的创建有方式有两种。
    // 在栈空间创建
    BaseObject obj1;
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    // 在堆空间创建
    BaseObject* obj2 = new BaseObject();
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    delete obj2;
    LOGD(BASETAG, "手动删除obj2，而obj1则不用管，超出作用域，系统会自动释放", obj2);
}

void transObject() {
    BaseObject obj1;
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    transObj1(obj1);
    BaseObject* obj2 = new BaseObject();
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    transObj2(obj2);
    delete obj2;
}

void transObj1(BaseObject obj1) {
    LOGD(BASETAG, "接收到obj1，地址是=%p", &obj1);
}

void transObj2(BaseObject *obj2) {
    LOGD(BASETAG, "接收到obj2，地址是=%p", obj2);
}
