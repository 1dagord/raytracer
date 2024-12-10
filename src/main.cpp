#include <iostream>
#include <string>
#include <array>
#include <Eigen/Dense>
#include <boost/lexical_cast.hpp>

#include "main.hpp"
#include "features.hpp"

#define print(x)  for(auto const& v: x) {std::cout << v << ",";} std::cout << "\n";
#define print_tuple(tup) std::cout << tup.x << " " << tup.y << " " << tup.z << std::endl;

using Eigen::MatrixXf;


int main() {

    // ----- Testing Tuple, Point, and Vector -----

    MatrixXf A = MatrixXf::Constant(4, 3, 1.0);
    MatrixXf B = MatrixXf::Constant(3, 2, 2.0);
    MatrixXf C = A * B;

    Point p1(0, 1, 2);
    Point p2(3, 4, 5);
    Point p3 = p1 + p2;

    Vector x(1, 0, 0);
    Vector y(0, 1, 0);

    Vector z = x.cross(y);

    print_tuple(z);


    // std::cout << A << std::endl;
    // std::cout << B << std::endl;
    // std::cout << C << std::endl;

    // for (int i = 0; i < C.rows(); i++) {
    //     for (int j = 0; j < C.cols(); j++) {
    //         std::cout << C(i, j);
    //     }
    //     std::cout << std::endl;
    // }

    // ----- Testing Tuple, Point, and Vector -----


    return 0;
}