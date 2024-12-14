#pragma once

#include <vector>
#include <array>
#include <memory>
#include <Eigen/Dense>
#include "linalg.hpp"



// does not extend raylib::Ray to avoid using
// native raylib vectors for vector operations
class RTRay {
    public:
        Point origin;
        Vector direction;

    public:
        RTRay (Point p, Vector v) :
            origin(p),
            direction(v)
        {}

        Point position(float t);

        RTRay& operator=(const RTRay& other) {
            this->origin = other.origin;
            this->direction = other.direction;
            return *this;
        }

        // bool operator==(const RTRay& other) {
        //     return (this->origin == other.origin && this->direction == other.direction);
        // }
};

class RTSphere {
    public:
        Point origin;
        float radius;

    public:
        RTSphere (Point p, float rad) :
            origin(p),
            radius(rad)
        {}

        RTSphere (float rad) :
            origin(Point(0, 0, 0)),
            radius(rad)
        {}

        RTSphere () :
            origin(Point(0, 0, 0)),
            radius(1.0)
        {}

        std::vector<float> intersect(RTRay& r);

        bool operator==(RTSphere& other) {
            return (this->origin == other.origin && this->radius == other.radius);
        }
};

// TODO: find a way to instantiate class without explicit object type
template <typename T>
class Intersection {
    public:
        float t;
        T& object;

    public:
        Intersection (float _t, T& obj) :
            t(_t),
            object(obj)
        {}
};


// typedef std::vector<Intersection> InterRecord;