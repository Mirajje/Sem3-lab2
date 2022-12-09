#ifndef HPP_ARRAY_SEQUENCE
#define HPP_ARRAY_SEQUENCE

#include "Sequence.h"
#include "DynamicArray.hpp"
#include "Errors.h"

template <class T>
class ArraySequenceIterator
{
public:
    ArraySequenceIterator(const ArrayIterator<T>& it)
            : m_It(it){}

    ArraySequenceIterator(T* ptr)
            : m_It(ArrayIterator<T>(ptr)){}

    ArraySequenceIterator& operator++()
    {
        m_It ++;
        return *this;
    }

    ArraySequenceIterator operator++(int)
    {
        ArraySequenceIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    ArraySequenceIterator& operator--()
    {
        m_It --;
        return *this;
    }

    ArraySequenceIterator operator--(int)
    {
        ArraySequenceIterator<T> temp = *this;
        --(*this);
        return temp;
    }

    ArraySequenceIterator& operator =(const ArraySequenceIterator<T>& other)
    {
        if (this != &other)
            m_It = other.m_It;
        return *this;
    }

    bool operator ==(const ArraySequenceIterator<T>& other) const
    {
        return (m_It == other.m_It);
    }

    bool operator !=(const ArraySequenceIterator<T>& other) const
    {
        return (m_It != other.m_It);
    }

    T& operator*()
    {
        return *m_It;
    }

    T* get()
    {
        return m_It.get();
    }


private:

    ArrayIterator<T> m_It;

};

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T>* m_Array;

public:
    using Iterator = ArraySequenceIterator<T>;
public:
    ArraySequence();
    explicit ArraySequence(int count);
    ArraySequence(T* items, int count);
    ArraySequence(const std::initializer_list<T>& list);
    explicit ArraySequence(const DynamicArray<T>& other);
    explicit ArraySequence(DynamicArray<T>&& other);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence(ArraySequence<T>&& other) noexcept;
    explicit ArraySequence(const Sequence<T>& other);
    ~ArraySequence();

public:
    const T& get(int index) const;
    const T& getFirst() const;
    const T& getLast() const;
    int getLength() const;
    void resize(int new_Size);
    int find(const T& item) const;

public:
    Iterator begin();
    Iterator end();
    T& operator[](int index);
    ArraySequence<T>& operator =(const Sequence<T>& other);
    ArraySequence<T>& operator=(const std::initializer_list<T>& list);
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
ArraySequence<T>::ArraySequence()
{
    m_Array = new DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(int count)
{
    m_Array = new DynamicArray<T>(count);
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count)
{
    m_Array = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const std::initializer_list<T>& list)
{
    m_Array = new DynamicArray<T>(list);
}


template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& other)
{
    m_Array = new DynamicArray<T>(other);
}

template <class T>
ArraySequence<T>::ArraySequence(DynamicArray<T>&& other)
{
    m_Array = new DynamicArray<T>(std::move(other));
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other)
{
    m_Array = new DynamicArray<T>(*other.m_Array);
}

template <class T>
ArraySequence<T>::ArraySequence(ArraySequence<T>&& other) noexcept
{
    m_Array = new DynamicArray<T>(std::move(*other.m_Array));
}

template <class T>
ArraySequence<T>::ArraySequence(const Sequence<T>& other)
{
    m_Array = new DynamicArray<T>(other.getLength());
    for (int i = 0; i < other.getLength(); i++)
        m_Array->set(i, other.get(i));
}

template <class T>
ArraySequence<T>::~ArraySequence()
{
    delete m_Array;
}

template <class T>
const T& ArraySequence<T>::get(int index) const
{
    return m_Array->get(index);
}

template <class T>
const T& ArraySequence<T>::getFirst() const
{
    return m_Array->get(0);
}

template <class T>
const T& ArraySequence<T>::getLast() const
{
    return m_Array->get(m_Array->getSize() - 1);
}

template <class T>
int ArraySequence<T>::getLength() const
{
    return m_Array->getSize();
}

template <class T>
void ArraySequence<T>::resize(int new_size)
{
    m_Array->resize(new_size);
}

template <class T>
int ArraySequence<T>::find(const T& item) const
{
    for (int i = 0; i < m_Array->getSize(); i++)
        if (this->get(i) == item)
            return i;

    return -1;
}

template <class T>
ArraySequenceIterator<T> ArraySequence<T>::begin()
{
    return Iterator(m_Array->begin());
}

template <class T>
ArraySequenceIterator<T> ArraySequence<T>::end()
{
    return Iterator(m_Array->end());
}

template <class T>
T& ArraySequence<T>::operator[](int index)
{
    return (*m_Array)[index];
}

template <class T>
ArraySequence<T>& ArraySequence<T>::operator =(const Sequence<T>& other)
{
    if (this != &other)
    {
        DynamicArray<T> result(other.getLength());
        for (int i = 0; i < other.getLength(); i++)
            result[i] = other.get(i);

        *m_Array = result;
    }
    return *this;
}

template <class T>
ArraySequence<T>& ArraySequence<T>::operator=(const std::initializer_list<T>& list)
{
    (*m_Array) = list;
    return *this;
}

template <class T>
bool ArraySequence<T>::operator ==(const Sequence<T>& other) const
{
    if (m_Array->getSize() == other.getLength())
    {
        bool flag = true;
        for (int i = 0; i < m_Array->getSize(); i++)
            if (this->get(i) != other.get(i))
                flag = false;

        return flag;
    }

    return false;
}

template <class T>
void ArraySequence<T>::set(const T& item, int index)
{
    (*m_Array)[index] = item;
}

template <class T>
Sequence<T>* ArraySequence<T>::getSubSequence(int startIndex, int endIndex) const
{
    if (m_Array->getSize() == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (startIndex > endIndex || startIndex < 0 || endIndex >= m_Array->getSize())
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    auto* res = new ArraySequence<T>(endIndex - startIndex + 1);
    for (int i = startIndex; i < endIndex + 1; i++)
        (*res)[i - startIndex] = (*m_Array)[i];

    return res;
}

template <class T>
void ArraySequence<T>::insertAt(const T& item, int index)
{
    if (index < 0 || index > m_Array->getSize())
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    m_Array->resize(m_Array->getSize() + 1);

    T prev = (*m_Array)[index]; T temp;
    for (int i = index + 1; i < m_Array->getSize(); i++)
    {
        temp = (*m_Array)[i];
        (*m_Array)[i] = prev;
        prev = temp;
    }
    (*m_Array)[index] = item;
}

template <class T>
void ArraySequence<T>::append(const T& item)
{
    this->insertAt(item, m_Array->getSize());
}

template <class T>
void ArraySequence<T>::prepend(const T& item)
{
    this->insertAt(item, 0);
}

template <class T>
Sequence<T>* ArraySequence<T>::concat(Sequence<T>* other) const
{
    if (other == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    auto* resultArray = new ArraySequence<T>;
    *(resultArray->m_Array) = *(m_Array);

    for (int i = 0; i < other->getLength(); i++)
        resultArray->append((*other)[i]);

    return resultArray;
}

template <class T>
T&& ArraySequence<T>::pop(int index)
{
    return std::move(m_Array->pop(index));
}

template <class T>
void ArraySequence<T>::print() const
{
    m_Array->print();
}

template <class T>
Sequence<T>* ArraySequence<T>::map(T func(const T&)) const
{
    auto* result = new ArraySequence<T>(m_Array->getSize());
    for (int i = 0; i < m_Array->getSize(); i++)
        (*result)[i] = func(m_Array->get(i));

    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::where(bool func(const T&)) const
{
    int count = 0;
    for (int i = 0; i < m_Array->getSize(); i++)
        if (func(m_Array->get(i)))
            count += 1;

    auto* result = new ArraySequence<T>(count);

    int j = 0;
    for (int i = 0; i < m_Array->getSize(); i++)
        if (func(m_Array->get(i)))
        {
            result->set(m_Array->get(i), j);
            j += 1;
        }

    return result;
}

template <class T>
T ArraySequence<T>::reduce(T func(const T&, const T&), const T& startValue) const
{
    T result = startValue;
    for (int i = 0; i < m_Array->getSize(); i++)
    {
        result = func(m_Array->get(i), result);
    }
    return result;
}

#endif