#include "render_objects.hpp"

// Class Methods

Point RTRay::position(float t) {
	Point* res = new Point();
	*res = this->origin + (this->direction * t);
	return *res;
}

std::vector<float> RTRay::intersect_float(RTObject& obj) {
	/*
		Intersection includes points behind
		ray's origin

		If closest point < radius, two points
		If closest point == radius, one point (tangent)
		Else, zero points
	*/
	std::vector<float> res = {};

	// Compute discriminant
	Point object_to_ray;
	object_to_ray = this->origin - obj.origin;

	float a = this->direction.dot(this->direction);
	float b = 2 * this->direction.dot(object_to_ray);
	float c = (object_to_ray.dot(object_to_ray)) - 1;
	float discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant >= 0) {
		res = {
			(-b - sqrt(discriminant)) / (2 * a),
			(-b + sqrt(discriminant)) / (2 * a)
		};
	}

	return res;
}

InterRecord RTRay::intersect_no_mod(RTObject& obj) {
	/*
		Modification of above function that returns
		list of intersection records for any object
	*/
	InterRecord res = {};

	// Compute discriminant
	Point object_to_ray;
	object_to_ray = this->origin - obj.origin;

	float a = this->direction.dot(this->direction);
	float b = 2 * this->direction.dot(object_to_ray);
	float c = (object_to_ray.dot(object_to_ray)) - 1;
	float discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant >= 0) {
		res.push_back(Intersection((-b - sqrt(discriminant)) / (2 * a), obj));
		res.push_back(Intersection((-b + sqrt(discriminant)) / (2 * a), obj));
	}

	return res;
}

InterRecord RTRay::intersect(RTObject& obj) {
	/*
		Further modification of intersect(...) where
		object's transformation is applied to each RTRay
		before returning
	*/
	InterRecord res = {};

	// Compute discriminant
	Matrix4f m = to_sphere(obj)->transformation.inverse();
	RTRay ray = this->transform(m);	// invert to apply to ray instead of obj

	Point object_to_ray;
	object_to_ray = ray.origin - obj.origin;

	float a = ray.direction.dot(ray.direction);
	float b = 2 * ray.direction.dot(object_to_ray);
	float c = (object_to_ray.dot(object_to_ray)) - 1;
	float discriminant = pow(b, 2) - (4 * a * c);

	if (discriminant >= 0) {
		res.push_back(Intersection((-b - sqrt(discriminant)) / (2 * a), obj));
		res.push_back(Intersection((-b + sqrt(discriminant)) / (2 * a), obj));
	}

	return res;
}

/**
 * Transforms current ray by matrix `m`
 * @return: new transformed RTRay
 */
RTRay RTRay::transform(Matrix4f& m) {
	RTRay* res = new RTRay(this->origin, this->direction);
	res->origin = m * res->origin;
	res->direction = m * res->direction;
	return *res;
}

// Non-class Methods

/**
 * @return: InterRecord containing closest object of
 * 			hit within InterRecord `record`
 * 
 * 			If no intersection, returns empty InterRecord
 */
InterRecord hit(InterRecord& record) {
	InterRecord res = {};
	for (Intersection& i : record) {
		if (i.t >= 0) {
			if (res.empty()) {
				res.push_back(i);
			} else if (i.t < res.at(0).t) {
					res.at(0) = i;
			}
		}
	}
	return res;
}
