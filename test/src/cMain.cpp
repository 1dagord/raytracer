#include <iostream>

#include "cMain.hpp"

/*
    to use, run following commands:
        cd build/
        cmake .. && cmake --build . && ./test_raytracer
*/

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(1000, cMain::onButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Testing wxWidgets", wxDefaultPosition, wxSize(800, 600)){
    button1 = new wxButton(this, 1000, "Click Me", wxPoint(10, 10), wxSize(150, 50));
    tbox1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
    lbox1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

cMain::~cMain() {}

void cMain::onButtonClicked(wxCommandEvent& evt) {
    lbox1->AppendString(tbox1->GetValue());
    evt.Skip();     // event has been handled
}