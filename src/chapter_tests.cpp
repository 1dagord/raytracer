#include <iostream>
#include <cmath>
#include <raylib.h>
#include <Eigen/Dense>

#include "chapter_tests.hpp"
#include "linalg.hpp"
#include "save_ppm.hpp"


void BookTest::ChapterFour () {
    // Testing translation
	p = Point(-3, 4, 5);
	Matrix4f trans = translation(5, -3, 2);
	p_output = Point(2, 1, 7);
	assert(trans * p == p_output);

	Matrix4f trans_inv = trans.inverse();
	p_output = Point(-8, 7, 3);
	assert(trans_inv * p == p_output);

	v = Vector(-3, 4, 5);
	assert(v == trans_inv * v);

	// Testing scaling
	Matrix4f scal = scaling(2, 3, 4);
	p = Point(-4, 6, 8);
	p_output = Point(-8, 18, 32);
	assert(scal * p == p_output);

	v = Vector(-4, 6, 8);
	v_output = Vector(-8, 18, 32);
	assert(scal * v == v_output);

    v_output = Vector(-2, 2, 2);
    Matrix4f scal_inv = scal.inverse();
    assert(scal_inv * v == v_output);

    // Testing rotation: X-axis
    p = Point(0, 1, 0);
    Matrix4f half_quarter_x = rotation_x(M_PI / 4);
    Matrix4f full_quarter_x = rotation_x(M_PI / 2);
    p_output = Point(0, sqrt(2) / 2, sqrt(2) / 2);
    assert((half_quarter_x * p).isApprox(p_output, THRESH));    // Account for floating point error

    p_output = Point(0, 0, 1);
    assert((full_quarter_x * p).isApprox(p_output, THRESH));

    Matrix4f inv_half_quarter_x = half_quarter_x.inverse();
    p_output = Point(0, sqrt(2) / 2, -sqrt(2) / 2);
    assert((inv_half_quarter_x * p).isApprox(p_output, THRESH));

    // Y-axis
    p = Point(0, 0, 1);
    Matrix4f half_quarter_y = rotation_y(M_PI / 4);
    Matrix4f full_quarter_y = rotation_y(M_PI / 2);
    p_output = Point(sqrt(2) / 2, 0, sqrt(2) / 2);
    assert((half_quarter_y * p).isApprox(p_output, THRESH));

    p_output = Point(1, 0, 0);
    assert((full_quarter_y * p).isApprox(p_output, THRESH)); 

    // Z-axis
    p = Point(0, 1, 0);
    Matrix4f half_quarter_z = rotation_z(M_PI / 4);
    Matrix4f full_quarter_z = rotation_z(M_PI / 2);
    p_output = Point(-(sqrt(2) / 2), sqrt(2) / 2, 0);
    assert((half_quarter_z * p).isApprox(p_output, THRESH));

    p_output = Point(-1, 0, 0);
    assert((full_quarter_z * p).isApprox(p_output, THRESH)); 

    // Shearing
    Matrix4f shear = shearing(1, 0, 0, 0, 0, 0);
    p = Point(2, 3, 4);
    p_output = Point(5, 3, 4);
    assert((shear * p).isApprox(p_output, THRESH));

    shear = shearing(0, 1, 0, 0, 0, 0);
    p_output = Point(6, 3, 4);
    assert((shear * p).isApprox(p_output, THRESH));

    shear = shearing(0, 0, 1, 0, 0, 0);
    p_output = Point(2, 5, 4);
    assert((shear * p).isApprox(p_output, THRESH));

    shear = shearing(0, 0, 0, 1, 0, 0);
    p_output = Point(2, 7, 4);
    assert((shear * p).isApprox(p_output, THRESH));

    shear = shearing(0, 0, 0, 0, 1, 0);
    p_output = Point(2, 3, 6);
    assert((shear * p).isApprox(p_output, THRESH));

    shear = shearing(0, 0, 0, 0, 0, 1);
    p_output = Point(2, 3, 7);
    assert((shear * p).isApprox(p_output, THRESH));

    // Chained transformations
    p = Point(1, 0, 1);
    Matrix4f A = rotation_x(M_PI / 2);
    Matrix4f B = scaling(5, 5, 5);
    Matrix4f C = translation(10, 5, 7);

    Point p2(1, -1, 0);
    assert((A * p).isApprox(p2, THRESH));

    Point p3(5, -5, 0);
    assert((B * p2).isApprox(p3, THRESH));

    Point p4(15, 0, 7);
    assert((C * p3).isApprox(p4, THRESH));

    Matrix4f D = C * B * A;
    assert((D * p).isApprox(p4, THRESH));
}

void BookTest::ChapterTwo() {
    BeginDrawing();
        ClearBackground(BLACK);
        DrawPixel(2, 3, RED);
        DrawCircle(10, 100, 2, BLUE);
        DrawCircle(4, 4, 2, PURPLE);
        DrawText("Press 'S' to take a screenshot", 10, 10, 20, DARKGRAY);
    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
        createPPMFile();
    }
}