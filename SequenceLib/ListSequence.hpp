#ifndef HPP_LIST_SEQUENCE
#define HPP_LIST_SEQUENCE

#include "LinkedList.hpp"
#include "Sequence.h"

template <class T>
class ListSequenceIterator
{
public:
    ListSequenceIterator(const ListIterator<T>& it)
            : m_It(it){}

    ListSequenceIterator& operator++()
    {
        m_It ++;
        return *this;
    }

    ListSequenceIterator operator++(int)
    {
        ArraySequenceIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    ListSequenceIterator& operator--()
    {
        m_It --;
        return *this;
    }

    ListSequenceIterator operator--(int)
    {
        ArraySequenceIterator<T> temp = *this;
        --(*this);
        return temp;
    }

    ListSequenceIterator& operator =(const ListSequenceIterator<T>& other)
    {
        if (this != &other)
            m_It = other.m_It;
        return *this;
    }

    bool operator ==(const ListSequenceIterator<T>& other) const
    {
        return (m_It == other.m_It);
    }

    bool operator !=(const ListSequenceIterator<T>& other) const
    {
        return (m_It != other.m_It);
    }

    T& operator*()
    {
        return *m_It;
    }

private:

    ListIterator<T> m_It;

};

template <class T>
class ListSequence : public Sequence<T>
{
private:
    LinkedList<T>* m_List;

public:
    using Iterator = ListSequenceIterator<T>;

public:
    ListSequence();
    explicit ListSequence(int count);
    ListSequence(T* items, int count);
    ListSequence(const std::initializer_list<T>& list);
    explicit ListSequence(const LinkedList<T>& other);
    explicit ListSequence(LinkedList<T>&& other);
    ListSequence(const ListSequence<T>& other);
    ListSequence(ListSequence<T>&& other) noexcept;
    explicit ListSequence(const Sequence<T>& other);
    ~ListSequence();

public:
    const T& get(int index) const;
    const T& getFirst() const;
    const T& getLast() const;
    int getLength() const;
    int find(const T& item) const;

public:
    Iterator begin();
    Iterator end();
    T& operator[](int index);
    ListSequence<T>& operator =(const std::initializer_list<T>& list);
    ListSequence<T>& operator =(const Sequence<T>& other);
    bool operator ==(const Sequence<T>& other) const;

public:
    void set(const T& item, int index);
    Sequence<T>* getSubSequence(int startIndex, int endIndex) const;
    void insertAt(const T& item, int index);
    void append(const T& item);
    void prepend(const T& item);
    Sequence<T>* concat(Sequence<T>* other) const;
    T&& pop(int index);
    void print() const;

public:
    Sequence<T>* map(T func(const T&)) const;
    Sequence<T>* where(bool func(const T&)) const;
    T reduce(T func(const T&, const T&), const T& startValue) const;

};

template <class T>
ListSequence<T>::ListSequence()
{
    m_List = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(int count)
{
    m_List = new LinkedList<T>(count);
}

template <class T>
ListSequence<T>::ListSequence(T* items, int count)
{
    m_List = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(const std::initializer_list<T>& list)
{
    m_List = new LinkedList<T>(list);
}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& other)
{
    m_List = new LinkedList<T>(other);
}

template <class T>
ListSequence<T>::ListSequence(LinkedList<T>&& other)
{
    m_List = new LinkedList<T>(std::move(other));
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other)
{
    m_List = new LinkedList<T>(*other.m_List);
}

template <class T>
ListSequence<T>::ListSequence(ListSequence<T>&& other) noexcept
{
    m_List = new LinkedList<T>(std::move(*other.m_List));
}

template <class T>
ListSequence<T>::ListSequence(const Sequence<T>& other)
{
    m_List = new LinkedList<T>;
    for (int i = 0; i < other.getLength(); i++)
        m_List->append(other.get(i));
}

template <class T>
ListSequence<T>::~ListSequence()
{
    delete m_List;
}

template <class T>
const T& ListSequence<T>::get(int index) const
{
    return m_List->get(index);
}

template <class T>
const T& ListSequence<T>::getFirst() const
{
    return m_List->getFirst();
}

template <class T>
const T& ListSequence<T>::getLast() const
{
    return m_List->getLast();
}

template <class T>
int ListSequence<T>::getLength() const
{
    return m_List->getSize();
}

template <class T>
int ListSequence<T>::find(const T& item) const
{
    return m_List->find(item);
}

template <class T>
ListSequenceIterator<T> ListSequence<T>::begin()
{
    return Iterator(m_List->begin());
}

template <class T>
ListSequenceIterator<T> ListSequence<T>::end()
{
    return Iterator(m_List->end());
}

template <class T>
T& ListSequence<T>::operator[](int index)
{
    return (*m_List)[index];
}

template <class T>
ListSequence<T>& ListSequence<T>::operator =(const Sequence<T>& other)
{
    if (this != &other)
    {
        delete m_List;

        m_List = new LinkedList<T>;
        for (int i = 0; i < other.getLength(); i++)
            m_List->append(other.get(i));
    }
    return *this;
}

template <class T>
ListSequence<T>& ListSequence<T>::operator =(const std::initializer_list<T>& list)
{
    (*m_List) = list;

    return *this;
}

template <class T>
bool ListSequence<T>::operator ==(const Sequence<T>& other) const
{
    if (m_List->getSize() == other.getLength())
    {
        bool flag = true;
        for (int i = 0; i < m_List->getSize(); i++)
            if (this->get(i) != other.get(i))
                flag = false;

        return flag;
    }

    return false;
}

template <class T>
void ListSequence<T>::set(const T& item, int index)
{
    (*m_List)[index] = item;
}

template <class T>
Sequence<T>* ListSequence<T>::getSubSequence(int startIndex, int endIndex) const
{
    auto* res = new ListSequence<T>(*m_List->getSubList(startIndex, endIndex));
    return res;
}

template <class T>
void ListSequence<T>::insertAt(const T& item, int index)
{
    m_List->insertAt(item, index);
}

template <class T>
void ListSequence<T>::append(const T& item)
{
    m_List->append(item);
}

template <class T>
void ListSequence<T>::prepend(const T& item)
{
    m_List->prepend(item);
}

template <class T>
Sequence<T>* ListSequence<T>::concat(Sequence<T>* other) const
{
    if (other == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    auto* resultList = new ListSequence<T>;
    *(resultList->m_List) = *(m_List);

    for (int i = 0; i < other->getLength(); i++)
        resultList->append((*other)[i]);

    return resultList;
}

template <class T>
T&& ListSequence<T>::pop(int index)
{
    return std::move(m_List->pop(index));
}

template <class T>
void ListSequence<T>::print() const
{
    m_List->print();
}

template <class T>
Sequence<T>* ListSequence<T>::map(T func(const T&)) const
{
    return new ListSequence<T>(*(m_List->map(func)));
}

template <class T>
Sequence<T>* ListSequence<T>::where(bool func(const T&)) const
{
    return new ListSequence<T>(*(m_List->where(func)));
}

template <class T>
T ListSequence<T>::reduce(T func(const T&, const T&), const T& startValue) const
{
    return m_List->reduce(func, startValue);
}

#endif