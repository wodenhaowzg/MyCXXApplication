//
// Created by ZaneWang on 2021/12/2.
//

#ifndef MYCXXAPPLICATION_COMPLEX_H
#define MYCXXAPPLICATION_COMPLEX_H

#include "../BaseObject.h"
#include <iostream>

class Complex {

private:
    double m_real = 0.0;
    double m_image = 0.0;

public:
    /**
     * 默认构造
     */
    Complex();

    /**
     * 有参构造
     * @param real
     * @param image
     */
    Complex(double real, double image);

    /**
     * 拷贝构造
     * @param complex
     */
    Complex(const Complex &complex);

    /**
     * 析构函数
     */
    ~Complex();

    double getReal() const;

    void setReal(double real);

    double getImage() const;

    void setImage(double mImage);

//    Complex* operator+(const Complex& complex);
    Complex &operator+(const Complex &complex);

    Complex &operator=(const Complex &complex);
};


#endif //MYCXXAPPLICATION_COMPLEX_H
