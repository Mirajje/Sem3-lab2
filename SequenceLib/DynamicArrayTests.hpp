#ifndef HPP_DYNAMIC_ARRAY_TESTS
#define HPP_DYNAMIC_ARRAY_TESTS

#include "DynamicArray.hpp"
#include <cassert>

class DynamicArrayTests
{
private:
    static void constructorFromCountTest();
    static void constructorFromItemsAndCountTest();
    static void equalityTest();
    static void constructorFromDynamicArrayTest();
    static void constructorFromDynamicArrayRvalueReferenceTest();
    static void oneEqualAnotherRvalueReferenceTest();
    static void oneEqualAnotherTest();
    static void resizeTest();
    static void popTest();

public:
    static void allTestsTogether();
};

void DynamicArrayTests::constructorFromCountTest()
{
    DynamicArray<int> array(5);
    assert(array.getSize() == 5);
    for (int i = 0; i < 5; i++)
        assert(array.get(i) == 0);
}

void DynamicArrayTests::constructorFromItemsAndCountTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(items, 5);

    assert(array.getSize() == 5);
    for (int i = 0; i < 5; i++)
        assert(array.get(i) == i + 1);
}

void DynamicArrayTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array1(items, 5);

    DynamicArray<int> array2(5);
    for (int i = 0; i < 5; i++)
        array2[i] = i + 1;

    assert(array1 == array2);
}

void DynamicArrayTests::constructorFromDynamicArrayTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array1(items, 5);

    DynamicArray<int> array2(array1);
    assert(array1 == array2);
}

void DynamicArrayTests::constructorFromDynamicArrayRvalueReferenceTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array1(items, 5);
    DynamicArray<int> array1Copy(array1);

    DynamicArray<int> array2(std::move(array1));
    assert(array1Copy == array2);
}


void DynamicArrayTests::oneEqualAnotherRvalueReferenceTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array1(items, 5);

    DynamicArray<int> array2;
    array2 = DynamicArray<int>(items, 5);
    assert(array2 == array1);
}

void DynamicArrayTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> array1(items, 5);

    DynamicArray<int> array2;
    array2 = array1;
    assert(array2 == array1);
}

void DynamicArrayTests::resizeTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    int items2[6] = {0, 2, 2, 4, 5, 0};
    int items3[4] = {0, 2, 2, 4};
    DynamicArray<int> array1(items, 5);
    DynamicArray<int> array2(items2, 6);

    array1.resize(6);
    assert(array1 == array2);
    array1.resize(4);
    array2 = DynamicArray<int>(items3, 4);
    assert(array1 == array2);
}

void DynamicArrayTests::popTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    DynamicArray<int> array(items, 5);

    assert(array.pop(3) == 4);
    assert(array.getSize() == 4);
}

void DynamicArrayTests::allTestsTogether()
{
    constructorFromCountTest();
    constructorFromItemsAndCountTest();
    equalityTest();
    constructorFromDynamicArrayTest();
    constructorFromDynamicArrayRvalueReferenceTest();
    oneEqualAnotherRvalueReferenceTest();
    oneEqualAnotherTest();
    resizeTest();
    popTest();

}

#endif
