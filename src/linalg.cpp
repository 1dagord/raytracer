#include <cmath>
#include <Eigen/Dense>
#include "linalg.hpp"

using Eigen::Vector4f;
using Eigen::Matrix4f;


/**
 * @return: Translation matrix of form
 * 
 *          [1		0		0		x]
 *          [0		1		0		y]
 *          [0		0		1		z]
 *          [0		0		0		1]
 */
Matrix4f translation (float x, float y, float z) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(0, 3) = x;
	A(1, 3) = y;
	A(2, 3) = z;

	return A;
}

/**
 * @return: Scaling matrix of form
 * 
 *          [x		0		0		0]
 *          [0		y		0		0]
 *          [0		0		z		0]
 *          [0		0		0		1]
 * 
 *          Reflection is a rotation where at least
 *          one of the values x, y, z is negated
 */
Matrix4f scaling (float x, float y, float z) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(0, 0) = x;
	A(1, 1) = y;
	A(2, 2) = z;

	return A;
}

Matrix4f scaling (float val) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(0, 0) = val;
	A(1, 1) = val;
	A(2, 2) = val;

	return A;
}


/**
 * @param rad: rotation angle in radians
 * @return: Rotation matrix around x axis.
 *          Has form
 * 
 *          [1			0			0			0]
 *          [0			cos(r)		-sin(r)		0]
 *          [0			sin(r)		cos(r)		0]
 *          [0			0			0			1]
 */
Matrix4f rotation_x (float rad) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(1, 1) = cos(rad);
	A(1, 2) = -sin(rad);
	A(2, 1) = sin(rad);
	A(2, 2) = cos(rad);

	return A;
}


/**
 * @param rad: rotation angle in radians
 * @return: Rotation matrix around y axis.
 *          Has form
 * 
 *          [cos(r)		0			sin(r)		0]
 *          [0			1			0			0]
 *          [-sin(r)	0			cos(r)		0]
 *          [0			0			0			1]
 */
Matrix4f rotation_y (float rad) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(0, 0) = cos(rad);
	A(2, 0) = -sin(rad);
	A(0, 2) = sin(rad);
	A(2, 2) = cos(rad);

	return A;
}


/**
 * @param rad: rotation angle in radians
 * @return: Rotation matrix around z axis.
 *          Has form
 *          
 * 			[cos(r)		-sin(r)		0			0]
 *          [sin(r)		cos(r)		0			0]
 *          [0			0			1			0]
 *          [0			0			0			1]
 */
Matrix4f rotation_z (float rad) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(0, 0) = cos(rad);
	A(0, 1) = -sin(rad);
	A(1, 0) = sin(rad);
	A(1, 1) = cos(rad);

	return A;
}


/**
 * @return: Shearing matrix of form
 *          
 * 			[1			x_y			x_z		0]
 * 			[y_x		1			y_z		0]
 * 			[z_x		z_y			1		0]
 * 			[0			0			0		1]
 */
Matrix4f shearing (float x_y,
				   float x_z,
				   float y_x,
				   float y_z,
				   float z_x,
				   float z_y
				  ) {
	Matrix4f A = Matrix4f::Identity(4, 4);
	A(0, 1) = x_y;
	A(0, 2) = x_z;
	A(1, 0) = y_x;
	A(1, 2) = y_z;
	A(2, 0) = z_x;
	A(2, 1) = z_y;

	return A;
}