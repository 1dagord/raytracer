#pragma once

#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <Eigen/Dense>
#include "linalg.hpp"

#define downcast(x) dynamic_cast<RTObject*>(&x)
#define to_sphere(x) dynamic_cast<RTSphere*>(&x)

using Eigen::Matrix4f;


// Base class; represents any object on the screen
class RTObject {
    public:
        Point origin;
        
    public:
        RTObject (Point p) :
            origin(p)
        {}

        virtual ~RTObject () {}
        // use dynamic_cast<T> when referencing child objects
};

// Stores an intersected object and
// the point (on the ray) of intersection
class Intersection {
    public:
        float t;
        RTObject& object;

    public:
        Intersection (float _t, RTObject& obj) :
            t(_t),
            object(obj)
        {}


        Intersection& operator= (const Intersection& other) {
            this->t = other.t;
            this->object = other.object;
            return *this;
        }

        bool operator== (const Intersection other) {
            return ((this->t == other.t) && (&(this->object) == &(other.object)));
        }
}; 

// Stores a record of intersections
typedef std::vector<Intersection> InterRecord;
// may be good idea to make this a min heap

// Represents a ray of light. Not an RTObject.
class RTRay {
    public:
        Point origin;
        Vector direction;

    public:
        RTRay (Point p, Vector v) :
            origin(p),
            direction(v)
        {}

        RTRay () :
            origin(Point(0, 0, 0)),
            direction(Vector(0, 0, 0))
        {}

        Point position(float t);
        std::vector<float> intersect_float(RTObject& obj);
        InterRecord intersect_no_mod(RTObject& obj);
        InterRecord intersect(RTObject& obj);
        RTRay transform(Matrix4f& m);

        RTRay& operator=(const RTRay& other) {
            this->origin = other.origin;
            this->direction = other.direction;
            return *this;
        }

        bool operator==(const RTRay& other) {
            return (this->origin == other.origin && this->direction == other.direction);
        }
};

class RTSphere : public RTObject {
    public:
        float radius;
        Matrix4f transformation;

    public:
        RTSphere (Point p, float rad, Matrix4f m) :
            RTObject(p),
            radius(rad),
            transformation(m)
        {}

        RTSphere (Point p, float rad) :
            RTObject(p),
            radius(rad),
            transformation(Matrix4f::Identity(4, 4))
        {}

        RTSphere (float rad) :
            RTObject(Point(0, 0, 0)),
            radius(rad),
            transformation(Matrix4f::Identity(4, 4))
        {}

        RTSphere () :
            RTObject(Point(0, 0, 0)),
            radius(1.0),
            transformation(Matrix4f::Identity(4, 4))
        {}

        bool operator==(const RTSphere& other) {
            return (this->origin == other.origin && this->radius == other.radius);
        }
};

InterRecord hit(InterRecord& record);