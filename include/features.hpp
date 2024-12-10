#include <vector>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>


class Tuple{
    public:
        float x;
        float y;
        float z;
        float w; // 1 for points, 0 for vectors

        Tuple (float _x, float _y, float _z, float _w):
            x(_x),
            y(_y),
            z(_z),
            w(_w)
        {};


        float mag() {
            return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
        }

        void normalize() {
            float magnitude = this->mag();
            this->x /= magnitude;
            this->y /= magnitude;
            this->z /= magnitude;
            this->w /= magnitude;
        }

        bool operator== (const Tuple& other) {
            return (this->x == other.x && this->y == other.y && this->z == other.z);
        }

        void operator+= (const int num) {
            this->x += num;
            this->y += num;
            this->z += num;
        }

        void operator-= (const int num) {
            this->x -= num;
            this->y -= num;
            this->z -= num;
        }

        void operator*= (const int num) {
            this->x *= num;
            this->y *= num;
            this->z *= num;
        }

        void operator/= (const int num) {
            this->x /= num;
            this->y /= num;
            this->z /= num;
        }
};

class Point : public Tuple{
    public:
        Point(float _x, float _y, float _z) :
            Tuple(_x, _y, _z, 1) 
        {};

        Point operator= (const Point& other) {
            return Point(other.x, other.y, other.z);
        }

        Point operator+ (const Point& other) {
            return Point(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        Point operator+ (const int num) {
            return Point(this->x + num, this-> y + num, this->z + num);
        }

        Point operator- (const Point& other) {
            return Point(this->x - other.x, this->y - other.y, this->z - other.z);
        }

        Point operator- (const int num) {
            return Point(this->x - num, this-> y - num, this->z - num);
        }

        Point operator* (const Point& other) {
            return Point(this->x * other.x, this->y * other.y, this->z * other.z);
        }

        Point operator* (const int num) {
            return Point(this->x * num, this-> y * num, this->z * num);
        }

        Point operator/ (const Point& other) {
            return Point(this->x / other.x, this->y / other.y, this->z / other.z);
        }

        Point operator/ (const int num) {
            return Point(this->x / num, this-> y / num, this->z / num);
        }
};

class Vector : public Tuple{
    public:
        Vector(float _x, float _y, float _z) :
            Tuple(_x, _y, _z, 0)
        {};

        float dot(const Vector& other) {
            return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z) + (this->w * other.w));
        }

        Vector cross(const Vector& other) {
            return Vector(this->y * other.z - this->z * other.y,
                            this->z * other.x - this->x * other.z,
                            this->x * other.y - this->y * other.x);
        }

        Vector operator= (const Vector& other) {
            return Vector(other.x, other.y, other.z);
        }

        Vector operator+ (const Vector& other) {
            return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        Vector operator+ (const int num) {
            return Vector(this->x + num, this-> y + num, this->z + num);
        }

        Vector operator- (const Vector& other) {
            return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
        }

        Vector operator- (const int num) {
            return Vector(this->x - num, this-> y - num, this->z - num);
        }

        Vector operator* (const Vector& other) {
            return Vector(this->x * other.x, this->y * other.y, this->z * other.z);
        }

        Vector operator* (const int num) {
            return Vector(this->x * num, this-> y * num, this->z * num);
        }

        Vector operator/ (const Vector& other) {
            return Vector(this->x / other.x, this->y / other.y, this->z / other.z);
        }

        Vector operator/ (const int num) {
            return Vector(this->x / num, this-> y / num, this->z / num);
        }
};