#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow *parent) : MyFrame1(parent) {
//    this->SetBackgroundColour(wxColor(192, 192, 192));
    m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
    m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update(wxUpdateUIEvent &) {
    Repaint();
}

void GUIMyFrame1::m_b_grayscale_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.ConvertToGreyscale();
    Repaint();
}

void GUIMyFrame1::m_b_blur_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Blur(5);
    Repaint();
}

void GUIMyFrame1::m_b_mirror_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Mirror();
    Repaint();
}

void GUIMyFrame1::m_b_replace_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
    Repaint();
}

void GUIMyFrame1::m_b_rescale_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.Rescale(320, 240);
    Repaint();
}

void GUIMyFrame1::m_b_rotate_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Rotate(30 * M_PI / 180,
                             wxPoint(Img_Org.GetWidth(), Img_Org.GetHeight()));
    Repaint();
}

void GUIMyFrame1::m_b_rotate_hue_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.RotateHue(0.5);
    Repaint();
}

void GUIMyFrame1::m_b_mask_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
    Repaint();
}

void GUIMyFrame1::m_s_brightness_scroll(wxScrollEvent &) {
    Brightness(m_s_brightness->GetValue() - 100);
    Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll(wxScrollEvent &) {
    Contrast(m_s_contrast->GetValue() - 100);
    Repaint();
}

void GUIMyFrame1::m_b_prewitt_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Copy();
    const unsigned char *temp = Img_Org.GetData();
    unsigned char *data = Img_Cpy.GetData();

    int PrewittMatrix[3][3] = {
            {-1, 0, 1},
            {-1, 0, 1},
            {-1, 0, 1}
    };

    for (int y = 1; y < Img_Cpy.GetHeight() - 1; ++y) {
        for (int x = 1; x < Img_Cpy.GetWidth() - 1; ++x)
            for (int c = 0; c < 3; ++c) {
                int sum =
                        temp[IdxOf(x - 1, y - 1, c)] * PrewittMatrix[0][0] +
                        temp[IdxOf(x - 1, y, c)] * PrewittMatrix[0][1] +
                        temp[IdxOf(x - 1, y + 1, c)] * PrewittMatrix[0][2] +
                        temp[IdxOf(x, y - 1, c)] * PrewittMatrix[1][0] +
                        temp[IdxOf(x, y, c)] * PrewittMatrix[1][1] +
                        temp[IdxOf(x, y + 1, c)] * PrewittMatrix[1][2] +
                        temp[IdxOf(x + 1, y - 1, c)] * PrewittMatrix[2][0] +
                        temp[IdxOf(x + 1, y, c)] * PrewittMatrix[2][1] +
                        temp[IdxOf(x + 1, y + 1, c)] * PrewittMatrix[2][2];

                if (sum > 255) sum = 255;
                else if (sum < 0) sum = 0;
                data[IdxOf(x, y, c)] = static_cast<unsigned char>(sum);
            }
    }
}

void GUIMyFrame1::m_b_threshold_click(wxCommandEvent &) {
    Img_Cpy = Img_Org.Copy();
    unsigned char *data = Img_Cpy.GetData();
    for (int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; ++i) {
        if (data[i] < 128) data[i] = 0;
        else data[i] = 255;
    }
}


void GUIMyFrame1::Contrast(int value) {
    Img_Cpy = Img_Org.Copy();
    unsigned char *data = Img_Cpy.GetData();
    double V = 1.2725 * value;
    double V1 = 255 / (255 - 2 * V);
    double V2 = (255 + 2 * V) / 255;
    for (int i = 0; i <= Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; ++i) {
        if (V > 0)
            data[i] = (data[i] < V) ? 0 : (data[i] > 255 - V)
                                          ? 255 : V1 * (data[i] - V);
        else if (V < 0) data[i] = -V + V2 * data[i];
    }
}

void GUIMyFrame1::Repaint() {
    wxBitmap bitmap(Img_Cpy);
    wxClientDC dc(m_scrolledWindow);
    dc.Clear();
    m_scrolledWindow->DoPrepareDC(dc);
    dc.DrawBitmap(bitmap, 0, 0, true);
}

void GUIMyFrame1::Brightness(int value) {
    Img_Cpy = Img_Org.Copy();
    unsigned char *data = Img_Cpy.GetData();
    for (int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; ++i) {
        if ((data[i] + value) > 255) data[i] = 255;
        else if ((data[i] + value) < 0) data[i] = 0;
        else data[i] += value;
    }
}

int GUIMyFrame1::IdxOf(int x, int y, int c) {
    return y * Img_Cpy.GetWidth() * 3 + x * 3 + c;
}
