#include <wx/wx.h>
#include "GUIMyFrame1.h"

double Point(double w1, double w2, double p1, double p2, double val) {
    if (w2 > w1) {
        if (val > w2 || val < w1) return (-10);
        else return (p1 + (p2 - p1) * ((val - w1) / (w2 - w1)));
    }
    if (w2 < w1) {
        if (val < w2 || val > w1) return (-10);
        else return (p2 + (p1 - p2) * ((val - w2) / (w1 - w2)));
    }
    if (w1 == val) return (p1); else return (-10);
}

void DrawContour(wxDC &dc, double p[4][2], double w[4], double val) {
    double d[4];
    int x1, y1;
    d[0] = Point(w[0], w[1], p[0][1], p[1][1], val);
    d[1] = Point(w[1], w[2], p[1][0], p[2][0], val);
    d[2] = Point(w[2], w[3], p[2][1], p[3][1], val);
    d[3] = Point(w[3], w[0], p[3][0], p[0][0], val);

    if (d[0] > -10) {
        x1 = p[0][0] * 100;
        y1 = d[0] * 100;
        if (d[1] > -10) dc.DrawLine(x1, y1, d[1] * 100, p[1][1] * 100);
        else if (d[2] > -10) dc.DrawLine(x1, y1, p[2][0] * 100, d[2] * 100);
        else if (d[3] > -10) dc.DrawLine(x1, y1, d[3] * 100, p[3][1] * 100);
    } else if (d[1] > -10) {
        y1 = p[1][1] * 100;
        x1 = d[1] * 100;
        if (d[2] > -10) dc.DrawLine(x1, y1, p[2][0] * 100, d[2] * 100);
        else if (d[3] > -10) dc.DrawLine(x1, y1, d[3] * 100, p[3][1] * 100);
    } else if (d[2] > -10) {
        x1 = p[2][0] * 100;
        y1 = d[2] * 100;
        if (d[3] > -10) dc.DrawLine(x1, y1, d[3] * 100, p[3][1] * 100);
    }

}

float Shepard(int N, float d[100][3], float x, float y) {
    float weight, numerator, denominator;
    numerator = denominator = 0;
    for (int i = 0; i < N; ++i) {
        weight = 1.f / (fabs(pow((x - d[i][0]), 2) + pow((y - d[i][1]), 2)));
        numerator += d[i][2] * weight;
        denominator += weight;
    }
    return numerator / denominator;
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType,
                          int NoLevels, bool ShowPoints) {
    wxMemoryDC memDC;
    memDC.SelectObject(MemoryBitmap);
    memDC.SetBackground(*wxWHITE_BRUSH);
    memDC.Clear();

    memDC.SetDeviceOrigin(250, 250);
    memDC.SetPen(*wxBLACK_PEN);
    memDC.SetBrush(*wxTRANSPARENT_BRUSH);

    double min, max;
    min = max = d[0][2];
    for (float i = 2.5; i > -2.5; i -= 0.1)
        for (float j = 2.5; j > -5; j -= 0.1) {
            float val = Shepard(N, d, i, j);
            if (val < min)
                min = val;
            else if (val > max)
                max = val;
        }

    if (MappingType) {
        if (MappingType == 1)
            drawBlueRed(memDC, min, max);
        else if (MappingType == 2)
            drawBlueGreenRed(memDC, min, max);
        else if (MappingType == 3)
            drawGray(memDC, min, max);
    }

    if (Contour) {
        double p[4][2];
        double w[4];
        memDC.SetPen(*wxBLACK_PEN);
        for (float i = 2.5; i > -2.5; i -= 0.1f)
            for (float j = 2.5; j > -5; j -= 0.1f) {
                p[0][0] = i;
                p[0][1] = j;
                p[1][0] = i;
                p[1][1] = j + 0.1;
                p[2][0] = i + 0.1;
                p[2][1] = j + 0.1;
                p[3][0] = i + 0.1;
                p[3][1] = j;

                w[0] = Shepard(N, d, i, j);
                w[1] = Shepard(N, d, i, j + 0.1f);
                w[2] = Shepard(N, d, i + 0.1f, j + 0.1f);
                w[3] = Shepard(N, d, i + 0.1f, j);
                for (int k = 1; k <= NoLevels; ++k) {
                    DrawContour(memDC, p, w,
                                min + (max - min) * k / (NoLevels + 1));
                }
            }
    }

    if (ShowPoints) {
        memDC.SetPen(*wxBLACK_PEN);
        for (int i = 0; i < N; ++i) {
            memDC.DrawLine(d[i][0] * 100 - 3, d[i][1] * 100, d[i][0] * 100 + 4,
                           d[i][1] * 100);
            memDC.DrawLine(d[i][0] * 100, d[i][1] * 100 - 3, d[i][0] * 100,
                           d[i][1] * 100 + 4);
        }
    }
}


void GUIMyFrame1::drawBlueRed(wxMemoryDC &dc, double max, double min) {
    int r, g, b;
    float val;
    for (int i = -250; i < 250; ++i)
        for (int j = -250; j < 250; ++j) {
            val = Shepard(NoPoints, FunctionData, i / 100.f, j / 100.f);
            r = 255 - ((val - min) / (max - min)) * 255;
            g = 0;
            b = 255 - r;

            if (r < 0) r = 0;
            if (r > 255) r = 255;
            if (g < 0) g = 0;
            if (g > 255) g = 255;
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            dc.SetPen(wxPen(wxColour(r, g, b)));
            dc.DrawPoint(i, j);
        }
}

void GUIMyFrame1::drawBlueGreenRed(wxMemoryDC &dc, double max, double min) {
    int r, g, b;
    float val;
    for (int i = -250; i < 250; ++i)
        for (int j = -250; j < 250; ++j) {
            val = Shepard(NoPoints, FunctionData, i / 100.f, j / 100.f);
            r = 255 - ((val - min) / (max - min)) * 255;
            b = 255 - r;

            if ((val - min) / (max - min) < 0.5)
                g = ((val - min) / (max - min)) * 255 * 2;
            else
                g = 255 * 2 - ((val - min) / (max - min)) * 255 * 2;

            if (r < 0) r = 0;
            if (r > 255) r = 255;
            if (g < 0) g = 0;
            if (g > 255) g = 255;
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            dc.SetPen(wxPen(wxColour(r, g, b)));
            dc.DrawPoint(i, j);
        }
}

void GUIMyFrame1::drawGray(wxMemoryDC &dc, double max, double min) {
    int r, g, b;
    float val;
    for (int i = -250; i < 250; ++i)
        for (int j = -250; j < 250; ++j) {
            val = Shepard(NoPoints, FunctionData, i / 100.f, j / 100.f);
            r = ((val - min) / (max - min)) * 255;
            g = ((val - min) / (max - min)) * 255;
            b = ((val - min) / (max - min)) * 255;

            if (r < 0) r = 0;
            if (r > 255) r = 255;
            if (g < 0) g = 0;
            if (g > 255) g = 255;
            if (b < 0) b = 0;
            if (b > 255) b = 255;
            dc.SetPen(wxPen(wxColour(r, g, b)));
            dc.DrawPoint(i, j);
        }
}