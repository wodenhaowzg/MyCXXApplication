//
// Created by ZaneWang on 2021/3/30.
//
#include <string>
#include "object/BaseObject.h"
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


namespace A {

    int a = 100;
}

int a = 200;


extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_BaseTest_nativeStartTest(JNIEnv *env, jobject thiz) {
    LOGD_TWO(BASETAG, "========================================================================");
    // C++ 基本类型
    // 各个基本类型所占的内存大小
    LOGD_TWO(BASETAG, "char = %d", sizeof(char)); // 1
    LOGD_TWO(BASETAG, "bool = %d", sizeof(bool)); // 1
    LOGD_TWO(BASETAG, "short = %d", sizeof(short)); // 2
    LOGD_TWO(BASETAG, "int = %d", sizeof(int)); // 4
    LOGD_TWO(BASETAG, "long = %d", sizeof(long)); // 8
    LOGD_TWO(BASETAG, "long long = %d", sizeof(long long)); // 8
    LOGD_TWO(BASETAG, "float = %d", sizeof(float)); // 4
    LOGD_TWO(BASETAG, "double = %d", sizeof(double)); // 8

    LOGD_TWO(BASETAG, "short short = %d", sizeof(short short)); // 2
    LOGD_TWO(BASETAG, "short int = %d", sizeof(short int)); // 2
    LOGD_TWO(BASETAG, "long int = %d", sizeof(long int)); // 8
    LOGD_TWO(BASETAG, "long double = %d", sizeof(long double)); // 16
    LOGD_TWO(BASETAG, "long long int = %d", sizeof(long long int)); // 8

    LOGD_TWO(BASETAG, "========================================================================");

    // 各个基本类型最大值
    LOGD_TWO(BASETAG, "max char = %d", std::numeric_limits<char>::max());
    LOGD_TWO(BASETAG, "max bool = %d", std::numeric_limits<bool>::max());
    LOGD_TWO(BASETAG, "max short = %d", std::numeric_limits<short>::max());
    LOGD_TWO(BASETAG, "max int = %d", std::numeric_limits<int>::max());
    LOGD_TWO(BASETAG, "max long = %ld", std::numeric_limits<long>::max());
    LOGD_TWO(BASETAG, "max long long = %lld", std::numeric_limits<long long>::max());
    LOGD_TWO(BASETAG, "max float = %f", std::numeric_limits<float>::max());
    LOGD_TWO(BASETAG, "max double = %lf", std::numeric_limits<double>::max());

    LOGD_TWO(BASETAG, "max unsigned char = %u", std::numeric_limits<unsigned char>::max());
    LOGD_TWO(BASETAG, "max unsigned short = %u", std::numeric_limits<unsigned short>::max());
    LOGD_TWO(BASETAG, "max unsigned int = %u", std::numeric_limits<unsigned int>::max());
    LOGD_TWO(BASETAG, "max unsigned long = %lu", std::numeric_limits<unsigned long>::max());
    LOGD_TWO(BASETAG, "max unsigned long long = %llu", std::numeric_limits<unsigned long long>::max());

    LOGD_TWO(BASETAG, "max short short = %hd", std::numeric_limits<short short>::max());
    LOGD_TWO(BASETAG, "max short int = %hd", std::numeric_limits<short int>::max());
    LOGD_TWO(BASETAG, "max long int = %ld", std::numeric_limits<long int>::max());
    LOGD_TWO(BASETAG, "max long double = %Lf", std::numeric_limits<long double>::max());

    LOGD_TWO(BASETAG, "max unsigned short short = %hu", std::numeric_limits<unsigned short short>::max());
    LOGD_TWO(BASETAG, "max unsigned short int = %hu", std::numeric_limits<unsigned short int>::max());
    LOGD_TWO(BASETAG, "max unsigned long int = %lu", std::numeric_limits<unsigned long int>::max());

    LOGD_TWO(BASETAG, "max long long int = %ld", std::numeric_limits<long long int>::max());
    LOGD_TWO(BASETAG, "max unsigned long long int = %lu", std::numeric_limits<unsigned long long int>::max());

    // 基本类型变量
    char vChar = 'a';
    bool vBool = false;
    short vShort = 123;
    int vInt = 1234;
    long vLong = 12345;
    long long vLongLong = 123456;
    float vFloat = 1.1;
    double vDouble = 1.11;
    // C++ 字符串
    char vCharArray[] = "abc";
    const char *vCharPointer = "abc-pointer";

    LOGD_TWO(BASETAG, "vChar = %c", vChar);
    LOGD_TWO(BASETAG, "vBool = %d", vBool);
    LOGD_TWO(BASETAG, "vShort = %d", vShort);
    LOGD_TWO(BASETAG, "vInt = %d", vInt);
    LOGD_TWO(BASETAG, "vLong = %ld", vLong);
    LOGD_TWO(BASETAG, "vLongLong = %lld", vLongLong);
    LOGD_TWO(BASETAG, "vFloat = %f", vFloat);
    LOGD_TWO(BASETAG, "vDouble = %lf", vDouble);
    LOGD_TWO(BASETAG, "vCharArray = %s", vCharArray);
    LOGD_TWO(BASETAG, "vCharPointer = %s", vCharPointer);

    LOGD_TWO(BASETAG, "========================================================================");

    /**
     * 符号修饰
     * signed 有符号，有负数
     * unsigned 无符号，没有负数
     * long 字节变长为8个字节
     * short 字节变短为2个字节
     */
    unsigned char vCharU = 'b';
    unsigned char vCharArrayU[] = "abcU";
    unsigned short vShortU = 124;
    unsigned int vIntU = 1235;
    unsigned long vLongU = 12346;
    unsigned long long vLongLongU = 123457;

    short short vShortS = 125;
    short int vIntS = 1236;

    unsigned short short vShortUS = 126;
    unsigned short int vIntUS = 1237;

    long int vIntL = 1238;
    long double vDoubleL = 1.12;

    unsigned long int vIntUL = 1238;

    LOGD_TWO(BASETAG, "vCharU = %c", vCharU);
    LOGD_TWO(BASETAG, "vCharArrayU = %s", vCharArrayU);
    LOGD_TWO(BASETAG, "vShortU = %u", vShortU);
    LOGD_TWO(BASETAG, "vIntU = %u", vIntU);
    LOGD_TWO(BASETAG, "vLongU = %lu", vLongU);
    LOGD_TWO(BASETAG, "vLongLongU = %llu", vLongLongU);

    LOGD_TWO(BASETAG, "vShortS = %hd", vShortS);
    LOGD_TWO(BASETAG, "vIntS = %hd", vIntS);
    LOGD_TWO(BASETAG, "vShortUS = %hu", vShortUS);
    LOGD_TWO(BASETAG, "vIntUS = %hu", vIntUS);

    LOGD_TWO(BASETAG, "vIntL = %ld", vIntL);
    LOGD_TWO(BASETAG, "vDoubleL = %lf", vDoubleL);
    LOGD_TWO(BASETAG, "vIntUL = %lu", vIntUL);

    // 测试命名空间
//    int a = 300;
//    using namespace A::a;
//    LOGD_TWO(BASETAG, "a = %d", a);
}