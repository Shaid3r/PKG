#include "GUIMyFrame1.h"
#include "ConfigClass.h"
#include "ChartClass.h"

GUIMyFrame1::GUIMyFrame1(wxWindow *parent) : MyFrame1(parent) {
    WxScrollBar_alpha->SetScrollbar(0, 1, 360, 1, true);
    cfg = std::make_shared<ConfigClass>(this);
    Ly_min->SetLabel(
            wxString::Format(wxT("%2.4lf"), ChartClass(cfg).Get_Y_min()));
    Ly_max->SetLabel(
            wxString::Format(wxT("%2.4lf"), ChartClass(cfg).Get_Y_max()));
}

void GUIMyFrame1::MainFormClose(wxCloseEvent &) {
    Destroy();
}

void GUIMyFrame1::WxPanel_Repaint(wxUpdateUIEvent &) {
    Repaint();
}

void GUIMyFrame1::WxEdit_x0_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_x0->GetValue().ToDouble(&v)) {
        cfg->Set_x0(v);
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxEdit_y0_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_y0->GetValue().ToDouble(&v)) {
        cfg->Set_y0(v);
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxEdit_x1_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_x1->GetValue().ToDouble(&v)) {
        cfg->Set_x1(v);
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxEdit_y1_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_y1->GetValue().ToDouble(&v)) {
        cfg->Set_y1(v);
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxScrollBar_alpha_Update(wxScrollEvent &) {
    WxStaticText_alpha->SetLabel(
            wxString::Format(wxT("%d"), WxScrollBar_alpha->GetThumbPosition()));
    cfg->Set_Alpha(WxScrollBar_alpha->GetThumbPosition());
    Repaint();
}

void GUIMyFrame1::WxRB_Middle_Click(wxCommandEvent &) {
    cfg->SetRotateScreen(true);
    Repaint();
}

void GUIMyFrame1::WxRB_Center_Click(wxCommandEvent &) {
    cfg->SetRotateScreen(false);
    Repaint();
}

void GUIMyFrame1::WxEdit_dX_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_dX->GetValue().ToDouble(&v)) {
        cfg->Set_dX(v);
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxEdit_dY_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_dY->GetValue().ToDouble(&v)) {
        cfg->Set_dY(v);
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxEdit_x_start_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_x_start->GetValue().ToDouble(&v)) {
        cfg->Set_x_start(v);
        Ly_min->SetLabel(
                wxString::Format(wxT("%2.4lf"), ChartClass(cfg).Get_Y_min()));
        Ly_max->SetLabel(
                wxString::Format(wxT("%2.4lf"), ChartClass(cfg).Get_Y_max()));
        Layout();
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxEdit_x_stop_Update(wxCommandEvent &) {
    double v;
    if (WxEdit_x_stop->GetValue().ToDouble(&v)) {
        cfg->Set_x_stop(v);
        Ly_min->SetLabel(
                wxString::Format(wxT("%2.4lf"), ChartClass(cfg).Get_Y_min()));
        Ly_max->SetLabel(
                wxString::Format(wxT("%2.4lf"), ChartClass(cfg).Get_Y_max()));
        Layout();
        Repaint();
    } else wxBell();
}

void GUIMyFrame1::WxChoice_Selected(wxCommandEvent &) {
    cfg->Set_F_type(WxChoice->GetSelection());
}

void GUIMyFrame1::m_button1_click(wxCommandEvent &) {
    WxEdit_x0->SetValue(WxEdit_x_start->GetValue());
    WxEdit_x1->SetValue(WxEdit_x_stop->GetValue());
    Repaint();
}

void GUIMyFrame1::m_button2_click(wxCommandEvent &) {
    wxFileDialog WxOpenFileDialog(this, _("Wybierz plik"), _(""), _(""),
                                  _("config files (*.cfg)|*.cfg"), wxFD_OPEN);
    if (WxOpenFileDialog.ShowModal() == wxID_OK)
        cfg->Load(
                (const_cast<char *>((const char *) WxOpenFileDialog.GetPath().mb_str())));
}

void GUIMyFrame1::m_button3_click(wxCommandEvent &) {
    wxFileDialog WxSaveFileDialog(this, _("Wybierz plik"), _(""), _(""),
                                  _("config files (*.cfg)|*.cfg"), wxFD_SAVE);
    if (WxSaveFileDialog.ShowModal() == wxID_OK)
        cfg->Save(
                (const_cast<char *>((const char *) WxSaveFileDialog.GetPath().mb_str())));
}


GUIMyFrame1::~GUIMyFrame1() {

}

void GUIMyFrame1::Repaint() {
    wxClientDC dc1(WxPanel);
    wxBufferedDC dc(&dc1);

    ChartClass MyChart(cfg);
    int w, h;
    WxPanel->GetSize(&w, &h);
    MyChart.Draw(&dc, w, h);
}

void GUIMyFrame1::UpdateControls() {
    WxEdit_x0->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_x0()));
    WxEdit_x1->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_x1()));
    WxEdit_y0->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_y0()));
    WxEdit_y1->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_y1()));
    WxEdit_dX->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_dX()));
    WxEdit_dY->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_dY()));
    WxEdit_x_start->SetLabel(
            wxString::Format(wxT("%2.1lf"), cfg->Get_x_start()));
    WxEdit_x_stop->SetLabel(wxString::Format(wxT("%2.1lf"), cfg->Get_x_stop()));
    WxScrollBar_alpha->SetThumbPosition(int(cfg->Get_Alpha()));
    WxStaticText_alpha->SetLabel(
            wxString::Format(wxT("%d"), WxScrollBar_alpha->GetThumbPosition()));
}