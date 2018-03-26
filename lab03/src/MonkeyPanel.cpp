#include "MonkeyPanel.h"


BEGIN_EVENT_TABLE(MonkeyPanel, wxPanel)
                EVT_PAINT(MonkeyPanel::onPaint)
END_EVENT_TABLE()

MonkeyPanel::MonkeyPanel(wxFrame *parent) : wxPanel(parent) {
    backgroundColour.Set("#fff");
    starColour.Set("#000");
    this->SetBackgroundColour(backgroundColour);
    wxInitAllImageHandlers();
    bananaBitmap = new wxBitmap("banan.png");
}

void MonkeyPanel::setStarColour(const wxColour &colour) {
    starColour = colour;
    this->Refresh();
}

void MonkeyPanel::toogleBanana() {
    if (bananaVisible) {
        bananaVisible = false;
    } else {
        bananaVisible = true;
    }
    this->Refresh();
}

void MonkeyPanel::setText(const wxString &text) {
    this->text = text;
    this->Refresh();
}

void MonkeyPanel::draw(wxDC &dc) const {
    wxSize size = GetSize();
    dc.SetDeviceOrigin(size.x / 2, size.y / 2);
    dc.Clear();

    dc.DrawLine(wxPoint(0, 20), wxPoint(0, -95)); // body
    dc.DrawLine(wxPoint(0, -60), wxPoint(40, -30)); // right hand
    dc.DrawLine(wxPoint(0, 20), wxPoint(-40, 50)); // left leg
    dc.DrawLine(wxPoint(0, 20), wxPoint(40, 50)); // right leg

    dc.DrawCircle(0, -120, 30); // head
    dc.DrawCircle(10, -126, 5); // right eye

    // -30, -80
    wxPoint leftHandEnd(-40, -30);
    leftHandEnd.y += (30 - 80) * percent;
    if (bananaVisible) {
        dc.DrawCircle(-13, -126, 5); // left eye
        wxPoint face[] = {wxPoint(-13, -101), wxPoint(0, -95),
                          wxPoint(13, -101)};
        dc.DrawSpline(3, face);

        dc.DrawBitmap(*bananaBitmap, leftHandEnd - wxPoint(30, 20), true);
    } else {
        dc.DrawEllipse(-13, -128, 8, 5); // left eye
        wxPoint face[] = {wxPoint(-13, -101), wxPoint(0, -110),
                          wxPoint(13, -101)};
        dc.DrawSpline(3, face);
    }
    dc.DrawLine(wxPoint(0, -60), leftHandEnd); // left hand

    dc.SetFont(wxFont(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL,
                      wxFONTWEIGHT_LIGHT));
    dc.DrawText(text, -40, 55);
    dc.SetFont(wxFont(38, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC,
                      wxFONTWEIGHT_BOLD));
    dc.DrawRotatedText(text, 70, 40, 90);

    switch (choice) {
        case SUN: {
            dc.SetBrush(wxBrush(wxColour("#f4d942")));
            dc.SetPen(wxPen(wxColour("#f4d942")));
            dc.DrawCircle(-100, -180, 40);
            break;
        }
        case MOON: {
            dc.SetBrush(wxBrush(wxColour("#aaa")));
            dc.SetPen(wxPen(wxColour("#aaa")));
            dc.DrawCircle(-100, -180, 40);
            dc.SetPen(wxPen(wxColour("#fff")));
            dc.SetBrush(wxBrush(wxColour("#fff")));
            dc.DrawCircle(-115, -190, 40);

            dc.SetPen(wxPen(wxColour("#000")));
            dc.SetBrush(wxBrush(wxColour("#000")));
            dc.DrawCircle(-70, -182, 4);
            dc.DrawLine(-84, -160, -75, -155);
            break;

        }
        default: {
            wxPoint star[] = {wxPoint(113, 136), wxPoint(121, 120),
                              wxPoint(103, 111), wxPoint(124, 111),
                              wxPoint(133, 91), wxPoint(140, 100),
                              wxPoint(144, 111), wxPoint(163, 111),
                              wxPoint(148, 118), wxPoint(158, 136),
                              wxPoint(135, 126)};

            dc.SetBrush(wxBrush(starColour));
            dc.SetPen(wxPen(starColour));
            dc.DrawPolygon(11, star, -200, -300);
            dc.SetBrush(wxBrush("#fff"));
            dc.SetPen(wxPen("#fff"));
            wxPoint inside_star[] = {wxPoint(122, 119), wxPoint(125, 112),
                                     wxPoint(144, 112), wxPoint(147, 118),
                                     wxPoint(134, 124)};

            dc.DrawPolygon(5, inside_star, -200, -300);
        }
    }
}

void MonkeyPanel::setChoice(MonkeyPanel::Choice c) {
    choice = c;
    this->Refresh();
}

void MonkeyPanel::setPercent(float p) {
    percent = p;
    this->Refresh();
}

void MonkeyPanel::onPaint(wxPaintEvent &) {
    wxPaintDC dc(this);
    draw(dc);
}
