#ifndef MAIN_CPP_HASHFUNCTION_HPP
#define MAIN_CPP_HASHFUNCTION_HPP
#include <unordered_map>

#include "SequenceLib/Sequence_lib.h"

template <class T>
class HashFunctions
{
    int hashFunction(const T& elem);
    std::unordered_map<int, int> a;
    a.insert(5);
};

template <>
int HashFunctions<T>::has

template<class T>
int HashFunctions<T>::hashFunction(const T &elem)
{

}

#endif
