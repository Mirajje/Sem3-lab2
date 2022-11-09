#include <iostream>
#include "SequenceLib/Sequence_lib.h"
#include <memory>
#include <vector>
#include "HashTable.hpp"

int main()
{
    HashTable<int, int> map;
    map[2] = 3;
    map[2] = 4;
    map[2] = 5;
    map[3] = 4;
    map[57729] = 5;

    map.print();

    map.del(2);
    map.print();

    return 0;
}
