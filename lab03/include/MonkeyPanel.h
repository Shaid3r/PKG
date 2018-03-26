#pragma once

#include <wx/wxprec.h>

class MonkeyPanel : public wxPanel {
public:
    MonkeyPanel(wxFrame *parent);

    enum Choice {
        STAR, MOON, SUN
    };

    void toogleBanana();
    void draw(wxDC &dc) const;

    void setText(const wxString &text);
    void setStarColour(const wxColour &colour);
    void setChoice(MonkeyPanel::Choice c);
    void setPercent(float p);

private:
    void onPaint(wxPaintEvent &);

    wxString text;
    wxColour starColour, backgroundColour;
    wxBitmap *bananaBitmap;
    Choice choice = STAR;
    bool bananaVisible = false;
    float percent = 0;
DECLARE_EVENT_TABLE()
};
