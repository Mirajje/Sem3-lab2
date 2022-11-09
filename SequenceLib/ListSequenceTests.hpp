#ifndef HPP_LIST_SEQUENCE_TESTS
#define HPP_LIST_SEQUENCE_TESTS

#include "Sequence_lib.h"
#include <cassert>

class ListSequenceTests
{
private:
    static void equalityTest();
    static void oneEqualAnotherTest();
    static void concatTest();

public:
    static void allTestsTogether();
};

void ListSequenceTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    ListSequence<int> list(items, 5);

    Sequence<int>* seq = new ListSequence<int>(items, 5);
    assert(list == *seq);
}

void ListSequenceTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};

    Sequence<int>* seq = new ListSequence<int>(items, 5);
    ListSequence<int> list;
    list = *seq;

    assert(list == *seq);
}

void ListSequenceTests::concatTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    int items2[10] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    ListSequence<int> list(items, 5);
    Sequence<int>* seq = new ListSequence<int>(items, 5);
    assert(*list.concat(seq) == ListSequence<int>(items2, 10));
}

void ListSequenceTests::allTestsTogether()
{
    equalityTest();
    oneEqualAnotherTest();
    concatTest();

}

#endif
