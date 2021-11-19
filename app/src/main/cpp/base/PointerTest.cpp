//
// Created by ZaneWang on 2021/4/17.
//
#include "object/BaseObject.h"

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_PointerTest_pointerTest(JNIEnv *env, jobject thiz) {
    stringstream ss;
    // 定义一个变量
    int a = 100;
    // 定义一个指针变量，并将变量 a 的地址值赋值给 b
    int *b = &a;
    ss << "a address value: " << b << " | a value: " << *b;
//    LOGI(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    // 定义一个数组
    int var1[] = {100, 200};
    // 定义一个指针数组
    int *pointer_array[2];
    // 定义一个数组指针
    int (*pArray)[2];

    // 将 var1 的地址值赋值给 var2
    pArray = &var1;
    LOGI(BASETAG, "打印数组指针");
    for (int i = 0; i < 2; ++i) {
        LOGI(BASETAG, "value: %d", (*pArray)[i]);
    }

    // 将 var 数组中每个值的内存地址值赋值给 pointer_array 指针数组
    for (int i = 0; i < 2; ++i) {
        pointer_array[i] = &(var1[i]);
    }

    LOGI(BASETAG, "打印指针数组");
    for (int i = 0; i < 2; ++i) {
        LOGI(BASETAG, "value : %d", (*pointer_array)[i]);
    }
}
