#include <iostream>

#include "cMain.hpp"

/*
    to use, run following commands:
        cd build/
        cmake .. && cmake --build . && ./raytracer
*/

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Testing wxWidgets", wxDefaultPosition, {800, 600}){
    button1 = new wxButton(this, wxID_ANY, "Click Me", wxPoint(10, 10), wxSize(150, 50));
    tbox1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
    lbox1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

cMain::~cMain()
{}