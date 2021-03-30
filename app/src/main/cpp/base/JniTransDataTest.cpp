//
// Created by ZaneWang on 3/5/21.
//

#include <jni.h>
#include <malloc.h>
#include <cstdint>

struct DataStruct{
    uint8_t *data;
};

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_JNITransDataTest_getDataFromCxx(JNIEnv *env, jobject thiz) {

}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_JNITransDataTest_testFreeData(JNIEnv *env, jobject thiz) {
    uint8_t* data = (uint8_t*)malloc(720 * 1280 * 4);
    DataStruct* frame = new DataStruct();
    frame->data = data;
    delete frame;
}