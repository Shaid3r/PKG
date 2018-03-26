#include "RightPanel.h"
#include <wx/colordlg.h>

BEGIN_EVENT_TABLE(RightPanel, wxPanel)
                EVT_BUTTON(RightPanel::SAVE_BUTTON, RightPanel::onSaveButton)
                EVT_BUTTON(RightPanel::STAR_COLOUR_BUTTON,
                           RightPanel::onColourChange)
                EVT_CHOICE(RightPanel::CHOICES, RightPanel::onChoice)
                EVT_TEXT(RightPanel::TEXT_CTRL, RightPanel::onTextCtrl)
                EVT_CHECKBOX(RightPanel::BANANA_CHECKBOX,
                             RightPanel::onToogleBanana)
                EVT_COMMAND_SCROLL(RightPanel::BANANA_SCROLL_BAR,
                                   RightPanel::onBananaScroll)
END_EVENT_TABLE()

RightPanel::RightPanel(wxFrame *parent, MonkeyPanel *monkey) : wxPanel(parent) {
    this->SetBackgroundColour(wxColour(255, 220, 0));
    this->monkeyPanel = monkey;
    draw();
}

void RightPanel::draw() {
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    auto saveButton = new wxButton(this, SAVE_BUTTON, _T("Zapis do pliku"));
    vbox->Add(saveButton, 0, wxALL | wxCENTER, 10);

    bananaCheckBox = new wxCheckBox(this, BANANA_CHECKBOX, _T("banan"));
    vbox->Add(bananaCheckBox, 0, wxALL | wxCENTER, 10);

    bananaScrollBar = new wxScrollBar(this, BANANA_SCROLL_BAR);
    bananaScrollBar->Disable();
    bananaScrollBar->SetScrollbar(0, 15, 115, 10);
    vbox->Add(bananaScrollBar, 0, wxEXPAND | wxALL,
              10);

    progress = new wxGauge(this, wxID_ANY, 100);
    vbox->Add(progress, 0,
              wxALL | wxCENTER | wxEXPAND, 10);

    auto starColorButton = new wxButton(this, STAR_COLOUR_BUTTON,
                                        _T("kolor gwiazdki"));
    vbox->Add(starColorButton, 0, wxALL | wxCENTER, 10);

    this->textCtrl = new wxTextCtrl(this, TEXT_CTRL, "tekst");
    vbox->Add(textCtrl, 0, wxALL | wxCENTER,
              10);

    choice = new wxChoice(this, CHOICES);
    choice->Append(_T("gwiazdka"));
    choice->Append(_T("księżyc"));
    choice->Append(_T("słonko"));
    choice->Select(0);
    vbox->Add(choice, 0, wxALL | wxEXPAND, 10);

    saveFileDialog = new wxFileDialog(this, _("Wybierz plik do zapisu"), "",
                                      "obrazek.png",
                                      wxFileSelectorDefaultWildcardStr,
                                      wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    this->SetSizer(vbox);
}

void RightPanel::onChoice(wxCommandEvent &) {
    switch (choice->GetCurrentSelection()) {
        case 1:
            monkeyPanel->setChoice(MonkeyPanel::Choice::SUN);
            break;
        case 2:
            monkeyPanel->setChoice(MonkeyPanel::Choice::MOON);
            break;
        default:
            monkeyPanel->setChoice(MonkeyPanel::Choice::STAR);
            break;
    }
}

void RightPanel::onToogleBanana(wxCommandEvent &) {
    monkeyPanel->toogleBanana();
    if (bananaScrollBar->IsEnabled())
        bananaScrollBar->Disable();
    else
        bananaScrollBar->Enable();
}

void RightPanel::onBananaScroll(wxScrollEvent &) {
    int pos = bananaScrollBar->GetThumbPosition();
    progress->SetValue(pos);
    monkeyPanel->setPercent(static_cast<float>(pos) / progress->GetRange());
}

void RightPanel::onTextCtrl(wxCommandEvent &event) {
    monkeyPanel->setText(event.GetString());
}

void RightPanel::onSaveButton(wxCommandEvent &) {
    if (saveFileDialog->ShowModal() == wxID_OK) {
        auto filename = saveFileDialog->GetPath();
        wxBitmap bitmap(monkeyPanel->GetSize());
        wxMemoryDC dc(bitmap);
        monkeyPanel->draw(dc);
        dc.SelectObject(wxNullBitmap);
        bitmap.ConvertToImage().SaveFile(filename);
    }
}

void RightPanel::onColourChange(wxCommandEvent &) {
    wxColourDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        wxColour colour = dialog.GetColourData().GetColour();
        monkeyPanel->setStarColour(colour);
    }
}