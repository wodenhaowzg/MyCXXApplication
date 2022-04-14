//
// Created by ZaneWang on 2021/12/2.
//

#include "MyString.h"

MyString::MyString(const char *charStr) {
    if (charStr == nullptr) {
        m_data = new char[1];
        *m_data = '\0';
    } else {
        int len = strlen(charStr);
        m_data = new char[len + 1];
        assert(m_data != nullptr);
        strcpy(m_data, charStr);
    }
}

MyString::MyString(const MyString &string) {

}

MyString::~MyString() {

}
