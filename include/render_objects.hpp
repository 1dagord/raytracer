#pragma once

#ifndef RENDER_OBJECTS_H
#define RENDER_OBJECTS_H

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

typedef std::array<float, 3> RTColor;

class RTMaterial {
    public:
        float ambient, diffuse, specular, shininess;
        RTColor color;

    public:
        RTMaterial (float amb, float dif, float spec, float shin, RTColor col) :
            ambient(amb),
            diffuse(dif),
            specular(spec),
            shininess(shin),
            color(col)
        {}

        RTMaterial (float amb, float dif, float spec, float shin) :
            ambient(amb),
            diffuse(dif),
            specular(spec),
            shininess(shin),
            color(RTColor{1, 1, 1})
        {}

        RTMaterial () :
            ambient(0.1),
            diffuse(0.9),
            specular(0.9),
            shininess(200.0),
            color(RTColor{1, 1, 1})
        {}

        bool operator== (RTMaterial& other) {
            return (
                this->ambient == other.ambient &&
                this->diffuse == other.diffuse &&
                this->specular == other.specular &&
                this->shininess == other.shininess &&
                this->color == other.color
            );
        }
};

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
        RTMaterial material;

    public:
        RTSphere (Point p, float rad, Matrix4f m) :
            RTObject(p),
            radius(rad),
            transformation(m),
            material(RTMaterial())
        {}

        RTSphere (Point p, float rad) :
            RTObject(p),
            radius(rad),
            transformation(Matrix4f::Identity(4, 4)),
            material(RTMaterial())
        {}

        RTSphere (float rad) :
            RTObject(Point(0, 0, 0)),
            radius(rad),
            transformation(Matrix4f::Identity(4, 4)),
            material(RTMaterial())
        {}

        RTSphere () :
            RTObject(Point(0, 0, 0)),
            radius(1.0),
            transformation(Matrix4f::Identity(4, 4)),
            material(RTMaterial())
        {}

        Vector normal_at(Point p);

        bool operator==(const RTSphere& other) {
            return (this->origin == other.origin && this->radius == other.radius);
        }
};

InterRecord hit(InterRecord& record);

class PointLight : public RTObject {
    public:
        RTColor intensity;

    public:
        PointLight (Point pos, RTColor intens) :
            RTObject(pos),
            intensity(intens)
        {}
};

RTColor lighting(RTMaterial& mat, PointLight& light, Point& p, Vector& eye_vec, Vector& normal_vec);

#endif