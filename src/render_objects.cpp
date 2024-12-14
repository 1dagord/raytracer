#include "render_objects.hpp"


Point RTRay::position(float t) {
	Point res;
	res = this->origin + (this->direction * t);
	return res;
}

std::vector<float> RTCircle::intersect(RTRay& r) {
    std::vector<float> res = {};

    return res;
}

// bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2);  