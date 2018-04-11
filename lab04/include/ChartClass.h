#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
#include "vecmat.h"

class ChartClass {
public:
    ChartClass(std::shared_ptr<ConfigClass> c);

    void Draw(wxDC *dc, int w, int h);  // rysuje wykres

    void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
    double Get_Y_min(); // zwraca y_min
    double Get_Y_max(); // zwraca y_max
private:
    void line2d(wxDC *dc, int x1, int y1, int x2, int y2, const Matrix &m);
    Matrix RotateMatrix(double alpha);
    Matrix TranslateMatrix(double x, double y);
    Matrix ScaleMatrix(double x, double y);
    void DrawFunc(wxDC *dc, int w, int h, const Matrix &matrix);
    void textXY(wxDC *dc, double x, double y, double val, const Matrix &matrix);

    double GetFunctionValue(double x) const; // zwraca wartosci rysowanej funkcji

    std::shared_ptr<ConfigClass> cfg;
    int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
    double x_min, x_max; // zakres zmiennej x
    double y_min, y_max; // zakres wartosci przyjmowanych przez funkcje
};

#endif
