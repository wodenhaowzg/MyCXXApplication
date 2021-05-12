//
// Created by ZaneWang on 2021/4/17.
//
#include "BaseObject.h"
#include <vector>
void printVector(vector<int> &vec, stringstream &ss);

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_CollectionTest_arrayTest(JNIEnv *env, jobject thiz) {
    // 定义一个字符串buffer
    stringstream ss;
    // 栈定义：申请一个数组对象
    int array1[] = {1, 2, 3, 4, 5};
    // 计算数组长度
    int array1_len = sizeof(array1) / sizeof(array1[0]);
    // 遍历数组
    for (int i = 0; i < array1_len; ++i) {
        ss << "index: " << i << " - element: " << array1[i] << "\n";
    }
    LOGI(BASETAG, ss.str().c_str());
    // 重置字符串buffer
    // 重置状态
    ss.clear();
    // 重置内容
    ss.str("");
    for (int element : array1) {
        ss << "element: " << element << "\n";
    }
    LOGI(BASETAG, ss.str().c_str());

    // --------------------------------------------------------------------------------

    // 堆定义：指针数组
    ss.clear();
    ss.str("");
    ss << "----------------------------------------- Pointer array test -----------------------------------------" << "\n";
    LOGI(BASETAG, ss.str().c_str());

    ss.clear();
    ss.str("");
    int *array2 = array1;
    for (int i = 0; i < array1_len; i++) {
        ss << "index: " << i << " - element: " << *(array2 + i) << " | " << array2 + i << "\n";
    }
    LOGI(BASETAG, ss.str().c_str());
}

extern "C" JNIEXPORT void JNICALL Java_com_example_mycxxapplication_jni_CollectionTest_vectorTest(JNIEnv *env, jobject thiz) {
    // 定义一个字符串buffer
    stringstream ss;
    ss << "----------------------------------------- Vector test -----------------------------------------" << "\n";
    LOGI(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");

    // 定义一个 vector 集合
    vector<int> vec = {1, 2, 3, 4, 5};
    // 打印集合
    printVector(vec, ss);
    // 增加
    // 从尾部添加一个元素
    vec.push_back(6);
    printVector(vec, ss);
    // 插入指定位置
    vec.insert(vec.begin(), 7);
    printVector(vec, ss);
    vec.insert(vec.end() - 1, 8);
    printVector(vec, ss);

    // 删除
    // 从尾部删除一个元素
    vec.pop_back();
    printVector(vec, ss);
    // 移除一个任意位置上的元素
    vec.erase(vec.begin());
    printVector(vec, ss);

    // 修改和查询通过角标完成
    vec[0] = 100;
    printVector(vec, ss);
}

void printVector(vector<int> &vec, stringstream &ss){
    for (int i = 0; i < vec.size(); ++i) {
        ss << "index: " << i << " - element: " << vec[i] << " | size: " << vec.size() << " | capacity: " << vec.capacity() << "\n";
    }
    LOGI(BASETAG, ss.str().c_str());
    ss.clear();
    ss.str("");
}
