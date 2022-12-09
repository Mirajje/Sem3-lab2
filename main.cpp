#include <iostream>
#include "SequenceLib/Sequence_lib.h"
#include <memory>
#include <vector>
#include "HashTable.hpp"
#include "TheMostCommonSubSequence.hpp"
#include "HashTableTests.hpp"

int main()
{
    HashTableTests::allTestsTogether();
    IMap<std::string, std::vector<int>>* map = TheMostCommonSubSequence("abobaabobaaboba", 1, 5);
    for (auto& el : *map)
        std::cout << el.first << " " << el.second << "\n";


}
