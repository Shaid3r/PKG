#include "GUIMyFrame1.h"
#include <fstream>


GUIMyFrame1::GUIMyFrame1(wxWindow *parent) : MyFrame1(parent) {
    m_button_load_geometry->SetLabel(wxT("Wczytaj Geometrię"));
    m_staticText25->SetLabel(wxT("Obrót X:"));
    m_staticText27->SetLabel(wxT("Obrót Y:"));
    m_staticText29->SetLabel(wxT("Obrót Z:"));

    WxSB_TranslationX->SetRange(0, 200);
    WxSB_TranslationX->SetValue(100);
    WxSB_TranslationY->SetRange(0, 200);
    WxSB_TranslationY->SetValue(100);
    WxSB_TranslationZ->SetRange(0, 200);
    WxSB_TranslationZ->SetValue(100);

    WxSB_RotateX->SetRange(0, 360);
    WxSB_RotateX->SetValue(0);
    WxSB_RotateY->SetRange(0, 360);
    WxSB_RotateY->SetValue(0);
    WxSB_RotateZ->SetRange(0, 360);
    WxSB_RotateZ->SetValue(0);

    WxSB_ScaleX->SetRange(1, 200);
    WxSB_ScaleX->SetValue(100);
    WxSB_ScaleY->SetRange(1, 200);
    WxSB_ScaleY->SetValue(100);
    WxSB_ScaleZ->SetRange(1, 200);
    WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint(wxUpdateUIEvent &) {
    Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click(wxCommandEvent &) {
    wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""),
                                  wxT("Geometry file (*.geo)|*.geo"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (WxOpenFileDialog.ShowModal() == wxID_OK) {
        std::vector<Segment> data;
        double x1, y1, z1, x2, y2, z2;
        int r, g, b;

        std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
        if (in.is_open()) {
            data.clear();
            while (!in.eof()) {
                in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
                data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2),
                                       Color(r, g, b)));
            }
            in.close();
            model = std::make_unique<Object>(this, data);
        }
    }
}

void GUIMyFrame1::Scrolls_Updated(wxScrollEvent &) {
    WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"),
                                                 (WxSB_TranslationX->GetValue() -
                                                  100) / 50.0));
    WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"),
                                                 (WxSB_TranslationY->GetValue() -
                                                  100) / 50.0));
    WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"),
                                                 (WxSB_TranslationZ->GetValue() -
                                                  100) / 50.0));

    WxST_RotateX->SetLabel(
            wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
    WxST_RotateY->SetLabel(
            wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
    WxST_RotateZ->SetLabel(
            wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

    WxST_ScaleX->SetLabel(
            wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
    WxST_ScaleY->SetLabel(
            wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
    WxST_ScaleZ->SetLabel(
            wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));

    Repaint();
}


void GUIMyFrame1::Repaint() {
    wxClientDC dc1(WxPanel);
    wxBufferedDC dc(&dc1);
    dc.Clear();
    wxSize size = WxPanel->GetSize();

    if (model)
        model->Draw(dc, size.GetWidth(), size.GetHeight());
}