#include "cApp.hpp"


wxIMPLEMENT_APP(cApp);

cApp::cApp () {

};

cApp::~cApp () {
    
};

bool cApp::OnInit () {
    mainframe = new cMain();
    mainframe->Show();
    
    return true;
}