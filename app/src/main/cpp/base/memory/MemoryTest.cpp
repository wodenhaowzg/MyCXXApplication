//
// Created by ZaneWang on 2021/3/30.
//

#include <jni.h>
#include <malloc.h>
#include <cstdint>
#include <string.h>
#include "libyuv/convert.h"

struct DataStruct {
    uint8_t *data;
};

static DataStruct *dataStruct;

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_MemoryTest_testFreeData(JNIEnv *env, jobject thiz, jbyteArray buf, jint len, jint width, jint height) {
    jbyte *tempBuf = env->GetByteArrayElements(buf, nullptr);

    if (dataStruct != nullptr){
        free(dataStruct->data); // 必须先释放掉指针对象
        delete dataStruct; // BUG 如果只是删除结构体对象，结构体内部的指针对象会泄露。
    }

    uint8_t *data = (uint8_t *) malloc(len);
    memcpy(data, tempBuf, len);
    dataStruct = new DataStruct();
    dataStruct->data = data;

    env->ReleaseByteArrayElements(buf, tempBuf, 0);
}
