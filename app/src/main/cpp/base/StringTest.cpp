//
// Created by ZaneWang on 2021/4/17.
//

#include <sstream>
#include "object/BaseObject.h"

void printStringArray(const char *pStringArray[], int length);

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_StringTest_stringTest(JNIEnv *env, jobject thiz) {
    // 定义一个字符串buffer
    std::stringstream ss;
    // 字符串默认都是以 \0 空白字符结尾，所以字符数组的容量要比实际字符串长度多1
    char charArray[11] = {"Helloworld"};
    ss << charArray;
//    LOGI_TWO(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    int len = sizeof(charArray) / sizeof(charArray[0]);
    for (int i = 0; i < len; ++i) {
        ss << charArray[i] << ", ";
    }
//    LOGI_TWO(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    // 定义指针型的字符数组
    char *pCharArray = {"helloworld"}; // 直接定义的话，内容不能修改，因为是在常量区
    pCharArray = charArray;
    ss << "pointer char array: ";
    for (int i = 0; i < len; ++i) {
        ss << *(pCharArray + i) << ", ";
    }
//    LOGI_TWO(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    // 字符串常用操作，这里有两个版本，非安全和安全的，一般使用安全版本，安全版本带后缀_s，但是android提供的标准库中不存在.
    // 长度计算
    char charArray2[] = {"StringOperator"};
    len = strlen(charArray2);
    ss << "String: " << charArray;
    ss << ", String len: " << len;
//    LOGI_TWO(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    char container[16] = {0};
    // 复制 strncpy
    char charArray3[] = "copy";
    strcpy(container, charArray);
    for (int i = 0; i < 16; ++i) {
        ss << container[i] << ", ";
    }

    const char *ccc = ss.str().c_str();
//    LOGI_TWO(BASETAG, ccc);
    ss.clear();
    ss.str("");
    // 复制一段长度的字符串
    strncpy(container, charArray3, 4);
    for (int i = 0; i < 16; ++i) {
        ss << container[i];
    }
//    LOGI_TWO(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    // 比较 strcmp 通过对比ASCII值
    // 拼接 strcat
    // 查找字符 strchr
    // 查找字符串 strstr
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_StringTest_nativeTransCopyString(JNIEnv *env, jobject thiz, jobjectArray stringArray) {
    int len = env->GetArrayLength(stringArray);
    const char *cstrArray[len];
    for (int i = 0; i < len; ++i) {
        auto jstringRef = (jstring) env->GetObjectArrayElement(stringArray, i);
        const char *cstrRef = env->GetStringUTFChars(jstringRef, nullptr);
        cstrArray[i] = cstrRef;
    }
    printStringArray(cstrArray, len);
    for (int i = 0; i < len; ++i) {
        auto jstringRef = (jstring) env->GetObjectArrayElement(stringArray, i);
        env->ReleaseStringUTFChars(jstringRef, cstrArray[i]);
    }
}

void printStringArray(const char *pStringArray[], int length) {
    for (int i = 0; i < length; ++i) {
        LOGD("Print string: %s", pStringArray[i]);
    }
}