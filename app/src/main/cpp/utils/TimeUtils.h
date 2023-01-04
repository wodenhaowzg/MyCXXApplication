//
// Created by ZaneWang on 2020/7/26.
//

#ifndef MYCXXAPPLICATION_TIMEUTILS_H
#define MYCXXAPPLICATION_TIMEUTILS_H

#include "Timers.h"

class TimeUtils {

public:
    static long long currentTimeMillis();

    static long long nanoTime();

    static long long uptimeMillis();
};


#endif //MYCXXAPPLICATION_TIMEUTILS_H
