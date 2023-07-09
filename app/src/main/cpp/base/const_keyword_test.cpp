#include <jni.h>
#include "Common.h"
#include "simple_object.h"

//
// Created by ZaneWang on 2023/6/22.
//

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_BaseTest_nativeConstTest(JNIEnv *env, jobject thiz) {
    // 修饰变量，变量的值不可改变
//    const int a = 1;
//    const char b = '&%';
//    a = 2;  // 编译报错
//    b = '2'; // 编译报错

    // 修饰对象，对象中成员变量的值不可改变，不可调用非 const 成员方法。
//    const SimpleObject obj;
//    obj.m_type = 2; // 编译报错，不能改变成员变量的值
//    obj.m_name = "3"; // 编译报错，不能改变成员变量的值
//    obj.FirstFunc(); // 编译通过，可以调用被 const 修饰的方法
//    obj.SecondFunc(); // 编译报错，不可以调用没有被 const 修饰的方法

    // 修饰指针时，如果放在 * 号左侧，则代表指针所指向的内容不可改变
//    const SimpleObject* obj = new SimpleObject();
//    obj->m_type = 2; // 编译报错，不能改变成员变量的值
//    obj->m_name = "3"; // 编译报错，不能改变成员变量的值

    // 修饰指针时，如果放在 * 号右侧侧，则代表指针的指向不可改变，但指针指向的内容可以改变
//    SimpleObject* const obj = new SimpleObject();
//    SimpleObject* obj2 = new SimpleObject();
//    obj = obj2; // 编译报错，不能改变 obj 指针的指向

//      char c = '1';
//    LOGI("c address = %p, c value = %s", c, c);
//    const char * c1 = "22";
//    LOGI("c1 address = %p, c1 value = %s", c1, c1);
////    c1 = &c;
////    c1 = "33";
//    LOGI("after changed, c address = %p, c value = %s", c, c);
}