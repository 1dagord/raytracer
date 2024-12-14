#pragma once

#include "linalg.hpp"


class BookTest {
    public:
        Point p;
        Point p_output;
        Vector v;
        Vector v_output;

    public:
        BookTest() {}

        void ChapterTwo();
        void ChapterFour();
        void ChapterFour_Clock();
};