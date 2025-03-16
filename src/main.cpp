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
	// InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RayTracer");
	// SetTargetFPS(60);

	// Initialize tests from book
	BookTest bt;
	// bt.ChapterFour();
	// bt.ChapterFive();
	// bt.ChapterSix();
	bt.ChapterSeven();

	// while (!WindowShouldClose()) {
    //     // bt.ChapterTwo();
	// 	// bt.ChapterFour_Clock();
	// 	// bt.ChapterFive_Shadow();
	// 	// bt.ChapterSix_Shading();

	// 	// if (IsKeyPressed(KEY_S)) {
	// 	// 	createPPMFile();
	// 	// }
    // }
	// CloseWindow();

	return 0;
}