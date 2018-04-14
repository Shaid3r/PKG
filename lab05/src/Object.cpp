#include <iostream>
#include "Object.h"

Object::Object(MyFrame1 *model, std::vector<Segment> data) : data(
        std::move(data)), model(model) {
    xmin = xmax = this->data[0].begin.x;
    ymin = ymax = this->data[0].begin.y;
    for (Segment s : this->data) {
        if (s.begin.x > xmax) xmax = s.begin.x;
        if (s.end.x > xmax) xmax = s.end.x;
        if (s.begin.y > ymax) ymax = s.begin.y;
        if (s.end.y > ymax) ymax = s.end.y;
        if (s.begin.x < xmin) xmin = s.begin.x;
        if (s.end.x < xmin) xmin = s.end.x;
        if (s.begin.y < ymin) ymin = s.begin.y;
        if (s.end.y < ymin) ymin = s.end.y;
    }
}

void Object::Draw(wxDC &dc, int width, int height) {
    Matrix4 mf = fitWindowMatrix(width, height);
    Matrix4 mt = TranslateMatrix(model->WxSB_TranslationX->GetValue(),
                                 model->WxSB_TranslationY->GetValue(),
                                 model->WxSB_TranslationZ->GetValue());
    Matrix4 mr = RotateMatrix(model->WxSB_RotateX->GetValue(),
                              model->WxSB_RotateY->GetValue(),
                              model->WxSB_RotateZ->GetValue());
    Matrix4 ms = ScaleMatrix(model->WxSB_ScaleX->GetValue(),
                             model->WxSB_ScaleY->GetValue(),
                             model->WxSB_ScaleZ->GetValue());
    double p = 5.0;
    Matrix4 per = PerspectiveMatrix(model->WxSB_TranslationZ->GetValue(), width,
                                    height);
//    Matrix4 transformationMatrix = mf * mt * mr * ms * per;
//    Matrix4 transformationMatrix = per *mf * mt * mr * ms;
    Matrix4 transformationMatrix = mf * mt * mr * ms;
//transformationMatrix.Print();
    for (Segment s : data) {
        Vector4 vs, ve;
        vs.Set(s.begin.x, s.begin.y, s.begin.z);
        ve.Set(s.end.x, s.end.y, s.end.z);

        vs = transformationMatrix * vs;
        ve = transformationMatrix * ve;
        dc.SetPen(wxPen(wxColour(s.color.R, s.color.G, s.color.B)));
        dc.DrawLine(vs.GetX(), vs.GetY(), ve.GetX(), ve.GetY());
    }
}

Matrix4
Object::RotateMatrix(double phi_x, double phi_y = 0, double phi_z = 0) const {
    Matrix4 mx, my, mz;
    double radX = (360 - phi_x) * M_PI / 180.0;
    double radY = (360 - phi_y) * M_PI / 180.0;
    double radZ = (360 - phi_z) * M_PI / 180.0;

    mx.data[0][0] = 1;
    mx.data[1][1] = cos(radX);
    mx.data[1][2] = -sin(radX);
    mx.data[2][1] = sin(radX);
    mx.data[2][2] = cos(radX);
    mx.data[3][3] = 1;

    my.data[0][0] = cos(radY);
    my.data[0][2] = sin(radY);
    my.data[1][1] = 1;
    my.data[2][0] = -sin(radY);
    my.data[2][2] = cos(radY);
    my.data[3][3] = 1;

    mz.data[0][0] = cos(radZ);
    mz.data[0][1] = -sin(radZ);
    mz.data[1][0] = sin(radZ);
    mz.data[1][1] = cos(radZ);
    mz.data[2][2] = 1;
    mz.data[3][3] = 1;

    return mx * my * mz;
}

Matrix4 Object::TranslateMatrix(double tx, double ty, double tz) const {
    Matrix4 m;
    m.data[0][0] = 1;
    m.data[0][3] = tx / 50 - 2;
    m.data[1][1] = 1;
    m.data[1][3] = ty / 50 - 2;
    m.data[2][2] = 1;
    m.data[2][3] = tz / 50 - 2;
    m.data[3][3] = 1;
    return m;
}

Matrix4 Object::ScaleMatrix(double sx, double sy, double sz) const {
    Matrix4 m;
    m.data[0][0] = (sx - 1) / 100.0;
    m.data[1][1] = (sy - 1) / 100.0;
    m.data[2][2] = (sz - 1) / 100.0;
    m.data[3][3] = 1;

    return m;
}

Matrix4 Object::PerspectiveMatrix(double x, double width, double height) const {
    const double n = -1;
    const double f = -4;
    Matrix4 m;
    m.data[0][0] = 2 * n / (xmax - xmin);
    m.data[1][1] = 2 * n / (ymax - ymin);
    m.data[2][2] = -(f + n) / (f - n);
    m.data[3][3] = 0;
    m.data[0][2] = (xmax + xmin) / (xmax - xmin);
    m.data[1][2] = (ymax + ymin) / (ymax - ymin);
    m.data[3][2] = -1;
    m.data[2][3] = -2 * f * n / (f - n);

    return m;
}

Matrix4 Object::fitWindowMatrix(double w, double h) {
    double Sx = w / (xmax - xmin);
    double Sy = -h / (ymax - ymin);

    Matrix4 matrix;
    matrix.data[0][0] = Sx;
    matrix.data[0][3] = xmin - Sx * xmin;
    matrix.data[1][1] = Sy;
    matrix.data[1][3] = ymin + Sy * ymin;

    return matrix;
}
