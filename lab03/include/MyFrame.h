#pragma once

#include "MonkeyPanel.h"
#include "RightPanel.h"

class MyFrame : public wxFrame {
public:

    MyFrame(const wxSize &size, const wxString &title = _T("Lab03")) :
            wxFrame(nullptr, -1, title) {
        this->SetStatusBar(nullptr);
        this->SetSize(size);
        this->Center();

        initFrame();
    }

private:
    void initFrame() {
        wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
        monkeyPanel = new MonkeyPanel(this);
        rightPanel = new RightPanel(this, monkeyPanel);
        hbox->Add(monkeyPanel, 7, wxEXPAND | wxALL, 3);
        hbox->Add(rightPanel, 3, wxEXPAND | wxALL, 3);

        this->SetSizer(hbox);
        this->SetBackgroundColour(_T("#b0b0b2"));
    }

    void OnExit(wxCommandEvent &) {
        Close(true);
    }

    MonkeyPanel *monkeyPanel;
    RightPanel *rightPanel;
};
