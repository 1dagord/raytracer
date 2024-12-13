#include <iostream>

#include "main.hpp"


using Eigen::MatrixXf;

int main() {
    InitWindow(800, 600, "RayTracer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}