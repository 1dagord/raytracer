#pragma once

#ifndef MAIN_H
#define MAIN_H


const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 400;

// Used to account for floating-point error
const float THRESH = 1e-4;

inline bool equals(float a, float b) {
    return std::abs(a - b) < THRESH;
}

inline bool equals(std::array<float, 3> a, std::array<float, 3> b) {
    for (int i = 0; i < 3; i++) {
        if (std::abs(a.at(i) - b.at(i)) > THRESH)
            return false;
    }
    return true;
}

#endif