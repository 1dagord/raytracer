#include "render_objects.hpp"


Point RTRay::position(float t) {
	Point* res = new Point();
	*res = this->origin + (this->direction * t);
	return *res;
}

std::vector<float> RTSphere::intersect(RTRay& r) {
	/*
		Intersection includes points behind
		ray's origin

		If closest point < radius, two points
		If closest point == radius, one point (tangent)
		Else, zero points
	*/
	std::vector<float> res = {};

	// Compute discriminant
	Point sphere_to_ray;
	sphere_to_ray = r.origin - this->origin;

	float a = r.direction.dot(r.direction);
	float b = 2 * r.direction.dot(sphere_to_ray);
	float c = (sphere_to_ray.dot(sphere_to_ray)) - 1;
	float discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant >= 0) {
		res = {
			(-b - sqrt(discriminant)) / (2 * a),
			(-b + sqrt(discriminant)) / (2 * a)
		};
	}

	return res;
}