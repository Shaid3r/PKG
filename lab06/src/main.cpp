#include <wx/wx.h>
#include "GUIMyFrame1.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
    virtual int OnExit() { return 0; }
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    GUIMyFrame1 *mainFrame = new GUIMyFrame1(nullptr);

    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxPNGHandler);
    wxImage image;
    {
        wxLogNull logNo;
        if (!image.LoadFile("test.jpg")) {
            wxMessageBox(wxT("Nie udało się załadować obrazka"));
            mainFrame->Destroy();
            return true;
        } else {
            mainFrame->Img_Org = image.Copy();
            mainFrame->Img_Cpy = mainFrame->Img_Org.Copy();
            if (!image.LoadFile("mask.png")) {
                wxMessageBox(wxT("Nie udało się załadowac maski"));
                mainFrame->Destroy();
                return true;
            } else mainFrame->Img_Mask = image.Copy();
        }
    }

    mainFrame->Show(true);
    SetTopWindow(mainFrame);

    return true;
}