#pragma once

#include <wx/wxprec.h>
#include "MonkeyPanel.h"

class RightPanel : public wxPanel {
public:
    RightPanel(wxFrame *parent, MonkeyPanel *monkey);

private:
    void draw();

    void onChoice(wxCommandEvent &);
    void onToogleBanana(wxCommandEvent &);
    void onColourChange(wxCommandEvent &);
    void onSaveButton(wxCommandEvent &);
    void onBananaScroll(wxScrollEvent &);
    void onTextCtrl(wxCommandEvent &event);

    wxFileDialog *saveFileDialog;
    wxCheckBox *bananaCheckBox;
    MonkeyPanel *monkeyPanel;
    wxScrollBar *bananaScrollBar;
    wxGauge *progress;
    wxChoice *choice;
    wxTextCtrl *textCtrl;

    enum {
        CHOICES = wxID_HIGHEST,
        BANANA_CHECKBOX,
        SAVE_BUTTON,
        STAR_COLOUR_BUTTON,
        BANANA_SCROLL_BAR,
        TEXT_CTRL
    };

DECLARE_EVENT_TABLE()
};
