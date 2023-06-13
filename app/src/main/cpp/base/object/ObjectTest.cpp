//
// Created by ZaneWang on 6/2/21.
//
#include <thread>
#include <unistd.h>
#include "BaseObject.h"
#include "bean/Complex.h"
#include "ObjectLifeTest.h"
#include "vector"

void transObject();

void transObj1(BaseObject object);

void transObj2(BaseObject *pObject);

void transObj3(BaseObject &obj3);

void changeObject();

void baseOperator();

void test1111(uint32_t aa, uint32_t &bb);

void transObj4();

uint32_t mtest = 0;
std::vector<BaseObject> m_vector;


extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ObjectTest_structTest(JNIEnv *env, jobject thiz) {
    // 1、对象的创建和释放。
//    ObjectLifeTest objectLifeTest;
//    objectLifeTest.startTest();
//    LOGD_TWO(BASETAG, "========================================分隔符================================");
    // 2、对象的传递。
    transObject();
//    LOGD_TWO(BASETAG, "========================================分隔符================================");
    // 3、对象的改变
//    changeObject();
    // 4、对象基本使用
//    baseOperator();

//    LOGD_TWO(BASETAG, "============000: %p", &mtest);
//    test1111(mtest, mtest);
//    LOGD_TWO(BASETAG, "============222: %d, %p", mtest, &mtest);
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_ObjectTest_stringTest(JNIEnv *env, jobject thiz, jstring str) {
    // 测试字符串转移
//    m_pStringTest = new StringTest();
    const char *localStr = env->GetStringUTFChars(str, nullptr);
//    LOGD_TWO(BASETAG, "获取到字符串，地址 = %p", &localStr);
//    m_pStringTest->m_string = localStr;
//    LOGD_TWO(BASETAG, "字符串已转移到 StringTest 对象上，检查是否存在 = %s，地址 = %p", m_pStringTest->m_string, &m_pStringTest->m_string);
    env->ReleaseStringUTFChars(str, localStr);
//    LOGD_TWO(BASETAG, "字符串已转移到 StringTest 对象上，检查是否存在 = %s，地址 = %p", m_pStringTest->m_string, &m_pStringTest->m_string);
//    delete m_pStringTest;
}


void test1111(uint32_t aa, uint32_t &bb) {
    LOGD_TWO(BASETAG, "============111 %p, %p", &aa, &bb);
    bb = 3;
    aa = 5;
}

#include "dream_handler_test.h"



std::shared_ptr<DreamHandlerTest> test;
/**
 * 对象在方法之间传递时，引用传递会自动生成一个新的临时对象，指针传递则不会自动生成临时对象。
 */
void transObject() {
//    BaseObject obj1("obj1");
//    LOGD_TWO(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
//    transObj1(obj1);

//    BaseObject *obj2 = new BaseObject("m_pObj");
//    LOGD_TWO(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
//    transObj2(obj2);
//    delete obj2;

//    BaseObject obj3("obj3");
//    transObj3(obj3);

//    transObj4();

    test = std::make_shared<DreamHandlerTest>();
    test->StartTest();
}

void transObj4() {
    // 在栈上创建一个局部变量
    BaseObject obj4("obj4");
    LOGD_TWO(BASETAG, "我是在栈上创建的 obj4，地址是=%p", &obj4);
    // 放入全局集合中
    m_vector.push_back(obj4);
    std::thread thread([] {
        usleep(1 * 1000);
        BaseObject obj = m_vector.front();
        LOGD_TWO(BASETAG, "从另一个线程从全局集合中读取 obj4，地址是=%p", &obj);
    });
    thread.join();
}

/**
 * 在栈中创建的对象，其地址不能被改变、转移。
 */
void changeObject() {
    BaseObject obj1("obj1");
    LOGD_TWO(BASETAG, "我是在栈空间上创建的obj1，地址是=%p", &obj1);
    BaseObject *obj2 = new BaseObject("m_pObj");
    LOGD_TWO(BASETAG, "我是在堆空间上创建的obj2，地址是=%p", obj2);
    BaseObject *obj3 = new BaseObject("obj3");
    LOGD_TWO(BASETAG, "我是在堆空间上创建的obj3，地址是=%p", obj3);
    obj1 = *obj2;
    LOGD_TWO(BASETAG, "将 m_pObj 赋值给 obj1 后，obj1 地址是=%p，m_pObj 地址是=%p", &obj1, obj2);
    obj2 = obj3;
    LOGD_TWO(BASETAG, "将 obj3 赋值给 m_pObj 后，m_pObj 地址是=%p，obj3 地址是=%p", obj2, obj3);
}

void baseOperator() {
//    Complex *complex = new Complex(1.0, 1.0);
//    Complex *complex2 = new Complex(2.0, 2.0);
//    Complex *complex3 = new Complex(3.0, 3.0);
//    LOGD_TWO(BASETAG, "创建 Complex 对象1 real = %lf , image = %lf, address = %p", complex->getReal(), complex->getImage(), complex);
//    LOGD_TWO(BASETAG, "创建 Complex 对象2 real = %lf , image = %lf, address = %p", complex2->getReal(), complex2->getImage(), complex2);
//    LOGD_TWO(BASETAG, "创建 Complex 对象3 real = %lf , image = %lf, address = %p", complex3->getReal(), complex3->getImage(), complex3);
//    Complex* comp;
//    comp = *complex + *complex2;

    Complex complex(1.0, 1.0);
    Complex complex2(2.0, 2.0);
    Complex complex3(3.0, 3.0);
    Complex comp;
    comp = complex + complex2;
    LOGD_TWO(BASETAG, "Complex1 对象 和 Complex2 对象做加法运算 real = %lf , image = %lf, address = %p", comp.getReal(), comp.getImage(), &comp);
//    delete complex;
//    delete complex2;
//    delete complex3;
}

void transObj1(BaseObject obj1) {
    LOGD_TWO(BASETAG, "接收到obj1，地址是=%p", &obj1);
}

void transObj2(BaseObject *obj2) {
    LOGD_TWO(BASETAG, "接收到obj2，地址是=%p", obj2);
}

void transObj3(BaseObject &obj3) {
    BaseObject obj4("obj4");
    LOGD_TWO(BASETAG, "创建临时对象 obj4，地址是=%p，obj3 地址是=%p", &obj4, &obj3);
    obj3 = obj4;
    LOGD_TWO(BASETAG, "将 obj4 传递给 obj3 后，obj3 地址是=%p，obj4 地址是=%p", &obj3, &obj4);
    LOGD_TWO(BASETAG, "obj3=%s, obj4=%s", obj3.getName(), obj4.getName());
}