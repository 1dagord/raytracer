#include "cApp.hpp"


wxIMPLEMENT_APP(cApp);

cApp::cApp () {

};

cApp::~cApp () {
    
};

bool cApp::OnInit () {
    main_frame = new cMain();
    main_frame->Show();
    
    return true;
}