//
// Created by ZaneWang on 2020/7/26.
//

#ifndef MYCXXAPPLICATION_THREADUTILS_H
#define MYCXXAPPLICATION_THREADUTILS_H


class ThreadUtils {

public:
    /**
     * 获取当前线程 ID
     * @return 返回当前线程 ID
     */
    static int GetCurrentThreadId();

    /**
     * 当前线程睡眠
     * @param duration 睡眠时长，单位 ms
     */
    static void Sleep(unsigned int duration);
};


#endif //MYCXXAPPLICATION_THREADUTILS_H
