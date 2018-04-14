#pragma once

#include <wx/dc.h>
#include <utility>
#include <vector>
#include "GUI.h"
#include "vecmat.h"

struct Point {
    float x, y, z;

    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
    int R, G, B;

    Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
    Point begin, end;
    Color color;

    Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end),
                                                      color(_color) {}
};

class Object {
public:
    Object(MyFrame1 *model, std::vector<Segment> data);

    void Draw(wxDC &dc, int width, int height);

private:
    std::vector<Segment> data;
    MyFrame1 *model;
    float xmin, xmax, ymin, ymax;

    Matrix4 RotateMatrix(double phi_x, double phi_y, double phi_z) const;

    Matrix4 ScaleMatrix(double sx, double sy, double sz) const;

    Matrix4 TranslateMatrix(double tx, double ty, double tz) const;

    Matrix4 fitWindowMatrix(double w, double h);

    Matrix4 PerspectiveMatrix(double p, double width, double height) const;
};



