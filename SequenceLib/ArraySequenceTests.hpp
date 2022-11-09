#ifndef HPP_ARRAY_SEQUENCE_TESTS
#define HPP_ARRAY_SEQUENCE_TESTS

#include "Sequence_lib.h"
#include <cassert>
#include "LinkedListTests.hpp"

class ArraySequenceTests
{
private:
    static void findTest();
    static void equalityTest();
    static void oneEqualAnotherTest();
    static void getSubSequenceTest();
    static void insertAtTest();
    static void concatTest();
    static void popTest();
    static void mapTest();
    static void whereTest();
    static void reduceTest();

public:
    static void allTestsTogether();
};

void ArraySequenceTests::findTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    ArraySequence<int> ArraySequence(items, 5);

    assert(ArraySequence.find(0) == 0);
    assert(ArraySequence.find(2) == 1);
    assert(ArraySequence.find(4) == 3);
    assert(ArraySequence.find(5) == 4);
    assert(ArraySequence.find(-7) == -1);
}

void ArraySequenceTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    ArraySequence<int> array(items, 5);

    Sequence<int>* seq = new ArraySequence<int>(items, 5);
    assert(array == *seq);
}

void ArraySequenceTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    Sequence<int>* seq = new ArraySequence<int>(items, 5);
    ArraySequence<int> array;
    array = *seq;

    assert(array == *seq);
}

void ArraySequenceTests::getSubSequenceTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    ArraySequence<int> array1(items, 5);

    ArraySequence<int> array2(4);
    for (int i = 0; i < 4; i++)
        array2[i] = items[i + 1];

    Sequence<int>* seq = &array2;
    assert(*seq == *array1.getSubSequence(1, 4));
}

void ArraySequenceTests::insertAtTest()
{
    int items1[5] = {0, 2, 2, 4, 5};
    int items2[7] = {0, 2, 3, 2, 15, 4, 5};

    ArraySequence<int> array1(items1, 5);
    ArraySequence<int> array2(items2, 7);
    array1.insertAt(3, 2);
    array1.insertAt(15, 4);

    assert(array1 == array2);
}

void ArraySequenceTests::concatTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    int items2[10] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    ArraySequence<int> array(items, 5);
    Sequence<int>* seq = new ArraySequence<int>(items, 5);
    assert(*array.concat(seq) == ArraySequence<int>(items2, 10));
}

void ArraySequenceTests::popTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    ArraySequence<int> array(items, 5);

    assert(array.pop(3) == 4);
    assert(array.getLength() == 4);
}

void ArraySequenceTests::mapTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    int items2[5] = {3, 5, 5, 7, 8};
    ArraySequence<int> array1(items, 5);
    ArraySequence<int> array2(items2, 5);

    assert(*array1.map(func1) == array2);
}

void ArraySequenceTests::whereTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    int items2[5] = {4, 5};
    ArraySequence<int> array1(items, 5);
    ArraySequence<int> array2(items2, 2);

    assert(*array1.where(func2) == array2);
}

void ArraySequenceTests::reduceTest()
{
    int items[5] = {-1, 2, 2, 4, 5};
    ArraySequence<int> array(items, 5);

    assert(array.reduce(func3, 4) == 16);
}

void ArraySequenceTests::allTestsTogether()
{
    findTest();
    equalityTest();
    oneEqualAnotherTest();
    getSubSequenceTest();
    insertAtTest();
    concatTest();
    popTest();
    mapTest();
    whereTest();
    reduceTest();

}



#endif
