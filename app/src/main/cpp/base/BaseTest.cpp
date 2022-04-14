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
    LOGD(BASETAG, "========================================================================");
    // C++ 基本类型
    // 各个基本类型所占的内存大小
    LOGD(BASETAG, "char = %d", sizeof(char)); // 1
    LOGD(BASETAG, "bool = %d", sizeof(bool)); // 1
    LOGD(BASETAG, "short = %d", sizeof(short)); // 2
    LOGD(BASETAG, "int = %d", sizeof(int)); // 4
    LOGD(BASETAG, "long = %d", sizeof(long)); // 8
    LOGD(BASETAG, "long long = %d", sizeof(long long)); // 8
    LOGD(BASETAG, "float = %d", sizeof(float)); // 4
    LOGD(BASETAG, "double = %d", sizeof(double)); // 8

    LOGD(BASETAG, "short short = %d", sizeof(short short)); // 2
    LOGD(BASETAG, "short int = %d", sizeof(short int)); // 2
    LOGD(BASETAG, "long int = %d", sizeof(long int)); // 8
    LOGD(BASETAG, "long double = %d", sizeof(long double)); // 16
    LOGD(BASETAG, "long long int = %d", sizeof(long long int)); // 8

    LOGD(BASETAG, "========================================================================");

    // 各个基本类型最大值
    LOGD(BASETAG, "max char = %d", std::numeric_limits<char>::max());
    LOGD(BASETAG, "max bool = %d", std::numeric_limits<bool>::max());
    LOGD(BASETAG, "max short = %d", std::numeric_limits<short>::max());
    LOGD(BASETAG, "max int = %d", std::numeric_limits<int>::max());
    LOGD(BASETAG, "max long = %ld", std::numeric_limits<long>::max());
    LOGD(BASETAG, "max long long = %lld", std::numeric_limits<long long>::max());
    LOGD(BASETAG, "max float = %f", std::numeric_limits<float>::max());
    LOGD(BASETAG, "max double = %lf", std::numeric_limits<double>::max());

    LOGD(BASETAG, "max unsigned char = %u", std::numeric_limits<unsigned char>::max());
    LOGD(BASETAG, "max unsigned short = %u", std::numeric_limits<unsigned short>::max());
    LOGD(BASETAG, "max unsigned int = %u", std::numeric_limits<unsigned int>::max());
    LOGD(BASETAG, "max unsigned long = %lu", std::numeric_limits<unsigned long>::max());
    LOGD(BASETAG, "max unsigned long long = %llu", std::numeric_limits<unsigned long long>::max());

    LOGD(BASETAG, "max short short = %hd", std::numeric_limits<short short>::max());
    LOGD(BASETAG, "max short int = %hd", std::numeric_limits<short int>::max());
    LOGD(BASETAG, "max long int = %ld", std::numeric_limits<long int>::max());
    LOGD(BASETAG, "max long double = %Lf", std::numeric_limits<long double>::max());

    LOGD(BASETAG, "max unsigned short short = %hu", std::numeric_limits<unsigned short short>::max());
    LOGD(BASETAG, "max unsigned short int = %hu", std::numeric_limits<unsigned short int>::max());
    LOGD(BASETAG, "max unsigned long int = %lu", std::numeric_limits<unsigned long int>::max());

    LOGD(BASETAG, "max long long int = %ld", std::numeric_limits<long long int>::max());
    LOGD(BASETAG, "max unsigned long long int = %lu", std::numeric_limits<unsigned long long int>::max());

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

    LOGD(BASETAG, "vChar = %c", vChar);
    LOGD(BASETAG, "vBool = %d", vBool);
    LOGD(BASETAG, "vShort = %d", vShort);
    LOGD(BASETAG, "vInt = %d", vInt);
    LOGD(BASETAG, "vLong = %ld", vLong);
    LOGD(BASETAG, "vLongLong = %lld", vLongLong);
    LOGD(BASETAG, "vFloat = %f", vFloat);
    LOGD(BASETAG, "vDouble = %lf", vDouble);
    LOGD(BASETAG, "vCharArray = %s", vCharArray);
    LOGD(BASETAG, "vCharPointer = %s", vCharPointer);

    LOGD(BASETAG, "========================================================================");

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

    LOGD(BASETAG, "vCharU = %c", vCharU);
    LOGD(BASETAG, "vCharArrayU = %s", vCharArrayU);
    LOGD(BASETAG, "vShortU = %u", vShortU);
    LOGD(BASETAG, "vIntU = %u", vIntU);
    LOGD(BASETAG, "vLongU = %lu", vLongU);
    LOGD(BASETAG, "vLongLongU = %llu", vLongLongU);

    LOGD(BASETAG, "vShortS = %hd", vShortS);
    LOGD(BASETAG, "vIntS = %hd", vIntS);
    LOGD(BASETAG, "vShortUS = %hu", vShortUS);
    LOGD(BASETAG, "vIntUS = %hu", vIntUS);

    LOGD(BASETAG, "vIntL = %ld", vIntL);
    LOGD(BASETAG, "vDoubleL = %lf", vDoubleL);
    LOGD(BASETAG, "vIntUL = %lu", vIntUL);

    // 测试命名空间
    int a = 300;
    using namespace A::a;
    LOGD(BASETAG, "a = %d", a);
}