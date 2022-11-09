#ifndef MAIN_CPP_HASHTABLE_HPP
#define MAIN_CPP_HASHTABLE_HPP

#include "SequenceLib/Sequence_lib.h"
#include <functional>

template <class D, class T>
class HashTable
{
public:
    HashTable();
    HashTable(const HashTable<D, T>& other);
    HashTable(HashTable<D, T>&& other) noexcept;

    T& operator [](const D& key);
    int count(const D& key); // returns 0 or 1
    void del(const D& key);
    void print();

private:
    Sequence<ListSequence<std::pair<D, T>>*>* m_Data;
};

template <class D, class T>
HashTable<D, T>::HashTable()
{
    m_Data = new ArraySequence<ListSequence<std::pair<D, T>>*>(226);
};

template <class D, class T>
HashTable<D, T>::HashTable(const HashTable<D, T>& other)
{
    m_Data = new ArraySequence<ListSequence<std::pair<D, T>>*>(other.m_Data->getLength());
    for (int i = 0; i < m_Data->getLength(); i++)
    {
        if ((*other.m_Data)[i])
            (*m_Data)[i] = new ListSequence<std::pair<D, T>>( *((*other.m_Data)[i]) );
    }
};

template <class D, class T>
HashTable<D, T>::HashTable(HashTable<D, T>&& other) noexcept
{
    m_Data = other.m_Data;
    other.m_Data = nullptr;
};

template <class D, class T>
void HashTable<D, T>::print()
{
    for (int i = 0; i < m_Data->getLength(); i++)
        if ((*m_Data)[i])
            for (auto& el : *(*m_Data)[i])
                std::cout << el.first << " " << el.second << "\n";
}

template<class D, class T>
T& HashTable<D, T>::operator[](const D& key)
{
    std::size_t index = (std::hash<D>{}(key) % 57727);

    int multiplier = 1;
    while (m_Data->getLength() * multiplier < index)
    {
        multiplier *= 2;
    }

    if (multiplier > 1)
        m_Data = m_Data->concat(new ArraySequence<ListSequence<std::pair<D, T>>*>(m_Data->getLength() * (multiplier - 1)));

    if (!(*m_Data)[index])
        (*m_Data)[index] = new ListSequence<std::pair<D, T>>;

    auto list = (*m_Data)[index];

    for (std::pair<D, T>& el : *list)
        if (el.first == key)
            return el.second;

    list->append(std::pair<D, T>(key, T()));
    return (*list)[-1].second;
}

template<class D, class T>
int HashTable<D, T>::count(const D& key)
{
    int check = 0;
    std::size_t index = (std::hash<D>{}(key) % 57727);

    if ((*m_Data)[index])
    {
        for (auto& el : *(*m_Data)[index])
            if (el.first == key)
                check++;
    }

    return check;
}

template<class D, class T>
void HashTable<D, T>::del(const D &key)
{
    std::size_t index = (std::hash<D>{}(key) % 57727);

    if (this->count(key))
    {
        std::size_t index = (std::hash<D>{}(key) % 57727);
        int i = 0;
        for (auto& el : *(*m_Data)[index])
        {
            if (el.first == key)
                break;
            i++;
        }

        (*m_Data)[index]->pop(i);
    }
}


#endif
