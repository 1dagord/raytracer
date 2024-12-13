#include <iostream>
#include <format>
#include <raylib.h>
#include <Eigen/Dense>

#include "main.hpp"
#include "save_ppm.hpp"

using Eigen::MatrixXf;

/*
	to use, run following commands:
		cd build/
		cmake .. && cmake --build . && ./raytracer
*/

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RayTracer");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
			DrawPixel(2, 3, RED);
			DrawCircle(10, 100, 2, BLUE);
			DrawCircle(4, 4, 2, PURPLE);
            DrawText("Press 'S' to take a screenshot", 10, 10, 20, DARKGRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            createPPMFile();
        }
    }

	CloseWindow();
	return 0;
}