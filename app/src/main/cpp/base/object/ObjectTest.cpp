//
// Created by ZaneWang on 6/2/21.
//
#include "BaseObject.h"
#include "Complex.h"

void createObject();

void transObject();

void transObj1(BaseObject object);

void transObj2(BaseObject *pObject);

void changeObject();

void baseOperator();

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ObjectTest_structTest(JNIEnv *env, jobject thiz) {
    // 1、对象的创建和释放。
//    createObject();
//    LOGD(BASETAG, "========================================分隔符================================");
    // 2、对象的传递。
//    transObject();
//    LOGD(BASETAG, "========================================分隔符================================");
    // 3、对象的改变
//    changeObject();
    // 4、对象基本使用
    baseOperator();
}

/**
 * 对象可以在栈和堆两中内存空间上创建。其中在栈上创建的对象，其生命周期由系统管理，而在堆上创建的生命周期，需要自己管理，new/delete
 */
void createObject() {
    // 对象的创建有方式有两种。
    // 在栈空间创建
    BaseObject obj1("obj1");
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    // 在堆空间创建
    BaseObject *obj2 = new BaseObject("obj2");
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    delete obj2;
    LOGD(BASETAG, "手动删除obj2，而obj1则不用管，超出作用域，系统会自动释放", obj2);
}

/**
 * 对象在方法之间传递时，引用传递会自动生成一个新的临时对象，指针传递则不会自动生成临时对象。
 */
void transObject() {
    BaseObject obj1("obj1");
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    transObj1(obj1);
    BaseObject *obj2 = new BaseObject("obj2");
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    transObj2(obj2);
    delete obj2;
}

/**
 * 在栈中创建的对象，其地址不能被改变、转移。
 */
void changeObject() {
    BaseObject obj1("obj1");
    LOGD(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    BaseObject *obj2 = new BaseObject("obj2");
    LOGD(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    BaseObject *obj3 = new BaseObject("obj3");
    LOGD(BASETAG, "我是在堆空间上创建的obj3，地址是=%p", obj3);
    obj1 = *obj2;
    LOGD(BASETAG, "将 obj2 赋值给 obj1 后，obj1 地址是=%p，obj2 地址是=%p", &obj1, obj2);
    obj2 = obj3;
    LOGD(BASETAG, "将 obj3 赋值给 obj2 后，obj2 地址是=%p，obj3 地址是=%p", obj2, obj3);
}

void baseOperator() {
//    Complex *complex = new Complex(1.0, 1.0);
//    Complex *complex2 = new Complex(2.0, 2.0);
//    Complex *complex3 = new Complex(3.0, 3.0);
//    LOGD(BASETAG, "创建 Complex 对象1 real = %lf , image = %lf, address = %p", complex->getReal(), complex->getImage(), complex);
//    LOGD(BASETAG, "创建 Complex 对象2 real = %lf , image = %lf, address = %p", complex2->getReal(), complex2->getImage(), complex2);
//    LOGD(BASETAG, "创建 Complex 对象3 real = %lf , image = %lf, address = %p", complex3->getReal(), complex3->getImage(), complex3);
//    Complex* comp;
//    comp = *complex + *complex2;

    Complex complex(1.0, 1.0);
    Complex complex2(2.0, 2.0);
    Complex complex3(3.0, 3.0);
    Complex comp;
    comp = complex + complex2;
    LOGD(BASETAG, "Complex1 对象 和 Complex2 对象做加法运算 real = %lf , image = %lf, address = %p", comp.getReal(), comp.getImage(), &comp);
//    delete complex;
//    delete complex2;
//    delete complex3;
}

void transObj1(BaseObject obj1) {
    LOGD(BASETAG, "接收到obj1，地址是=%p", &obj1);
}

void transObj2(BaseObject *obj2) {
    LOGD(BASETAG, "接收到obj2，地址是=%p", obj2);
}


