#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <any>
#include <typeinfo>
#include <memory>
#include <raylib.h>
#include <Eigen/Dense>
#include <boost/algorithm/string.hpp>

#include "chapter_tests.hpp"
#include "linalg.hpp"
#include "save_ppm.hpp"
#include "render_objects.hpp"
#include "world.hpp"
#include "main.hpp"

#define BOOST_DISABLE_ASSERTS   // only use std macro-defined assert

void BookTest::ChapterSeven() {
    World w = World();
    for (const auto& obj : w.objects) {
        assert(*to_sphere(*obj) == RTSphere(1.0) || *to_sphere(*obj) == RTSphere(0.5));
    }
    assert(*(w.lights.back()) == PointLight());
}


void BookTest::ChapterSix_Shading() {
    Point ray_origin(0.0, 0.0, -5.0);
    Point position;
    RTSphere sphere;
    sphere.material.color = RTColor{1, 0.2, 1};

    Point light_position(-10, 10, -10);
    RTColor light_color = RTColor{1, 1, 1};
    PointLight light(light_position, light_color);

    float wall_z = 10.0;
    float wall_size = 7.0;
    float h_wall_size = wall_size / 2;
    float canvas_pixels = WINDOW_WIDTH;
    float pixel_size = wall_size / canvas_pixels;

    float world_x = 0, world_y = 0;     // must be floats to produce smooth image
    Vector vec, normal_vec, eye_vec;
    RTRay r;
    Point p;
    InterRecord xs, h;
    RTColor color;
    Color obj_color;

    BeginDrawing();
        ClearBackground(BLACK);
        for (float y = 0; y < WINDOW_HEIGHT; y++) {
            world_y = h_wall_size - (pixel_size * y);

            for (float x = 0; x < WINDOW_WIDTH; x++) {
                world_x = -h_wall_size + (pixel_size * x);
                position = Point(world_x, world_y, wall_z);
                vec = position - ray_origin;
                vec.normalize();
            
                r = RTRay(ray_origin, vec);
                xs = r.intersect(sphere);

                if (!xs.empty() && !hit(xs).empty()) {
                    h = hit(xs);
                    p = r.position(h.at(0).t);
                    normal_vec = to_sphere(h.at(0).object)->normal_at(p);
                    r.direction.normalize();
                    eye_vec = -1 * r.direction;
                    RTMaterial mat = to_sphere(h.at(0).object)->material;
                    color = lighting(mat, light, p, eye_vec, normal_vec);

                    obj_color.r = static_cast<uint8_t>(color.at(0) * 255);
                    obj_color.g = static_cast<uint8_t>(color.at(1) * 255);
                    obj_color.b = static_cast<uint8_t>(color.at(2) * 255);
                    obj_color.a = static_cast<uint8_t>(255);

                    DrawPixel(x, y, obj_color);
                }
            }
        }
    EndDrawing();
}

void BookTest::ChapterSix() {
    // Testing normal_at(...)
    RTSphere s;
    Vector n;
    n = s.normal_at(Point(1, 0, 0));
    assert(n.isApprox(Vector(1, 0, 0), THRESH));

    n = s.normal_at(Point(0, 1, 0));
    assert(n.isApprox(Vector(0, 1, 0), THRESH));

    n = s.normal_at(Point(0, 0, 1));
    assert(n.isApprox(Vector(0, 0, 1), THRESH));

    n = s.normal_at(Point(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3));
    assert(n.isApprox(Vector(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3), THRESH));  // floating point error
    Vector norm_n;
    norm_n = n;
    norm_n.normalize();
    assert(n.isApprox(norm_n, THRESH));

    s.transformation = translation(0, 1, 0);
    n = s.normal_at(Point(0, 1.70711, -0.70711));
    assert(n.isApprox(Vector(0, 0.70711, -0.70711)));

    s.transformation = scaling(1, 0.5, 1) * rotation_z(EIGEN_PI / 5);
    n = s.normal_at(Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
    assert(n.isApprox(Vector(0, 0.97014, -0.24254)));

    // Testing reflect(...)
    Vector v(1, -1, 0);
    n = Vector(0, 1, 0);
    Vector r = v.reflect(n);
    assert(r.isApprox(Vector(1, 1, 0), THRESH));

    v = Vector(0, -1, 0);
    n = Vector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
    r = v.reflect(n);
    assert(r.isApprox(Vector(1, 0, 0), THRESH));

    // Testing PointLight
    PointLight pl(Point(), {1, 1, 1});
    RTColor output{1, 1, 1};
    assert(pl.origin == Point());
    assert(pl.intensity == output);

    // Testing RTMaterial
    RTMaterial mat;
    assert(mat.color == output);
    assert(equals(mat.ambient, 0.1));
    assert(equals(mat.diffuse, 0.9));
    assert(equals(mat.specular, 0.9));
    assert(equals(mat.shininess, 200.0));

    s = RTSphere();
    assert(s.material == RTMaterial());
    mat = RTMaterial();
    mat.ambient = 1;
    s.material = mat;
    assert(s.material == mat);
    assert(s.material.ambient == 1);

    // Testing lighting(...)
    // light behind eye, both opposite surface
    Vector eye_vec(0, 0, -1);
    Vector normal_vec(0, 0, -1);
    PointLight light(Point(0, 0, -10), RTColor{1, 1, 1});
    Point p;
    mat = RTMaterial();
    RTColor res = lighting(mat, light, p, eye_vec, normal_vec);
    assert((res == RTColor{1.9, 1.9, 1.9}));

    // eye between light and surface, eye offset 45º
    eye_vec = Vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    res = lighting(mat, light, p, eye_vec, normal_vec);
    assert((res == RTColor{1.0, 1.0, 1.0}));

    // light w eye opposite surface, light offset 45º
    eye_vec = Vector(0, 0, -1);
    light = PointLight(Point(0, 10, -10), RTColor{1, 1, 1});
    res = lighting(mat, light, p, eye_vec, normal_vec);
    assert(equals(res, RTColor{0.7364, 0.7364, 0.7364}));

    // eye in path of light's reflection vector
    eye_vec = Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    res = lighting(mat, light, p, eye_vec, normal_vec);
    assert(equals(res, RTColor{1.6364, 1.6364, 1.6364}));

    // surface between light and eye
    eye_vec = Vector(0, 0, -1);
    light = PointLight(Point(0, 0, 10), RTColor{1, 1, 1});
    res = lighting(mat, light, p, eye_vec, normal_vec);
    assert(equals(res, RTColor{0.1, 0.1, 0.1}));
}

void BookTest::ChapterFive_Shadow() {
    Point ray_origin(0.0, 0.0, -5.0);
    Point position;
    RTSphere shape;

    // Shrink along X-axis
    // shape.transformation = scaling(1, 0.5, 1);

    // Shrink along Y-axis
    // shape.transformation = scaling(0.5, 1, 1);

    // Shrink and rotate
    // shape.transformation = rotation_z(EIGEN_PI / 4) * scaling(0.5, 1, 1);

    // Shrink and skew
    shape.transformation = shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1);

    float wall_z = 10.0;
    float wall_size = 7.0;
    float h_wall_size = wall_size / 2;
    float canvas_pixels = WINDOW_WIDTH;
    float pixel_size = wall_size / canvas_pixels;

    float world_x = 0, world_y = 0;     // must be floats to produce smooth image
    Vector vec;
    RTRay r;
    InterRecord xs;

    BeginDrawing();
        ClearBackground(BLACK);
        for (float y = 0; y < WINDOW_HEIGHT; y++) {
            world_y = h_wall_size - (pixel_size * y);

            for (float x = 0; x < WINDOW_WIDTH; x++) {
                world_x = -h_wall_size + (pixel_size * x);
                position = Point(world_x, world_y, wall_z);
                vec = position - ray_origin;
                vec.normalize();
            
                r = RTRay(ray_origin, vec);
                xs = r.intersect(shape);

                if (!xs.empty() && !hit(xs).empty()) {
                    DrawPixel(x, y, RED);
                }
            }
        }
    EndDrawing();
}

void BookTest::ChapterFive() {
    // Testing position(...)
    RTRay r(Point{2, 3, 4}, Vector{1, 0, 0});
    p_output = Point(2, 3, 4);
    assert(r.position(0) == p_output);     // Must use to avoid ambiguity

    p_output = Point(3, 3, 4);
    assert(r.position(1) == p_output);

    p_output = Point(1, 3, 4);
    assert(r.position(-1) == p_output);

    p_output = Point(4.5, 3, 4);
    assert(r.position(2.5) == p_output);

    // Testing intersect(...): ray origin outside sphere
    r = RTRay(Point{0, 0, -5}, Vector{0, 0, 1});
    RTSphere s;
    std::vector<float> points = r.intersect_float(s);
    assert(points.size() == 2);
    assert((std::vector<float>{4.0, 6.0} == points));

    r = RTRay(Point{0, 1, -5}, Vector{0, 0, 1});
    points = r.intersect_float(s);
    assert(points.size() == 2);
    assert((std::vector<float>{5.0, 5.0} == points));

    r = RTRay(Point{0, 2, -5}, Vector{0, 0, 1});
    points = r.intersect_float(s);
    assert(points.empty());

    // Testing intersect(...): ray origin inside sphere
    r = RTRay(Point{0, 0, 0}, Vector{0, 0, 1});
    points = r.intersect_float(s);
    assert(points.size() == 2);
    assert((std::vector<float>{-1.0, 1.0} == points));

    // Testing intersect(...): sphere behind ray
    r = RTRay(Point{0, 0, 5}, Vector{0, 0, 1});
    points = r.intersect_float(s);
    assert(points.size() == 2);
    assert((std::vector<float>{-6.0, -4.0} == points));

    // Testing Intersection
    Intersection inter(3.5, s);
    assert(inter.t == 3.5);
    assert(downcast(inter.object) == downcast(s));  // downcast then compare objects
    assert(&inter.object == &s);

    // Testing InterRecord
    Intersection inter1(1, s);
    Intersection inter2(2, s);
    InterRecord xs = {inter1, inter2};
    assert(xs.size() == 2);
    assert(xs[0].t == 1 && xs[1].t == 2);
    xs.clear();

    // Testing new intersect(...) *no float*
    xs = r.intersect_no_mod(s);
    assert(xs.size() == 2);
    assert(downcast(xs[0].object) == downcast(s));
    assert(downcast(xs[1].object) == downcast(s));
    xs.clear();

    // Testing hit(...)
    xs = InterRecord{inter1, inter2};
    assert(!hit(xs).empty() && hit(xs).at(0) == inter1);
    xs.clear();

    inter1 = Intersection(-1, s);
    inter2 = Intersection(1, s);
    xs = InterRecord{inter1, inter2};
    assert(!hit(xs).empty() && hit(xs).at(0) == inter2);
    xs.clear();

    inter1 = Intersection(-2, s);
    inter2 = Intersection(-1, s);
    xs = InterRecord{inter1, inter2};
    assert(hit(xs).empty());
    xs.clear();

    inter1 = Intersection(5, s);
    inter2 = Intersection(7, s);
    Intersection inter3(-3, s);
    Intersection inter4(2, s);
    xs = InterRecord{inter1, inter2, inter3, inter4};
    assert(!hit(xs).empty() && hit(xs).at(0) == inter4);

    // Testing transform(...): translation
    r = RTRay(Point{1, 2, 3}, Vector{0, 1, 0});
    Matrix4f m = translation(3, 4, 5);
    RTRay r2 = r.transform(m);
    p_output = Point(4, 6, 8);
    assert(r2.origin == p_output);

    v_output = Vector(0, 1, 0);
    assert(r2.direction == v_output);

    // Testing transform(...): scaling
    m = scaling(2, 3, 4);
    r2 = r.transform(m);
    p_output = Point(2, 6, 12);
    assert(r2.origin == p_output);

    v_output = Vector(0, 3, 0);
    assert(r2.direction == v_output);

    // Testing transformation
    assert(s.transformation == Matrix4f::Identity(4, 4));
    s.transformation = translation(2, 3, 4);
    assert(s.transformation == translation(2, 3, 4));

    // Testing new intersect(...): ray modification
    r = RTRay(Point(0, 0, -5), Vector(0, 0, 1));
    s = RTSphere();
    s.transformation = scaling(2, 2, 2);
    xs = r.intersect(s);
    assert(xs.size() == 2);
    assert(xs.at(0).t == 3 && xs.at(1).t == 7);
    xs.clear();

    s.transformation = translation(5, 0, 0);
    xs = r.intersect(s);
    assert(xs.empty());
}

void BookTest::ChapterFour_Clock() {
    time_t now;
    char* datetime;

    // Store current date and time
    time(&now);
    datetime = ctime(&now);

    // Obtain time from `datetime`
    std::vector<std::string> words;
    boost::split(words, datetime, boost::is_any_of(" "));

    // Split time by hour, minute, and second
    std::vector<std::string> clock_time;
    boost::split(clock_time, words.at(3), boost::is_any_of(":"));

    // Convert to ints
    std::vector<int> num_time;
    for (std::string& item : clock_time)
        num_time.push_back(std::stoi(item));

    int window_x = GetWindowPosition().x;
    int window_y = GetWindowPosition().y;
    int window_width = GetScreenWidth();
    int window_height = GetScreenHeight();

    Point origin(window_width / 2, window_height / 2, 0);

    // Set reference points for hours, minutes, and seconds
    Point twelve_o_clock(0, 1, 0);
    Point zero_mins(0, 1, 0);
    Point zero_secs(0, 1, 0);

    float clock_radius = 0.6 * (window_width / 2);
    Matrix4f arm_scale = scaling(clock_radius, clock_radius, clock_radius);

    // Rotate hour, minute, and second hands
    Point hour_hand(0, 1, 0);
    hour_hand = rotation_z(num_time.at(0) * EIGEN_PI / 6) * hour_hand;
    hour_hand = scaling(clock_radius * 0.4) * hour_hand;

    Point min_hand(0, 1, 0);
    min_hand = rotation_z(num_time.at(1) * EIGEN_PI / 30) * min_hand;
    min_hand = scaling(clock_radius * 0.8) * min_hand;

    Point sec_hand(0, 1, 0);
    sec_hand = rotation_z(num_time.at(2) * EIGEN_PI / 30) * sec_hand;
    sec_hand = scaling(clock_radius * 0.6) * sec_hand;

    BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleLines(origin(0), origin(1), (int)clock_radius, WHITE);
        DrawLine(
            window_width / 2,
            window_height / 2,
            window_width / 2 - hour_hand(0),
            window_height / 2 - hour_hand(1),
            RED
        );
        DrawLine(
            window_width / 2,
            window_height / 2,
            window_width / 2 - min_hand(0),
            window_height / 2 - min_hand(1),
            RED
        );
        DrawLine(
            window_width / 2,
            window_height / 2,
            window_width / 2 - sec_hand(0),
            window_height / 2 - sec_hand(1),
            RED
        );
    EndDrawing();
}

void BookTest::ChapterFour() {
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
    Matrix4f half_quarter_x = rotation_x(EIGEN_PI / 4);
    Matrix4f full_quarter_x = rotation_x(EIGEN_PI / 2);
    p_output = Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2);
    assert((half_quarter_x * p).isApprox(p_output, THRESH));    // Account for floating point error

    p_output = Point(0, 0, 1);
    assert((full_quarter_x * p).isApprox(p_output, THRESH));

    Matrix4f inv_half_quarter_x = half_quarter_x.inverse();
    p_output = Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    assert((inv_half_quarter_x * p).isApprox(p_output, THRESH));

    // Testing rotation: Y-axis
    p = Point(0, 0, 1);
    Matrix4f half_quarter_y = rotation_y(EIGEN_PI / 4);
    Matrix4f full_quarter_y = rotation_y(EIGEN_PI / 2);
    p_output = Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2);
    assert((half_quarter_y * p).isApprox(p_output, THRESH));

    p_output = Point(1, 0, 0);
    assert((full_quarter_y * p).isApprox(p_output, THRESH)); 

    // Testing rotation: Z-axis
    p = Point(0, 1, 0);
    Matrix4f half_quarter_z = rotation_z(EIGEN_PI / 4);
    Matrix4f full_quarter_z = rotation_z(EIGEN_PI / 2);
    p_output = Point(-(std::sqrt(2) / 2), std::sqrt(2) / 2, 0);
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
    Matrix4f A = rotation_x(EIGEN_PI / 2);
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