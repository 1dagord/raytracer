#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <raylib.h>

namespace fs = std::filesystem;

// Set path of saved image
fs::path root_path = fs::current_path().parent_path();
fs::path file_path = root_path / "window_bytecode.cpp";


void createPPMFile() {
    // default pixel format: PIXELFORMAT_UNCOMPRESSED_R8G8B8A8

    // Get window position and size
    int window_x = GetWindowPosition().x;
    int window_y = GetWindowPosition().y;
    int window_width = GetScreenWidth();
    int window_height = GetScreenHeight();

    // Take screenshot of the window
    Image screen_image = LoadImageFromScreen();

    // Store pixel data in byte array
    Color* pixels = LoadImageColors(screen_image);
    unsigned char byte_array[window_width * window_height * 4];

    for (int i = 0; i < window_width * window_height; i++) {
        byte_array[i * 4] = pixels[i].r;
        byte_array[i * 4 + 1] = pixels[i].g;
        byte_array[i * 4 + 2] = pixels[i].b;
        byte_array[i * 4 + 3] = pixels[i].a;
    }

    // Create and populate .ppm file
    std::string save_path = (root_path / fs::path("src/output/screen.ppm"));
    std::ofstream out_file(save_path);

    // Write header to .ppm file
    out_file << "P3" << std::endl;
    out_file << window_width << " " << window_height << std::endl;
    if (screen_image.format == PIXELFORMAT_UNCOMPRESSED_R16G16B16) {
        out_file << 65535 << std::endl;
    } else {
        out_file << 255 << std::endl;
    }
    
    // Populate .ppm file with byte data
    int char_count = 0;
    for (int i = 0; i < 4 * window_width * window_height; i += 4) {
        // ensure line length < 70
        char_count += 3;
        if (char_count >= 70)
            out_file << "\n";
            char_count = 0;
        // skip alpha channel, only write RGB
        for (int z = 0; z < 3; z++) {
            // cast bytes to decimal
            out_file << std::setfill('0') << std::setw(3)
                << static_cast<int>(byte_array[i + z])
                << ((i != 0 && i % (4 * window_width) == 0) ? ("\n") : (" "));
        }
    }

    // May cause errors while viewing if not appended
    out_file << "\n";

    // Free up memory
    out_file.close();
    UnloadImageColors(pixels);
    UnloadImage(screen_image);
}