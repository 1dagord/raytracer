#pragma once

#include <vector>
#include <Eigen/Dense>
#include "linalg.hpp"


// does not extend raylib::Ray to avoid using
// native raylib vectors for vector operations
class RTRay {
    public:
        Point& origin;
        Vector& direction;

    public:
        RTRay (Point& p, Vector& v) :
            origin(p),
            direction(v)
        {}

        Point position(float t);
};

class RTCircle {
    public:
        Point& origin;
        float radius;

    public:
        RTCircle (Point& p, float rad) :
            origin(p),
            radius(rad)
        {}

        std::vector<float> intersect(RTRay& r);
};