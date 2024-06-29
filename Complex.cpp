//
// Created by alon on 6/29/24.
//

#include "Complex.hpp"
Complex  Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}


bool Complex::operator>(const Complex& other) const {
    return (real + imag) * (real + imag) > (other.real + other.imag) * (other.real + other.imag);
}

bool Complex::operator<(const Complex& other) const{
    return other > *this;
}

std::ostream& operator<<(std::ostream& out, const Complex& c) {
    out << "(" << c.real << " + " << c.imag << "i)";
    return out;
}
