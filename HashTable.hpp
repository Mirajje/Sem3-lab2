#ifndef MAIN_CPP_HASHTABLE_HPP
#define MAIN_CPP_HASHTABLE_HPP

#include "SequenceLib/Sequence_lib.h"
#include <functional>

#include "SequenceLib/Sequence_lib.h"
#include <functional>

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& seq)
{
    for (int i = 0; i < seq.size(); i++)
        out << seq[i] << " ";

    return out;
}

template <class D, class T>
class HashTableIterator
{
public:

    using data = ListSequence<std::pair<D, T>>;

    HashTableIterator(ArraySequenceIterator<data*> _external_It, int _count, int _size)
        : external_It(_external_It)
    {
        size = _size;
        count = _count;
        if (*external_It && _count != _size)
            internal_It = (*external_It)->begin();

    }

    HashTableIterator(const HashTableIterator<D, T>& _it)
        : external_It(_it.external_It), internal_It(_it.internal_It)
    {
        size = _it.size;
        count = _it.count;
        external_It = _it.external_It;
        internal_It = _it.internal_It;
    }

    HashTableIterator& operator++()
    {
        if (internal_It.get())
            internal_It++;

        if (!internal_It.get())
        {
            external_It++;
            count++;
            while (!(*external_It))
            {
                external_It++;
                count++;
                if (count == size)
                    return *this;
            }

            if (*external_It)
                internal_It = (*external_It)->begin();

        }

        if (!(*external_It))
        {
            internal_It = ListSequenceIterator<std::pair<D, T>>();
        }

        return *this;
    }

    HashTableIterator& operator =(const HashTableIterator<D, T>& other)
    {
        if (this != &other)
        {
            count = other.count;
            size = other.size;
            external_It = other.external_It;
            internal_It = other.internal_It;
        }
        return *this;
    }

    bool operator ==(const HashTableIterator<D, T>& other) const
    {
        return (internal_It == other.internal_It && external_It == other.external_It);
    }

    bool operator !=(const HashTableIterator<D, T>& other) const
    {
        return (internal_It != other.internal_It || external_It != other.external_It);
    }

    std::pair<D, T>& operator*()
    {
        return *internal_It;
    }

private:
    ArraySequenceIterator<ListSequence<std::pair<D, T>>*> external_It;
    ListSequenceIterator<std::pair<D, T>> internal_It;
    int count, size;

};

template <class D, class T>
class HashTable
{
public:
    HashTable();
    explicit HashTable(int);
    HashTable(const std::initializer_list<std::pair<D, T>>&);
    HashTable(const HashTable<D, T>& other);
    HashTable(HashTable<D, T>&& other) noexcept;
    ~HashTable();

    HashTableIterator<D, T> begin();
    HashTableIterator<D, T> end();
    T& operator [](const D& key);
    int capacity();
    int size();
    int count(const D& key); // returns 0 or 1
    void del(const D& key);
    void print();

private:
    std::size_t hash(const D& key);
    void resize(int new_size);
    ArraySequence<ListSequence<std::pair<D, T>>*>* m_Data;
    int m_Size = 0;

};

template <class D, class T>
HashTable<D, T>::HashTable()
{
    m_Data = new ArraySequence<ListSequence<std::pair<D, T>>*>(15);
};

template <class D, class T>
HashTable<D, T>::HashTable(int size)
{
    m_Data = new ArraySequence<ListSequence<std::pair<D, T>>*>(size);
};

template<class D, class T>
HashTable<D, T>::HashTable(const std::initializer_list<std::pair<D, T>>& list)
{
    m_Data = new ArraySequence<ListSequence<std::pair<D, T>>*>(list.size());
    for (auto& el : list)
        (*this)[el.first] = el.second;
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
HashTable<D, T>::~HashTable()
{
    for (auto& el : *m_Data)
        delete el;
    delete m_Data;
};

template <class D, class T>
std::size_t HashTable<D, T>::hash(const D& key)
{
    return (std::hash<D>{}(key) % m_Data->getLength());
}

template <class D, class T>
void HashTable<D, T>::resize(int new_Size)
{
    auto* temp = m_Data;
    m_Data = new ArraySequence<ListSequence<std::pair<D, T>>*>(new_Size);
    m_Size = 0;

    for (auto& el : (*temp))
        if (el)
            for (auto& el2 : *el)
                (*this)[el2.first] = el2.second;

    delete temp;
};

template <class D, class T>
void HashTable<D, T>::print()
{
    for (auto& el : (*m_Data))
        if (el)
            for (auto& el2 : *(el))
                std::cout << el2.first << " " << el2.second << std::endl;
}

template<class D, class T>
HashTableIterator<D, T> HashTable<D, T>::begin()
{
    int count = 0;
    auto current = m_Data->begin();
    while (!(*current) && (current != m_Data->end()))
    {
        current++;
        count++;
    }
    return HashTableIterator<D, T>(current, count, m_Data->getLength());
}

template<class D, class T>
HashTableIterator<D, T> HashTable<D, T>::end()
{
    return HashTableIterator<D, T>(m_Data->end(), m_Data->getLength(), m_Data->getLength());
}

template<class D, class T>
int HashTable<D, T>::capacity()
{
    return m_Data->getLength();
}

template<class D, class T>
int HashTable<D, T>::size()
{
    return m_Size;
}

template<class D, class T>
T& HashTable<D, T>::operator[](const D& key)
{
    std::size_t index = hash(key);

    if (!(*m_Data)[index])
        (*m_Data)[index] = new ListSequence<std::pair<D, T>>;

    auto list = (*m_Data)[index];

    for (std::pair<D, T>& el : *list)
        if (el.first == key)
            return el.second;

    m_Size++;
    list->append(std::pair<D, T>(key, T()));

    if (m_Size >= m_Data->getLength() * 0.75)
    {
        this->resize(m_Data->getLength() * 2 + 1);
        return (*this)[key];
    }

    return (*list)[-1].second;
}

template<class D, class T>
int HashTable<D, T>::count(const D& key)
{
    int check = 0;
    std::size_t index = hash(key);

    if (index < m_Data->getLength() && (*m_Data)[index])
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
    std::size_t index = hash(key);

    if (this->count(key))
    {
        int i = 0;
        for (auto& el : *(*m_Data)[index])
        {
            if (el.first == key)
                break;
            i++;
        }

        (*m_Data)[index]->pop(i);
        m_Size--;
    }
}


#endif
