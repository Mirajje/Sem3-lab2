#include <vector>
#include "tests.cpp"
#include "ComplexNumber.h"

int main()
{
    tests();

    int list[5] = {1, 2, 3, 4, 5};

    RectMatrix<ComplexNumber> matrix(2, 3);
    matrix[0][0] = ComplexNumber(15, 2);
    matrix.print();
    RectMatrix<ComplexNumber>matrix2 = matrix;
    (matrix + matrix2 * (5)).print();
    matrix = matrix.transpose();
    matrix.print();

}
