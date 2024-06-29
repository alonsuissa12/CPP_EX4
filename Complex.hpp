//
// Created by alon on 6/29/24.
//

#ifndef CPP_EX4_COMPLAEX_H
#define CPP_EX4_COMPLAEX_H

#include <iostream>


class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Overload the addition operator
    Complex operator+(const Complex& other) const;

    // Overload the subtraction operator
    Complex operator-(const Complex& other) const;

    // Overload the equality operator
    bool operator==(const Complex& other) const;

    // Overload the inequality operator
    bool operator!=(const Complex& other) const;

    // Overload the comparison operator (>)
    bool operator>(const Complex& other) const;

    // Overload the comparison operator (<)
    bool operator<(const Complex& other) const;

    // Overload the stream insertion operator (for output)
    friend std::ostream& operator<<(std::ostream& out, const Complex& c);

};



#endif //CPP_EX4_COMPLAEX_H
