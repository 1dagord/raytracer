#include <iostream>
#include <format>
#include <raylib.h>
#include <Eigen/Dense>

#include "main.hpp"
#include "save_ppm.hpp"
#include "chapter_tests.hpp"
#include "render_objects.hpp"

using Eigen::Vector4f;
using Eigen::Matrix4f;

/*
	to use, run following commands:
		cd build/
		cmake .. && cmake --build . && ./raytracer
*/

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RayTracer");
	SetTargetFPS(60);

	// Initialize tests from book
	BookTest bt;
	// bt.ChapterFour();
	bt.ChapterFive();

	// while (!WindowShouldClose()) {
    //     // bt.ChapterTwo();
	// 	bt.ChapterFour_Clock();
    // }
	// CloseWindow();

	return 0;
}