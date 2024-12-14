#pragma once

#include <Eigen/Dense>

using Eigen::Vector4f;
using Eigen::Matrix4f;


class Tuple : virtual public Vector4f {};

class Vector : public Tuple {
    public:
        Vector (float _x, float _y, float _z) :
        Vector4f (_x, _y, _z, 0)
        {}

        Vector () :
        Vector4f (0, 0, 0, 0)
        {}

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

        template<typename OtherDerived>
        Point& operator=(const Eigen::MatrixBase <OtherDerived>& other) {
            this->Vector4f::operator=(other);
            return *this;
        }
};

Matrix4f translation (float x, float y, float z);
Matrix4f scaling (float x, float y, float z);
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