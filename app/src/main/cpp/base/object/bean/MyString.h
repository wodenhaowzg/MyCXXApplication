//
// Created by ZaneWang on 2021/12/2.
//

#ifndef MYCXXAPPLICATION_MYSTRING_H
#define MYCXXAPPLICATION_MYSTRING_H

#include <cstring>
#include <cassert>

class MyString {

private:
    char* m_data = nullptr;

public:
    MyString(const char* charStr);

    MyString(const MyString& string);

    ~MyString();
};


#endif //MYCXXAPPLICATION_MYSTRING_H
