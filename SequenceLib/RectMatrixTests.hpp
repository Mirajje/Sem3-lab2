#ifndef MAIN_CPP_RECTMATRIXTESTS_HPP
#define MAIN_CPP_RECTMATRIXTESTS_HPP

#include "RectMatrix.hpp"

class RectMatrixTests
{
private:
    static void constructorFromHeightAndWidthTest();
    static void equalityTest();
    static void constructorFromAnotherMatrixTest();
    static void constructorFromAnotherMatrixRvalueReferenceTest();
    static void oneEqualAnotherTest();
    static void oneEqualAnotherRvalueReferenceTest();

    static void sumTest();
    static void scalarMultiplyTest();
    static void matrixMultiplyTest();

    static void addStringTest();
    static void addColumnTest();
    static void popStringTest();
    static void popColumnTest();
    static void swapStringTest();
    static void swapColumnsTest();
    static void transposeTest();

public:
    static void allTestsTogether();
};

void RectMatrixTests::constructorFromHeightAndWidthTest()
{
    RectMatrix<int> matrix(5, 6);
    assert(matrix.getWidth() == 6);
    assert(matrix.getHeight() == 5);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            assert(matrix.get(i, j) == 0);
}

void RectMatrixTests::equalityTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2(5, 6);
    assert(matrix1 == matrix2);
    matrix1[0][2] = 15;
    assert(!(matrix1 == matrix2));
    matrix2[0][2] = 15;
    assert(matrix1 == matrix2);
}

void RectMatrixTests::constructorFromAnotherMatrixTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2 = matrix1;
    assert(matrix1 == matrix2);
}

void RectMatrixTests::constructorFromAnotherMatrixRvalueReferenceTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix1Copy = matrix1;
    RectMatrix<int> matrix2 = std::move(matrix1);
    assert(matrix1Copy == matrix2);
}

void RectMatrixTests::oneEqualAnotherTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2(2, 3);
    matrix2 = matrix1;
    assert(matrix1 == matrix2);
}

void RectMatrixTests::oneEqualAnotherRvalueReferenceTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix1Copy = matrix1;
    RectMatrix<int> matrix2(2, 3);
    matrix2 = std::move(matrix1);
    assert(matrix1Copy == matrix2);
}

void RectMatrixTests::sumTest()
{
    RectMatrix<int> matrix1(5, 6);
    RectMatrix<int> matrix2(5, 6);
    matrix1[0][0] = 5;
    matrix2[1][3] = 6;

    RectMatrix<int> result(5, 6);
    result[0][0] = 5; result[1][3] = 6;
    assert(matrix1 + matrix2 == result);
}

void RectMatrixTests::scalarMultiplyTest()
{
    RectMatrix<int> matrix1(5, 6);
    matrix1[0][0] = 5;

    RectMatrix<int> result(5, 6);
    result[0][0] = 15;
    assert(matrix1 * 3 == result);
    assert(3 * matrix1 == result);
}

void RectMatrixTests::addStringTest()
{
    int list[6] = {1, 2, 3, 4, 5, 6};
    RectMatrix<int> matrix(5, 6);
    Sequence<int>* seq = new ArraySequence<int>(list, 6);
    matrix.addString(*seq, 5);

    RectMatrix<int> result(6, 6);
    for (int i = 0; i < 6; i++)
        result[5][i] = i + 1;

    assert(matrix == result);
}

void RectMatrixTests::addColumnTest()
{
    int list[5] = {1, 2, 3, 4, 5};
    RectMatrix<int> matrix(5, 6);
    Sequence<int>* seq = new ArraySequence<int>(list, 5);
    matrix.addColumn(*seq, 6);

    RectMatrix<int> result(5, 7);
    for (int i = 0; i < 5; i++)
        result[i][6] = i + 1;

    assert(matrix == result);
}

void RectMatrixTests::popStringTest()
{
    int list[6] = {1, 2, 3, 4, 5, 6};
    RectMatrix<int> matrix(5, 6);
    for (int i = 0; i < 6; i++)
        matrix[4][i] = i + 1;

    Sequence<int>* seq = new ArraySequence<int>(list, 6);

    Sequence<int>* result = matrix.popString(4);

    assert(*result == *seq);
}

void RectMatrixTests::popColumnTest()
{
    int list[5] = {1, 2, 3, 4, 5};
    RectMatrix<int> matrix(5, 6);
    for (int i = 0; i < 5; i++)
        matrix[i][0] = i + 1;

    Sequence<int>* seq = new ArraySequence<int>(list, 5);

    Sequence<int>* result = matrix.popColumn(0);

    assert(*result == *seq);
}

void RectMatrixTests::swapStringTest()
{
    RectMatrix<int> matrix(5, 6);
    for (int i = 0; i < 6; i++)
        matrix[4][i] = i + 1;

    RectMatrix<int> result(5, 6);
    for (int i = 0; i < 6; i++)
        result[3][i] = i + 1;


    matrix.swapStrings(3, 4);

    assert(result == matrix);
}

void RectMatrixTests::swapColumnsTest()
{
    RectMatrix<int> matrix(5, 6);
    for (int i = 0; i < 5; i++)
        matrix[i][0] = i + 1;

    RectMatrix<int> result(5, 6);
    for (int i = 0; i < 5; i++)
        result[i][1] = i + 1;

    matrix.swapColumns(0, 1);
    assert(result == matrix);
}

void RectMatrixTests::transposeTest()
{
    RectMatrix<int> matrix(5, 6);
    for (int i = 0; i < 5; i++)
        matrix[i][0] = i + 1;

    matrix = std::move(matrix.transpose());

    RectMatrix<int> result(6, 5);
    for (int i = 0; i < 5; i++)
        result[0][i] = i + 1;

    assert(result == matrix);
}

void RectMatrixTests::matrixMultiplyTest()
{
    RectMatrix<int> matrix(2, 3);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            matrix[i][j] = i + j;

    RectMatrix<int> result(2, 2);
    result[0][0] = 5; result[0][1] = 8; result[1][0] = 8; result[1][1] = 14;

    matrix = matrix * matrix.transpose();
    assert(result == matrix);
}


void RectMatrixTests::allTestsTogether()
{
    constructorFromHeightAndWidthTest();
    equalityTest();
    constructorFromAnotherMatrixTest();
    constructorFromAnotherMatrixRvalueReferenceTest();
    oneEqualAnotherTest();
    oneEqualAnotherRvalueReferenceTest();
    sumTest();
    scalarMultiplyTest();
    addStringTest();
    addColumnTest();
    popStringTest();
    popColumnTest();
    swapStringTest();
    swapColumnsTest();
    transposeTest();
    matrixMultiplyTest();

}

#endif
