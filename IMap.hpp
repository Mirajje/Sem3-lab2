#ifndef MAIN_CPP_IMAP_HPP
#define MAIN_CPP_IMAP_HPP

#include "HashTable.hpp"

template <class D, class T>
class IMapIterator
{
public:
    using data = ListSequence<std::pair<D, T>>;

    IMapIterator(ArraySequenceIterator<data*> _external_It, int _count, int _size)
        : it(_external_It, _count, _size){};

    explicit IMapIterator(const HashTableIterator<D, T>& _it)
            : it(_it){};

    IMapIterator& operator++()
    {
        ++it;
        return *this;
    }

    IMapIterator& operator =(const IMapIterator<D, T>& other)
    {
        if (this != &other)
            it = other.it;

        return *this;
    }

    bool operator ==(const IMapIterator<D, T>& other) const
    {
        return (it == other.it);
    }

    bool operator !=(const IMapIterator<D, T>& other) const
    {
        return (it != other.it);
    }

    std::pair<D, T>& operator*()
    {
        return *it;
    }


private:
    HashTableIterator<D, T> it;
};

template <class D, class T>
class IMap
{
public:
    IMap();
    IMap(const std::initializer_list<std::pair<D, T>>&);
    IMap(const IMap<D, T>& other);
    IMap(IMap<D, T>&& other) noexcept;
    ~IMap();

    IMapIterator<D, T> begin();
    IMapIterator<D, T> end();
    T& operator [](const D& key);
    int size();
    int count(const D& key); // returns 0 or 1
    void del(const D& key);

private:
    HashTable<D, T>* m_Data;

};

template <class D, class T>
IMap<D, T>::IMap()
{
    m_Data = new HashTable<D, T>(15);
};

template<class D, class T>
IMap<D, T>::IMap(const std::initializer_list<std::pair<D, T>>& list)
{
    m_Data = new HashTable<D, T>(list);
};

template <class D, class T>
IMap<D, T>::IMap(const IMap<D, T>& other)
{
    m_Data = new HashTable<D, T>(other.m_Data);
};

template <class D, class T>
IMap<D, T>::IMap(IMap<D, T>&& other) noexcept
{
    m_Data = other.m_Data;
    other.m_Data = nullptr;
};

template <class D, class T>
IMap<D, T>::~IMap()
{
    delete m_Data;
};

template<class D, class T>
IMapIterator<D, T> IMap<D, T>::begin()
{
    return IMapIterator<D, T>(m_Data->begin());
}

template<class D, class T>
IMapIterator<D, T> IMap<D, T>::end()
{
    return IMapIterator<D, T>(m_Data->end());
}

template<class D, class T>
int IMap<D, T>::size()
{
    return m_Data->size();
}

template<class D, class T>
T& IMap<D, T>::operator[](const D& key)
{
    return (*m_Data)[key];
}

template<class D, class T>
int IMap<D, T>::count(const D& key)
{
    return m_Data->count(key);
}

template<class D, class T>
void IMap<D, T>::del(const D &key)
{
    m_Data->del(key);
}

#endif
