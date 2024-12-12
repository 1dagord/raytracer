#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <Eigen/Dense>

#define print(x)  for(auto const& v: x) {std::cout << v << ",";} std::cout << "\n";
#define print_tuple(tup) std::cout << tup.x << " " << tup.y << " " << tup.z << std::endl;

using Eigen::MatrixXf;
using Eigen::Vector3f;


void testFunc() {

    // ----- Testing Tuple, Point, and Vector -----


    MatrixXf A = MatrixXf::Constant(4, 3, 1.0);
    MatrixXf B = MatrixXf::Constant(3, 2, 2.0);
    MatrixXf C = A * B;

    Vector3f p1(0, 1, 2);
    Vector3f p2(3, 4, 5);
    Vector3f p3 = p1 + p2;

    Vector3f x(1, 0, 0);
    Vector3f y(0, 1, 0);

    Vector3f z = x.cross(y);

    // testing cross product
    std::cout << z(2) << std::endl;

    // testing matrix print
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;

    // testing item access in matrix
    for (int i = 0; i < C.rows(); i++) {
        for (int j = 0; j < C.cols(); j++) {
            std::cout << C(i, j);
        }
        std::cout << std::endl;
    }

    // ----- Testing Tuple, Point, and Vector -----

}