#pragma once

#ifndef CHAPTER_TESTS_H
#define CHAPTER_TESTS_H

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
        void ChapterFive();
        void ChapterFive_Shadow();
        void ChapterSix();
        void ChapterSix_Shading();
        void ChapterSeven();
};

#endif