#pragma once

#ifndef LINALG_H
#define LINALG_H

#include <cmath>
#include <Eigen/Dense>

using Eigen::Vector4f;
using Eigen::Matrix4f;


class Tuple : virtual public Vector4f {
    public:
        float magnitude() {
            return (
                std::sqrt(
                    (*this).dot(*this) - (*this)(3)
                )
            );
        }

        void normalize() {
            float mag = magnitude();
            (*this)(0) /= mag;
            (*this)(1) /= mag;
            (*this)(2) /= mag;
        }

};

class Vector : public Tuple {
    public:
        Vector (float _x, float _y, float _z) :
        Vector4f (_x, _y, _z, 0)
        {}

        Vector () :
        Vector4f (0, 0, 0, 0)
        {}

        Vector reflect(Vector& normal) {
            Vector res;
            res = normal * 2 * ((*this).dot(normal));
            res = (*this) - res;
            return res;
        }

        // allow assignment from Eigen's Vector class
        template<typename OtherDerived>
        Vector& operator=(const Eigen::MatrixBase <OtherDerived>& other) {
            this->Vector4f::operator=(other);
            return *this;
        }
};

class Point : public Tuple {
    public:
        Point (float _x, float _y, float _z) :
        Vector4f (_x, _y, _z, 1)
        {}

        Point () :
        Vector4f (0, 0, 0, 1)
        {}

        // allow assignment from Eigen's Vector class
        template<typename OtherDerived>
        Point& operator=(const Eigen::MatrixBase <OtherDerived>& other) {
            this->Vector4f::operator=(other);
            return *this;
        }
};

Matrix4f translation (float x, float y, float z);
Matrix4f scaling (float x, float y, float z);
Matrix4f scaling (float val);
Matrix4f rotation_x (float rad);
Matrix4f rotation_y (float rad);
Matrix4f rotation_z (float rad);
Matrix4f shearing (float x_y,
				   float x_z,
				   float y_x,
				   float y_z,
				   float z_x,
				   float z_y
				  );

#endif