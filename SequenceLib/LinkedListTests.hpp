#ifndef HPP_LINKED_LIST_TESTS
#define HPP_LINKED_LIST_TESTS

#include "LinkedList.hpp"
#include <cassert>

class LinkedListTests
{
private:
    static void constructorFromCountTest();
    static void constructorFromItemsAndCountTest();
    static void equalityTest();
    static void constructorFromLinkedListTest();
    static void constructorFromLinkedListRvalueReferenceTest();
    static void oneEqualAnotherRvalueReferenceTest();
    static void oneEqualAnotherTest();
    static void findTest();
    static void popTest();
    static void getSubListTest();
    static void appendTest();
    static void prependTest();
    static void insertAtTest();
    static void concatTest();
    static void mapTest();
    static void whereTest();
    static void reduceTest();

public:
    static void allTestsTogether();
};

void LinkedListTests::constructorFromCountTest()
{
    LinkedList<int> list(5);
    assert(list.getSize() == 5);
    for (int i = 0; i < 5; i++)
        assert(list.get(i) == 0);
}

void LinkedListTests::constructorFromItemsAndCountTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list(items, 5);

    assert(list.getSize() == 5);
    for (int i = 0; i < 5; i++)
        assert(list.get(i) == i + 1);
}

void LinkedListTests::equalityTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);

    LinkedList<int> list2(5);
    for (int i = 0; i < 5; i++)
        list2[i] = i + 1;

    assert(list1 == list2);
}

void LinkedListTests::constructorFromLinkedListTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);

    LinkedList<int> list2(list1);
    assert(list2 == list1);
}

void LinkedListTests::constructorFromLinkedListRvalueReferenceTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);
    LinkedList<int> list1Copy(list1);

    LinkedList<int> list2(std::move(list1));
    assert(list2 == list1Copy);
}

void LinkedListTests::oneEqualAnotherRvalueReferenceTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);

    LinkedList<int> list2;
    list2 = LinkedList<int>(items, 5);
    assert(list2 == list1);
}

void LinkedListTests::oneEqualAnotherTest()
{
    int items[5] = {1, 2, 3, 4, 5};
    LinkedList<int> list1(items, 5);

    LinkedList<int> list2;
    list2 = list1;
    assert(list2 == list1);
}

void LinkedListTests::findTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    LinkedList<int> list(items, 5);

    assert(list.find(0) == 0);
    assert(list.find(2) == 1);
    assert(list.find(4) == 3);
    assert(list.find(5) == 4);
    assert(list.find(-7) == -1);
}

void LinkedListTests::popTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    LinkedList<int> list(items, 5);

    assert(list.pop(3) == 4);
    assert(list.getSize() == 4);
}

void LinkedListTests::getSubListTest()
{
    int items1[5] = {0, 2, 2, 4, 5};
    int items2[4] = {2, 2, 4, 5};
    LinkedList<int> list1(items1, 5);
    LinkedList<int> list2 = *list1.getSubList(1, 4);

    list1 = LinkedList<int>(items2, 4);
    assert(list1 == list2);
}

void LinkedListTests::appendTest()
{
    LinkedList<int> list(0);
    list.append(5);
    list.append(3);
    int items[2] = {5, 3};
    assert(list == LinkedList<int>(items, 2));
}

void LinkedListTests::prependTest()
{
    LinkedList<int> list(0);
    list.prepend(5);
    list.prepend(3);
    int items[2] = {3, 5};
    assert(list == LinkedList<int>(items, 2));
}

void LinkedListTests::insertAtTest()
{
    LinkedList<int> list(0);
    list.insertAt(5, 0);
    list.insertAt(3, 1);
    int items[2] = {5, 3};
    assert(list == LinkedList<int>(items, 2));
}

void LinkedListTests::concatTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    LinkedList<int> list1(items, 5);
    LinkedList<int> list2(items, 5);

    int items2[10] = {0, 2, 2, 4, 5, 0, 2, 2, 4, 5};
    LinkedList<int> list3(items2, 10);
    assert(*list1.concat(&list2) == list3);
}

template <class T>
T func1(const T& s)
{
    return s + 3;
}

template <class T>
bool func2(const T& s)
{
    return (s > 3);
}

template <class T>
T func3(const T& v1, const T& v2)
{
    return (v1 + v2);
}

void LinkedListTests::mapTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    int items2[5] = {3, 5, 5, 7, 8};
    LinkedList<int> list1(items, 5);
    LinkedList<int> list2(items2, 5);

    assert(*list1.map(func1) == list2);
}

void LinkedListTests::whereTest()
{
    int items[5] = {0, 2, 2, 4, 5};
    int items2[5] = {4, 5};
    LinkedList<int> list1(items, 5);
    LinkedList<int> list2(items2, 2);

    assert(*list1.where(func2) == list2);
}

void LinkedListTests::reduceTest()
{
    int items[5] = {-1, 2, 2, 4, 5};
    LinkedList<int> list(items, 5);

    assert(list.reduce(func3, 4) == 16);
}

void LinkedListTests::allTestsTogether()
{
    constructorFromCountTest();
    constructorFromItemsAndCountTest();
    equalityTest();
    constructorFromLinkedListTest();
    constructorFromLinkedListRvalueReferenceTest();
    oneEqualAnotherRvalueReferenceTest();
    oneEqualAnotherTest();
    findTest();
    popTest();
    getSubListTest();
    appendTest();
    prependTest();
    insertAtTest();
    concatTest();
    mapTest();
    whereTest();
    reduceTest();

}


#endif