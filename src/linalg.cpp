#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "linalg.hpp"

// Linear algebra functions needed for ray tracing

/*
    Run following command to run program
    cmake .. && cmake --build . && ./raytracer
*/

std::vector<std::vector<int> > buildMatrix(int m, int n) {
    std::vector<std::vector<int> > A(m, std::vector<int>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A.at(i).at(j) = i*n + j;
        }
    }

    return A;
}

/**
 * @brief Performs matrix multiplication
 * @param A: Left matrix to be multiplied
 * @param B: Right matrix to be multiplied
 * @return Resulting matrix from multiplication
 */
std::vector<std::vector<int> > matmul(std::vector<std::vector<int> >& A, std::vector<std::vector<int> >& B) {
    int ma = A.size();
    int mb = B.size();

    if (ma < 1 || mb < 1)
        throw std::invalid_argument("Inputs are not matrices");

    int na = A.at(0).size();
    int nb = B.at(0).size();

    // for multiplication, na should equal mb

    if (na != mb)
        throw std::invalid_argument("Dimensions do not match");
    
    // initialize result matrix
    // dimensions: ma x nb
    std::vector<std::vector<int> > result(
        ma,
        std::vector<int>(nb)
    );

    // loop over both matrices and perform multiplication
    for (int i = 0; i < ma; i++) {
        for (int j = 0; j < nb; j++) {
            // for summing values in current overlapping row and column
            std::cout << result.at(i).at(j) << std::endl;
            for (int k = 0; k < ma; k++) {
                result.at(i).at(j) += A.at(i).at(k) * B.at(k).at(j);
            }
        }
    }

    std::cout << "Matrices multiplied successfully" << std::endl;

    return result;
}