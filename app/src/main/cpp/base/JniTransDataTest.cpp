//
// Created by ZaneWang on 3/5/21.
//

#include <jni.h>
#include <malloc.h>
#include <cstdint>
#include "Common.h"

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_JNITransDataTest_nativeTransferObjectToCXX(JNIEnv *env, jobject thiz, jobjectArray array) {
    // Get array size.
    jsize size = env->GetArrayLength(array);
    LOGI("TransObject -> array size = %d", size);
    for (int i = 0; i < size; ++i) {
        jobject bean = env->GetObjectArrayElement(array, i);
        // Get jclass
        jclass beanClazz = env->GetObjectClass(bean);
        if (beanClazz == nullptr) {
            LOGE("TransObject -> jclass is null! bean = %p", bean);
            return;
        }
        // Get mName
        jfieldID nameFieldId = env->GetFieldID(beanClazz, "mName", "Ljava/lang/String;");
        if (nameFieldId == nullptr) {
            LOGE("TransObject -> mName jfieldID is null! bean = %p", bean);
            return;
        }
        jstring nameStr = (jstring) env->GetObjectField(bean, nameFieldId);
        if (nameStr == nullptr) {
            LOGE("TransObject -> mName jstring is null! bean = %p", bean);
            return;
        }
        const char *nameChar = env->GetStringUTFChars(nameStr, nullptr);
        env->ReleaseStringUTFChars(nameStr, nameChar);
        // Get mAge
        jfieldID ageField = env->GetFieldID(beanClazz, "mAge", "I");
        if (ageField == nullptr) {
            LOGE("TransObject -> mAge jfieldID is null! bean = %p", bean);
            return;
        }
        jint ageInt = (jint) env->GetIntField(bean, ageField);
        if (ageInt == 0) {
            LOGE("TransObject -> mAge jint is null! bean = %p", bean);
            return;
        }
        // Get mMoney
        jfieldID moneyField = env->GetFieldID(beanClazz, "mMoney", "J");
        if (moneyField == nullptr) {
            LOGE("TransObject -> mMoney jfieldID is null! bean = %p", bean);
            return;
        }
        jint moneyLong = (jint) env->GetLongField(bean, moneyField);
        if (moneyLong == 0) {
            LOGE("TransObject -> mMoney jint is null! bean = %p", bean);
            return;
        }
        // Get mMoney
        jfieldID okField = env->GetFieldID(beanClazz, "mOk", "Z");
        if (okField == nullptr) {
            LOGE("TransObject -> mOk jfieldID is null! bean = %p", bean);
            return;
        }
        jboolean okBoolean = (jint) env->GetBooleanField(bean, okField);
        LOGI("TransObject -> bean info, name = %s, age = %d, money = %lld, ok = %d", nameChar, ageInt, moneyLong, okBoolean);
    }
}