#include <wx/dc.h>
#include <memory>
#include <sstream>
#include <iomanip>

#include "ChartClass.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) {
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range() {
    double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    xmin = cfg->Get_x_start();
    xmax = cfg->Get_x_stop();

    step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double) x_step;
    x = cfg->Get_x_start();

    for (i = 0; i <= x_step; i++) {
        y = GetFunctionValue(x);
        if (y > ymax) ymax = y;
        if (y < ymin) ymin = y;
        x = x + step;
    }

    y_min = ymin;
    y_max = ymax;
    x_min = xmin;
    x_max = xmax;
}


double ChartClass::GetFunctionValue(double x) {
    if (cfg->Get_F_type() == 1) return x * x;
    if (cfg->Get_F_type() == 2) return 0.5 * exp(4 * x - 3 * x * x);
    return x + sin(x * 4.0);
}

double ChartClass::Get_Y_min() {
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() {
    Set_Range();
    return y_max;
}

void ChartClass::Draw(wxDC *dc, int w, int h) {
    dc->SetBackground(wxBrush(wxColour(255, 255, 255)));
    dc->Clear();
    dc->SetPen(wxPen(wxColour(255, 0, 0)));
    dc->DrawRectangle(10, 10, w - 20, h - 20);

    dc->SetClippingRegion(wxRect(11, 11, w - 22, h - 22));
    dc->SetDeviceOrigin(w / 2, h / 2);

    Matrix t;
    int width = w / 2 - 10;
    int height = h / 2 - 10;

    int moveX = -width + abs(cfg->Get_x0()) * 2 * width /
                      (abs(cfg->Get_x1()) + abs(cfg->Get_x0()));
    int moveY = -height + abs(cfg->Get_y1()) * 2 * height /
                       (abs(cfg->Get_y0()) + abs(cfg->Get_y1()));

    if (cfg->RotateScreenCenter()) {
        t = RotateMatrix(cfg->Get_Alpha() * M_PI / 180);
        t = t * TranslateMatrix(cfg->Get_dX(), cfg->Get_dY());
        t = t * TranslateMatrix(moveX, moveY);
    } else {
        t = TranslateMatrix(cfg->Get_dX(), cfg->Get_dY());
        t = t * TranslateMatrix(moveX, moveY);
        t = t * RotateMatrix(cfg->Get_Alpha() * M_PI / 180);
    }

    double scaleX, scaleY;
    scaleX = 2 / (cfg->Get_x1() - cfg->Get_x0());
    scaleY = 2 / (cfg->Get_y1() - cfg->Get_y0());
    t = t * ScaleMatrix(scaleX, scaleY);

    dc->SetPen(wxPen(wxColour(0, 0, 255)));
    // OX
    line2d(dc, cfg->Get_x_start() * width, 0, cfg->Get_x_stop() * width, 0, t);
    // ticks
    line2d(dc, cfg->Get_x_start() * width / 2, -5 / scaleY,
           cfg->Get_x_start() * width / 2, +5 / scaleY, t);
    text2d(dc, cfg->Get_x_start() * width / 2 - 5, 15, cfg->Get_x_start() / 2,
           t);

    line2d(dc, cfg->Get_x_stop() * width / 3, -5 / scaleY,
           cfg->Get_x_stop() * width / 3, +5 / scaleY, t);
    text2d(dc, cfg->Get_x_stop() * width / 3 - 5, 15, cfg->Get_x_stop() / 3, t);

    line2d(dc, cfg->Get_x_stop() * 2 * width / 3, -5 / scaleY,
           cfg->Get_x_stop() * 2 * width / 3, +5 / scaleY, t);
    text2d(dc, cfg->Get_x_stop() * width * 2 / 3 - 5, 15,
           cfg->Get_x_stop() * 2 / 3, t);

    // OX arrow
    line2d(dc, cfg->Get_x_stop() * width, 0,
           cfg->Get_x_stop() * width - 15 / scaleX,
           -7 / scaleY, t);
    line2d(dc, cfg->Get_x_stop() * width, 0,
           cfg->Get_x_stop() * width - 15 / scaleX,
           7 / scaleY, t);
    // OY
    line2d(dc, 0, -Get_Y_min() * height, 0, -Get_Y_max() * height, t);

    // OY arrow
    line2d(dc, 0, -Get_Y_max() * height, -7 / scaleX,
           -Get_Y_max() * height + 15 / scaleY,
           t);
    line2d(dc, 0, -Get_Y_max() * height, 7 / scaleX,
           -Get_Y_max() * height + 15 / scaleY,
           t);

    // ticks
    line2d(dc, -5 / scaleX, -Get_Y_min() * height / 2, 5 / scaleX,
           -Get_Y_min() * height / 2, t);
    text2d(dc, 15, -Get_Y_min() * height / 2 - 10, Get_Y_min() / 2, t);

    line2d(dc, -5 / scaleX, -Get_Y_max() * height / 3, 5 / scaleX,
           -Get_Y_max() * height / 3, t);
    text2d(dc, 15, -Get_Y_max() * height / 3 - 10, Get_Y_max() / 3, t);

    line2d(dc, -5 / scaleX, -Get_Y_max() * height * 2 / 3, 5 / scaleX,
           -Get_Y_max() * height * 2 / 3, t);
    text2d(dc, 15, -Get_Y_max() * height * 2 / 3 - 10, Get_Y_max() * 2 / 3, t);

    dc->SetPen(wxPen(wxColour(0, 255, 0)));
    switch (cfg->Get_F_type()) {
        case 0:
            DrawFunc1(dc, width, height, t);
            break;
        case 1:
            DrawFunc2(dc, width, height, t);
            break;
        case 2:
            DrawFunc3(dc, width, height, t);
            break;
    }

}

void
ChartClass::line2d(wxDC *dc, int x1, int y1, int x2, int y2, const Matrix &m) {
    Vector begin, end;
    begin.Set(x1, y1);
    end.Set(x2, y2);

    begin = m * begin;
    end = m * end;

    dc->DrawLine(begin.GetX(), begin.GetY(), end.GetX(), end.GetY());
}

Matrix ChartClass::RotateMatrix(double alpha) {
    Matrix matrix;
    matrix.data[0][0] = cos(alpha);
    matrix.data[0][1] = sin(alpha);
    matrix.data[0][2] = 0;
    matrix.data[1][0] = -sin(alpha);
    matrix.data[1][1] = cos(alpha);
    matrix.data[1][2] = 0;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 1;
    return matrix;
}

Matrix ChartClass::TranslateMatrix(double x, double y) {
    Matrix matrix;
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = x;
    matrix.data[1][0] = 0;
    matrix.data[1][1] = 1;
    matrix.data[1][2] = y;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 1;
    return matrix;
}

Matrix ChartClass::ScaleMatrix(double x, double y) {
    Matrix matrix;
    matrix.data[0][0] = x;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[1][0] = 0;
    matrix.data[1][1] = y;
    matrix.data[1][2] = 0;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 1;
    return matrix;
}

void ChartClass::DrawFunc1(wxDC *dc, int w, int h, const Matrix &matrix) {
    double value, nextValue;
    double dx = 0.05;
    double x = cfg->Get_x_start();
    while (x < cfg->Get_x_stop()) {
        value = -(x + sin(4 * x));
        nextValue = -((x + dx) + sin(4 * (x + dx)));
        line2d(dc, x * w, value * h, (x + dx) * w, nextValue * h, matrix);
        x += dx;
    }
}

void ChartClass::DrawFunc2(wxDC *dc, int w, int h,
                           const Matrix &matrix) {
    double value, nextValue;
    double dx = 0.05;
    double x = cfg->Get_x_start();
    while (x < cfg->Get_x_stop()) {
        value = -(x * x);
        nextValue = -((x + dx) * (x + dx));
        line2d(dc, x * w, value * h, (x + dx) * w, nextValue * h, matrix);
        x += dx;
    }
}

void ChartClass::DrawFunc3(wxDC *dc, int w, int h,
                           const Matrix &matrix) {
    double value, nextValue;
    double dx = 0.05;
    double x = cfg->Get_x_start();
    while (x < cfg->Get_x_stop()) {
        value = -0.5 * pow(M_E, 4 * x - 3 * x * x);
        nextValue = -0.5 * pow(M_E, 4 * (x + dx) - 3 * (x + dx) * (x + dx));
        line2d(dc, x * w, value * h, (x + dx) * w, nextValue * h, matrix);
        x += dx;
    }
}

void ChartClass::text2d(wxDC *dc, double x, double y, double val,
                        const Matrix &matrix) {
    Vector v, v2;
    v.Set(x, y);
    v2 = matrix * v;
    std::stringstream s;
    s << std::setprecision(2) << val;
    dc->DrawRotatedText(s.str(), v2.GetX(), v2.GetY(), cfg->Get_Alpha());
}

