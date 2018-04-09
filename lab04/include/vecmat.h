#pragma once
//Extremely simple vector and matrix classes by Janusz Malinowski.
#include <cstdio>

class Vector {
public:
    Vector();

    void Print();

    void Set(double d1, double d2);
    double GetX();
    double GetY();

    double data[3];
};

class Matrix {
public:
    Matrix();
    void Print();
    Matrix operator*(const Matrix);
    friend Vector operator*(const Matrix, const Vector);

    double data[3][3];
};
