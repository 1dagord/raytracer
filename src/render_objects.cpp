#include "render_objects.hpp"

// Class Methods

Point RTRay::position(float t) {
	Point res;
	res = this->origin + (this->direction * t);
	return res;
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

Vector RTSphere::normal_at(Point world_point) {
	Vector res;
	Point object_point, object_normal, world_normal;

	object_point = this->transformation.inverse() * world_point;
	object_normal = object_point - this->origin;
	world_normal = this->transformation.inverse().transpose() * object_normal;

	res = *(dynamic_cast<Tuple*>(&world_normal));
	res = (Vector)res;
	res(3) = 0;
	res.normalize();
	return res;
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

RTColor lighting(RTMaterial& mat, PointLight& light, Point& p, Vector& eye_vec, Vector& normal_vec) {
	// Combine surface color with light color's intensity
	RTColor effective_color;
	for (int i = 0; i < 3; i++)
		effective_color.at(i) = mat.color.at(i) * light.intensity.at(i);

	// Find direction to light source
	Vector light_vec;
	Point light_point;
	light_point = light.origin - p;
	light_vec = *(dynamic_cast<Tuple*>(&light_point));
	light_vec = (Vector)light_vec;
	light_vec(3) = 0;
	light_vec.normalize();

	// Compute ambient contribution
	RTColor ambient, diffuse, specular;
	for (int i = 0; i < 3; i++) {
		ambient.at(i) = effective_color.at(i) * mat.ambient;
	}

	float light_dot_normal = light_vec.dot(normal_vec);

	if (light_dot_normal < 0) {
		diffuse = {0, 0, 0};
		specular = {0, 0, 0};
	} else {
		for (int i = 0; i < 3; i++) {
			diffuse.at(i) = effective_color.at(i) * mat.diffuse * light_dot_normal;
		}
		Vector neg_light_vec;
		neg_light_vec = -1 * light_vec;
		Vector reflect_vec = neg_light_vec.reflect(normal_vec);
		float reflect_dot_eye = reflect_vec.dot(eye_vec);

		if (reflect_dot_eye <= 0) {
			specular = {0, 0, 0};
		} else {
			// Compute specular contribution
			float factor = std::powf(reflect_dot_eye, mat.shininess);
			// std::cout << reflect_dot_eye << std::endl;
			// ----- PROBLEM IS HERE -----
			for (int i = 0; i < 3; i++) {
				specular.at(i) = light.intensity.at(i) * mat.specular * factor;
			}
			// ----- PROBLEM IS HERE -----
			// auto it = std::max_element(specular.begin(), specular.end());
			// std::cout << *it << "\n";
		}
	}

	RTColor res;
	for (int i = 0; i < 3; i++) {
		res.at(i) = ambient.at(i) + diffuse.at(i) + specular.at(i);
	}

	// auto it1 = std::max_element(ambient.begin(), ambient.end());
	// auto it2 = std::max_element(diffuse.begin(), diffuse.end());
	// auto it3 = std::max_element(specular.begin(), specular.end());
	// auto it4 = std::max_element(res.begin(), res.end());
	// // auto it5 = std::min_element(res.begin(), res.end());

	// // for (int i = 0; i < 3; i++)
	// // 	res.at(i) = ((res.at(i) - *it5) / (*it4 - *it5));

	// Print resulting color
	// for (float v : res)
	// 	std::cout << v << " ";
	// std::cout << std::endl;

	// std::cout << *it1 << "\t\t" << *it2 << "\t\t" << *it3 << "\t\t" << *it4 <<"\n";

    return res;
}
