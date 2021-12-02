//
// Created by ZaneWang on 2021/12/2.
//

#include "Complex.h"

Complex::Complex() {
    m_real = 0.0;
    m_image = 0.0;
    LOGD(BASETAG, "Create complex = %p | real = 0 | image = 0", this);
}

Complex::Complex(double real, double image) {
    m_real = real;
    m_image = image;
    LOGD(BASETAG, "Create complex(double real, double image) = %p | real = %lf | image = %lf", this, m_real, m_image);
}

Complex::Complex(const Complex &complex) {
    m_real = complex.m_real;
    m_image = complex.m_image;
    LOGD(BASETAG, "Create complex(const Complex &complex) = %p | real = %lf | image = %lf", this, m_real, m_image);
}

Complex::~Complex() {
    LOGD(BASETAG, "Destroy complex = %p", this);
}

double Complex::getReal() const {
    return m_real;
}

void Complex::setReal(double real) {
    m_real = real;
}

double Complex::getImage() const {
    return m_image;
}

void Complex::setImage(double mImage) {
    m_image = mImage;
}

Complex& Complex::operator+(const Complex &complex) {
    LOGD(BASETAG, "operator+ invoked! complex = %p | this = %p", &complex, this);
    m_real += complex.m_real;
    m_image += complex.m_image;
    return *this;
}

Complex& Complex::operator=(const Complex &complex) {
    LOGD(BASETAG, "operator= invoked! complex = %p | this = %p", &complex, this);
    m_real = complex.m_real;
    m_image = complex.m_image;
    return *this;
}
