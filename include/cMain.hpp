#include <wx/wx.h>

class cMain : public wxFrame{
    public:
       cMain();
       ~cMain();

    public:
        wxButton* button1 = nullptr;
        wxTextCtrl* tbox1 = nullptr;
        wxListBox* lbox1 = nullptr;
};