//
// Created by ZaneWang on 2021/4/17.
//

#include <sstream>
#include <random>
#include <iostream>
#include "object/BaseObject.h"
#include "TimeUtils.h"
#include "ThreadUtils.h"

void printStringArray(const char *pStringArray[], int length);

long long testTextConnectPerformance();

long long testTextSubPerformance();

std::string parseFunctionName(const char *fullMethodName);

std::string parseFunctionName2(const char *fullMethodName);

void testBase();

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_StringTestJni_stringTest(JNIEnv *env, jobject thiz) {
//    testBase();

    // 测试字符串拼接性能，循环 10 次，经测试性能 snprintf > string.append > stringstream
//    long long test_count = 10;
//    long long total_elapsed = 0;
//    while (test_count > 0) {
//        long long elapsed = testTextConnectPerformance();
//        total_elapsed += elapsed;
//        test_count--;
//    }
//    long long avg_elapsed = total_elapsed / 10;
//    LOGI("平均耗时：%lld", avg_elapsed);

    testTextSubPerformance();
}

void testBase() {
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

/**
 * 测试字符串拼接效率最高的方式
 * @return
 */
long long testTextConnectPerformance() {
    // 方式1
    int bufferSize = 8192;
    char *outBuffer = new char[bufferSize];
    char *fmtBuffer = new char[bufferSize];
    int loop = 10000;
    long long total_elapsed = 0;
    while (loop > 0) {
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        int randomNum = dis(generator);
        long long randomNum2 = dis(generator);
        float randomNum3 = (float) dis(generator);
        double randomNum4 = (double) dis(generator);
        const char *text = "我是测试内容" + randomNum;
        const char *text2 = "我是测试内容2" + randomNum;
        const char *text3 = "我是测试内容3" + randomNum;
        const char *text4 = "我是测试内容4" + randomNum;
        const char *text5 = "我是测试内容5" + randomNum;
        long long currentTimeMillis = TimeUtils::CurrentTimeMillis();

        // 方式1 平均18ms
//        memset(outBuffer, 0, bufferSize);
//        memset(fmtBuffer, 0, bufferSize);
//        snprintf(outBuffer, bufferSize, "arg: [%d], arg: [%lld], arg: [%f], arg: [%lf], arg: [%s], arg: [%s], arg: [%s], arg: [%s], arg: [%s] -> %s\n",
//                 randomNum,
//                 randomNum2,
//                 randomNum3,
//                 randomNum4,
//                 text,
//                 text2,
//                 text3,
//                 text4,
//                 text5,
//                 fmtBuffer);

        // 方式2 平均55ms
//        std::string target_string;
//        target_string.append("arg: ").append(std::to_string(randomNum)).append(", arg: ").append(std::to_string(randomNum2))
//                .append(", arg: ").append(std::to_string(randomNum3))
//                .append(", arg: ").append(std::to_string(randomNum4))
//                .append(", arg: ").append(text)
//                .append(", arg: ").append(text2)
//                .append(", arg: ").append(text3)
//                .append(", arg: ").append(text4)
//                .append(", arg: ").append(text5);
//        const char* tart_text = target_string.c_str();

        // 方式3 平均92ms
        std::stringstream ss;
        ss << "arg: " << randomNum << ", arg: " + randomNum2 << ", arg: " << randomNum3 << ", arg: " << randomNum4 << ", arg: " << text << ", arg: " << text2 << ", arg: " << text3 << ", arg: " << text4 << ", arg: " << text5;
        const char *target_test = ss.str().c_str();
        long long currentTimeMillis2 = TimeUtils::CurrentTimeMillis();
        long long elapsed = currentTimeMillis2 - currentTimeMillis;
        total_elapsed += elapsed;
        loop--;
    }
    LOGI("耗时：%lld", total_elapsed);
    return total_elapsed;
}

long long testTextSubPerformance() {
    std::string code1 = "int func1(int arg)";
    std::string code2 = "const char* func1(int arg)";
    std::string code3 = "void MyClass::func1(int arg)";
    std::string code4 = "jint JNI_OnLoad(JavaVM *, void *)";

    long long currentTimeMillis = TimeUtils::CurrentTimeMillis();
    int loop = 100000;
    while (loop > 0) {
        parseFunctionName2(code3.c_str());
        loop--;
    }
    long long currentTimeMillis2 = TimeUtils::CurrentTimeMillis();
    __android_log_print(ANDROID_LOG_INFO, BASETAG, "elapsed: %lld", (currentTimeMillis2 - currentTimeMillis));
    return 0;

}

std::string parseFunctionName(const char *fullMethodName) {
    std::string srcString(fullMethodName);
    size_t openParen = srcString.find('(');
    if (openParen == std::string::npos) { // 没找到(
        return "";
    }
    // 从左括号向前查找函数名的起始位置
    size_t end = openParen;
    while (end > 0 && (std::isalnum(srcString[end - 1]) || srcString[end - 1] == ':' || srcString[end - 1] == '_')) {
        end--;
    }
    // 提取并返回函数名
    return srcString.substr(end, openParen - end);
}

std::string parseFunctionName2(const char *fullMethodName) {
    if (!fullMethodName) {
        return "";
    }
    char *space = const_cast<char *>(fullMethodName);
    const char *colon = strchr(fullMethodName, ':');
    if (colon) {
        // split ClassName
        space = const_cast<char *>(colon);
        while (space > fullMethodName) {
            if (*space == ' ') {
                space++;
                break;
            }
            space--;
        }
    }
    const char *lparenthesis = strchr(fullMethodName, '(');
    std::string s(space, lparenthesis - space);
    return s;
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_StringTestJni_nativeTransCopyString(JNIEnv *env, jobject thiz, jobjectArray stringArray) {
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