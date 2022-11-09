#ifndef HPP_TESTS_TOGETHER
#define HPP_TESTS_TOGETHER

#include "LinkedListTests.hpp"
#include "ListSequenceTests.hpp"
#include "DynamicArrayTests.hpp"
#include "ArraySequenceTests.hpp"
#include "RectMatrixTests.hpp"

void tests()
{
    /*LinkedListTests::allTestsTogether();
    ListSequenceTests::allTestsTogether();
    DynamicArrayTests::allTestsTogether();
    ArraySequenceTests::allTestsTogether();*/
    RectMatrixTests::allTestsTogether();
}

#endif