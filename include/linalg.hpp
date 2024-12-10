#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
    public:
        std::vector<std::vector<int> > mat;
        int rows, cols;

        Matrix(int m, int n) :
            mat(m, std::vector<int>(n)),
            rows(m),
            cols(n)
        {}

        // need to implement indexing

};

std::vector<std::vector<int> > buildMatrix(int m, int n);
std::vector<std::vector<int> > matmul(std::vector<std::vector<int> >& A, std::vector<std::vector<int> >& B);

#endif