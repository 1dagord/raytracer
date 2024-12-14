#include <iostream>
#include <format>
#include <raylib.h>
#include <Eigen/Dense>

#include "main.hpp"
#include "save_ppm.hpp"
#include "chapter_tests.hpp"

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

	BookTest bt;
	bt.ChapterOne();


	// while (!WindowShouldClose()) {
    //     BeginDrawing();
    //         ClearBackground(BLACK);
	// 		DrawPixel(2, 3, RED);
	// 		DrawCircle(10, 100, 2, BLUE);
	// 		DrawCircle(4, 4, 2, PURPLE);
    //         DrawText("Press 'S' to take a screenshot", 10, 10, 20, DARKGRAY);
    //     EndDrawing();

    //     if (IsKeyPressed(KEY_S)) {
    //         createPPMFile();
    //     }
    // }
	// CloseWindow();

	return 0;
}