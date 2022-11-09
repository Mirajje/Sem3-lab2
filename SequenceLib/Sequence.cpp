#ifndef CPP_SEQUENCE
#define CPP_SEQUENCE

#include "Sequence.h"

template <class T>
std::ostream& operator<<(std::ostream& out, const Sequence<T>& seq)
{
    for (int i = 0; i < seq.getLength(); i++)
        out << seq.get(i) << " ";

    return out;
}

#endif