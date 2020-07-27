//
// Created by ZaneWang on 2020/7/26.
//

#ifndef MYCXXAPPLICATION_TIMEUTILS_H
#define MYCXXAPPLICATION_TIMEUTILS_H

#include "Common.h"
#include <ctime>

static struct timeval tv;

class TimeUtils {

public:
    static long long currentTimeMillis();

    static long long nanoTime();
};


#endif //MYCXXAPPLICATION_TIMEUTILS_H
