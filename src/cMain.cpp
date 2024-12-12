#include <iostream>

#include "cMain.hpp"

/*
    to use, run following commands:
        cd build/
        cmake .. && cmake --build . && ./raytracer
*/

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Testing wxWidgets", wxDefaultPosition, {600, 400})
{}

cMain::~cMain()
{}