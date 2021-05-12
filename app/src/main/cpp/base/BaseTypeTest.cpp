//
// Created by ZaneWang on 2021/3/30.
//
#include <string>
#include "BaseObject.h"
#include <iostream>

using namespace std;
/**
 * 声明常量方式一
 */
#define CONSTANT_WIDTH 100;

/**
 * 声明常量方式二
 */
const int CONSTANT_WIDTH_8 = 0144; // 8进制
const int CONSTANT_WIDTH_10 = 100; // 10进制
const int CONSTANT_WIDTH_16 = 0x64; // 16进制

/**
 * 使用后缀U和L有两个点注意
 * 1、不区分大小写
 * 2、不区分顺序
 */
const int CONSTANT_WIDTH_U = 100U; // 表示无符号整数
const int CONSTANT_WIDTH_L = 100L; // 表示长整数
const int CONSTANT_WIDTH_UL = 100l; // 表示无符号长整数
const long long CONSTANT_LONG_WIDTH = 222;

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_BaseTypeTest_printBaseType(JNIEnv *env, jobject thiz) {
    LOGD("wzgtest", "long size with L: %d", sizeof(CONSTANT_WIDTH_L));
//    LOGD("wzgtest", "long long size : %s", sizeof(long));
}