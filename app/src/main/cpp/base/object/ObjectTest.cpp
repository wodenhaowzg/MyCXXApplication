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

/**
 * 结论
 * 1、对象可以在栈和堆两中内存空间上创建。其中在栈上创建的对象，其生命周期由系统管理，而在堆上创建的生命周期，需要自己管理，new/delete
 * 2、对象在方法之间传递时，引用传递会自动生成一个新的临时对象，指针传递则不会自动生成临时对象。
 * 3、在栈中创建的对象，其地址不能被改变、转移。
 */
void changeObject();

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ObjectTest_structTest(JNIEnv *env, jobject thiz) {
    // 1、对象的创建和释放。
    createObject();
    LOGD(BASETAG, "========================================分隔符================================");
    // 2、对象的传递。
    transObject();
    LOGD(BASETAG, "========================================分隔符================================");
    // 3、对象的改变
    changeObject();
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

void changeObject() {
    BaseObject obj1;
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    BaseObject* obj2 = new BaseObject();
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    BaseObject* obj3 = new BaseObject();
    LOGD(BASETAG, "我是在堆空间上创建的obj3，地址是=%p", obj3);
    obj1 = *obj2;
    LOGD(BASETAG, "将 obj2 赋值给 obj1 后，obj1 地址是=%p，obj2 地址是=%p", &obj1, obj2);
    obj2 = obj3;
    LOGD(BASETAG, "将 obj3 赋值给 obj2 后，obj2 地址是=%p，obj3 地址是=%p", obj2, obj3);
}

void transObj1(BaseObject obj1) {
    LOGD(BASETAG, "接收到obj1，地址是=%p", &obj1);
}

void transObj2(BaseObject *obj2) {
    LOGD(BASETAG, "接收到obj2，地址是=%p", obj2);
}
