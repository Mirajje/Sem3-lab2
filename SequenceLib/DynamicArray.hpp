#ifndef HPP_DYNAMIC_ARRAY
#define HPP_DYNAMIC_ARRAY

#include <iostream>
#include "Errors.h"

template <class T>
class ArrayIterator
{
public:
    ArrayIterator(T* ptr)
        : m_Ptr(ptr){}

    ArrayIterator& operator++()
    {
        m_Ptr ++;
        return *this;
    }

    ArrayIterator operator++(int)
    {
        ArrayIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    ArrayIterator& operator--()
    {
        m_Ptr --;
        return *this;
    }

    ArrayIterator operator--(int)
    {
        ArrayIterator<T> temp = *this;
        --(*this);
        return temp;
    }

    ArrayIterator& operator =(const ArrayIterator<T>& other)
    {
        if (this != &other)
            m_Ptr = other.m_Ptr;
        return *this;
    }

    bool operator ==(const ArrayIterator<T>& other) const
    {
        return (m_Ptr == other.m_Ptr);
    }

    bool operator !=(const ArrayIterator<T>& other) const
    {
        return (m_Ptr != other.m_Ptr);
    }

    T& operator*()
    {
        return *m_Ptr;
    }

private:
    T* m_Ptr;

};

template <class T>
class DynamicArray
{
private:
    T* m_Data = nullptr;
    int m_Size = 0;
    int m_Capacity = 0;

public:
    using Iterator = ArrayIterator<T>;

public:
    DynamicArray();
    explicit DynamicArray(int size);
    DynamicArray(T* items, int count);
    DynamicArray(const std::initializer_list<T>& list);
    DynamicArray(const DynamicArray<T>& other);
    DynamicArray(DynamicArray<T>&& other) noexcept;
    ~DynamicArray();

public:
    Iterator begin();
    Iterator end();
    T& operator[](int index);
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(const std::initializer_list<T>& list);
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept;
    bool operator ==(const DynamicArray<T>&);

public:
    const T& get(int index) const;
    int getSize() const;
    void set(int index, const T& value);
    void resize(int new_Size);
    T&& pop(int index);
    void print() const;

};

template <class T>
DynamicArray<T>::DynamicArray() = default;

template <class T>
DynamicArray<T>::DynamicArray(int size)
{
    if (size < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);
    m_Size = size;
    m_Capacity = size;
    m_Data = new T[m_Size]();
}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count)
{
    if (items == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    if (count < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    m_Size = count;
    m_Capacity = m_Size;
    m_Data = new T[m_Size];

    for (int i = 0; i < count; i++)
        m_Data[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
    m_Size = other.m_Size;
    m_Capacity = m_Size;
    m_Data = new T[m_Size];

    for (int i = 0; i < m_Size; i++)
        m_Data[i] = other.m_Data[i];
}

template <class T>
DynamicArray<T>::DynamicArray(const std::initializer_list<T>& list)
{
    m_Size = list.size();
    m_Capacity = m_Size;
    m_Data = new T[m_Size];

    for (int i = 0; i < m_Size; i++)
        m_Data[i] = list.begin()[i];
}

template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& other) noexcept
{
    m_Size = other.m_Size;
    m_Capacity = m_Size;
    m_Data = other.m_Data;

    other.m_Data = nullptr;
    other.m_Size = 0;
    other.m_Capacity = 0;
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] m_Data;
}

template <class T>
ArrayIterator<T> DynamicArray<T>::begin()
{
    return Iterator(m_Data);
}

template <class T>
ArrayIterator<T> DynamicArray<T>::end()
{
    return Iterator(&m_Data[m_Size]);
}

template <class T>
T& DynamicArray<T>::operator[](int index)
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    return m_Data[index];
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
    if (this != &other)
    {
        delete[] m_Data;
        m_Size = other.m_Size;
        m_Capacity = m_Size;
        m_Data = new T[m_Size];
        for (int i = 0; i < m_Size; i++)
            m_Data[i] = other.m_Data[i];
    }

    return *this;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const std::initializer_list<T>& list)
{
    this->resize(list.size());
    for (int i = 0; i < m_Size; i++)
        m_Data[i] = list.begin()[i];
    return *this;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept
{
    if (this != &other)
    {
        delete[] m_Data;
        m_Size = other.m_Size;
        m_Capacity = m_Size;
        m_Data = other.m_Data;

        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }

    return *this;
}

template <class T>
bool DynamicArray<T>::operator ==(const DynamicArray<T>& other)
{
    if (m_Size == other.getSize())
    {
        bool flag = true;
        for (int i = 0; i < m_Size; i++)
            if (this->get(i) != other.get(i))
                flag = false;

        return flag;
    }

    return false;
}

template <class T>
const T& DynamicArray<T>::get(int index) const
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    return m_Data[index];
}

template <class T>
int DynamicArray<T>::getSize() const { return m_Size; }

template <class T>
void DynamicArray<T>::set(int index, const T& value)
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    m_Data[index] = value;
}

template <class T>
void DynamicArray<T>::resize(int new_Size)
{
    if (new_Size < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    bool flag = false;
    while (m_Capacity < new_Size)
    {
        if (m_Capacity != 0)
            m_Capacity *= 2;
        else
            m_Capacity += 1;
        flag = true;
    }


    if (flag)
    {
        T* new_Data = new T[m_Capacity]();

        for (int i = 0; i < std::min(new_Size, m_Size); i++)
            new_Data[i] = m_Data[i];

        delete[] m_Data;
        m_Data = new_Data;
    }
    else
    {
        for (int i = new_Size; i < m_Size; i++)
            m_Data[i] = T();
    }
    m_Size = new_Size;
}

template <class T>
T&& DynamicArray<T>::pop(int index)
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index >= m_Size || index < 0)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    T* ans = new T(m_Data[index]);

    T* result_Data = new T[m_Capacity - 1]();

    for (int i = 0; i < m_Size - 1; i++)
        if (i < index)
            result_Data[i] = m_Data[i];
        else
            result_Data[i] = m_Data[i + 1];

    m_Size -= 1;
    m_Capacity -= 1;
    delete m_Data;
    m_Data = result_Data;
    return std::move(*ans);
}

template <class T>
void DynamicArray<T>::print() const
{
    if (m_Data != nullptr)
        for (int i = 0; i < m_Size; i++)
            std::cout << m_Data[i] << ' ';
    std::cout << '\n';
}

#endif