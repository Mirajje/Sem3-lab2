#ifndef MAIN_CPP_HASHTABLETESTS_HPP
#define MAIN_CPP_HASHTABLETESTS_HPP

#include <cassert>
#include <memory>
#include "HashTable.hpp"

class HashTableTests
{
public:
    static void allTestsTogether();

private:
    static void squareBracketsTest();
    static void deleteTest();

};

void HashTableTests::allTestsTogether()
{
    squareBracketsTest();
    deleteTest();
}

void HashTableTests::squareBracketsTest()
{
    HashTable<int, int> map;
    for (int i = 0; i < 17; i++)
        map[i] = -i;

    for (int i = 0; i < 17; i++)
        assert(map[i] == -i);
}

void HashTableTests::deleteTest()
{
    HashTable<int, int> map;
    assert(map.count(0) == 0);
    map[0] = 1;
    assert(map.count(0) == 1);
    map.del(0);
    assert(map.count(0) == 0);
}

#endif
