#include <wx/wx.h>

#include "cMain.hpp"


class cApp : public wxApp{
    public:
        cApp();
        ~cApp();

    private:
        cMain* main_frame = nullptr;

    public:
        virtual bool OnInit();
};