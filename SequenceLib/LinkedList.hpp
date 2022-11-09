#ifndef HPP_LINKED_LIST
#define HPP_LINKED_LIST

#include <iostream>
#include "Errors.h"

template <class T, class D>
std::ostream& operator << (std::ostream& output, const std::pair<T, D>& data)
{
    output << data.first << " " << data.second << "\n";
    return output;
}

template<class T>
struct Node
{
    T value;
    Node* next;
    Node* prev;
};

template <class T>
class ListIterator
{
public:
    ListIterator(Node<T>* ptr)
            : m_Ptr(ptr){}

    ListIterator& operator++()
    {
        m_Ptr = m_Ptr->next;
        return *this;
    }

    ListIterator operator++(int)
    {
        ListIterator<T> temp = *this;
        ++(*this);
        return temp;
    }

    ListIterator& operator--()
    {
        m_Ptr = m_Ptr->prev;
        return *this;
    }

    ListIterator operator--(int)
    {
        ListIterator<T> temp = *this;
        --(*this);
        return temp;
    }

    ListIterator& operator =(const ListIterator<T>& other)
    {
        if (this != &other)
            m_Ptr = other.m_Ptr;
        return *this;
    }

    bool operator ==(const ListIterator<T>& other) const
    {
        return (m_Ptr == other.m_Ptr);
    }

    bool operator !=(const ListIterator<T>& other) const
    {
        return (m_Ptr != other.m_Ptr);
    }

    T& operator*()
    {
        return m_Ptr->value;
    }

private:
    Node<T>* m_Ptr;

};

template<typename T>
class LinkedList{
private:
    Node<T>* m_Head = nullptr;
    Node<T>* m_Tail = nullptr;
    int m_Size = 0;

public:
    using Iterator = ListIterator<T>;

public:
    LinkedList();
    explicit LinkedList(int count);
    LinkedList(T* items, int count);
    LinkedList(const std::initializer_list<T>& list);
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    ~LinkedList();

public:
    Iterator begin();
    Iterator end();
    T& operator[](int index);
    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(const std::initializer_list<T>& list);
    LinkedList& operator=(LinkedList&& other) noexcept;
    bool operator ==(const LinkedList& other) const;

public:
    int getSize() const;
    const T& get(int index) const;
    const T& getFirst() const;
    const T& getLast() const;
    int find(T item) const;
    T&& pop(int index);
    LinkedList<T>* getSubList(int startIndex, int endIndex) const;
    void append(const T& item);
    void prepend(const T& item);
    void insertAt(const T& item, int index);
    LinkedList<T>* concat(LinkedList<T>* other);
    void print() const;
    void reversed_print() const;
    LinkedList<T>* map(T func(const T&)) const;
    LinkedList<T>* where(bool func(const T&)) const;
    T reduce(T func(const T&, const T&), const T& startValue) const;

};

template <class T>
LinkedList<T>::LinkedList() = default;

template <class T>
LinkedList<T>::LinkedList(int count)
{
    if (count < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    if (count > 0)
        m_Head = new Node<T>;

    Node<T> *current = m_Head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < count; i++)
    {
        current->value = T();
        current->prev = previous;
        if (i != count - 1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }
    if (current != nullptr)
    {
        m_Tail = current;
        m_Tail->next = nullptr;
    }
    m_Size = count;
}

template <class T>
LinkedList<T>::LinkedList(T* items, int count)
{
    if (items == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    if (count < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    if (count > 0)
        m_Head = new Node<T>;
    Node<T> *current = m_Head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < count; i++)
    {
        current->value = items[i];
        current->prev = previous;
        if (i != count - 1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }
    if (current != nullptr)
    {
        m_Tail = current;
        m_Tail->next = nullptr;
    }
    m_Size = count;
}

template <class T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& list)
{
    m_Size = list.size();
    if (m_Size > 0)
        m_Head = new Node<T>;
    Node<T> *current = m_Head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < m_Size; i++)
    {
        current->value = list.begin()[i];
        current->prev = previous;
        if (i != m_Size - 1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }
    if (current != nullptr)
    {
        m_Tail = current;
        m_Tail->next = nullptr;
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
    if (other.m_Size > 0)
    {
        m_Head = new Node<T>;
    }

    m_Size = other.m_Size;

    Node<T> *current = m_Head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < m_Size; i++)
    {
        current->value = other.get(i);
        current->prev = previous;
        if (i != m_Size - 1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }
    if (current != nullptr)
    {
        m_Tail = current;
        m_Tail->next = nullptr;
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
{
    m_Head = other.m_Head;
    m_Tail = other.m_Tail;
    m_Size = other.m_Size;

    other.m_Head = nullptr;
    other.m_Tail = nullptr;
    other.m_Size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    if (m_Head != nullptr)
    {
        Node<T> *current = m_Head;
        while (current->next != nullptr)
        {
            current = current->next;
            delete current->prev;
        }
        delete current;
    }
}

template <class T>
ListIterator<T> LinkedList<T>::begin()
{
    return Iterator(m_Head);
}

template <class T>
ListIterator<T> LinkedList<T>::end()
{
    return Iterator(nullptr);
}

template <class T>
T& LinkedList<T>::operator[](int index)
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index == -1)
        return m_Tail->value;

    if (index < 0 || index >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T>* current = m_Head;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->value;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
{
    if (this != &other)
    {
        Node<T>* current = m_Head;
        if (m_Head != nullptr)
        {
            while (current->next != nullptr)
            {
                current = current->next;
                delete current->prev;
            }
            delete current;
        }

        m_Head = nullptr; m_Tail = nullptr; m_Size = 0;
        if (other.m_Size > 0)
        {
            m_Size = other.m_Size;
            m_Head = new Node<T>;
        }

        current = m_Head;
        Node<T> *previous = nullptr;

        for (int i = 0; i < m_Size; i++)
        {
            current->value = other.get(i);
            current->prev = previous;
            if (i != m_Size - 1)
            {
                previous = current;
                current->next = new Node<T>;
                current = current->next;
            }
        }
        if (current != nullptr)
        {
            m_Tail = current;
            m_Tail->next = nullptr;
        }

    }

    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const std::initializer_list<T>& list)
{
    Node<T>* current;
    current = m_Head;
    for (int i = 0; i < list.size(); i++)
    {
        if (current == nullptr)
        {
            this->append(list.begin()[i]);
            continue;
        }

        current->value = list.begin()[i];
        m_Tail = current;
        current = current->next;
    }
    m_Tail->next = nullptr;
    m_Size = list.size();
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept
{
    if (this != &other)
    {
        Node<T> *current = m_Head;
        if (m_Head != nullptr)
        {
            while (current->next != nullptr)
            {
                current = current->next;
                delete current->prev;
            }
            delete current;
        }

        m_Head = other.m_Head;
        m_Size = other.m_Size;
        m_Tail = other.m_Tail;

        other.m_Head = nullptr;
        other.m_Tail = nullptr;
        other.m_Size = 0;
    }

    return *this;
}

template <class T>
bool LinkedList<T>::operator ==(const LinkedList& other) const
{
    if (m_Size == other.m_Size)
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
int LinkedList<T>::getSize() const { return m_Size; }

template <class T>
const T& LinkedList<T>::get(int index) const
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T>* current = m_Head;

    for (int i = 0; i < index; i++)
        current = current->next;

    return current->value;
}

template <class T>
const T& LinkedList<T>::getFirst() const
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    return m_Head->value;
}

template <class T>
const T& LinkedList<T>::getLast() const
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    return m_Tail->value;
}

template <class T>
int LinkedList<T>::find(T item) const
{
    if (m_Head != nullptr)
    {
        int index = 0;
        Node<T>* current = m_Head;
        while (current->next != nullptr)
        {
            if (current->value == item)
                return index;

            current = current->next;
            index += 1;
        }

        if (current->value == item)
            return index;
    }

    return -1;
}

template <class T>
T&& LinkedList<T>::pop(int index)
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T>* current = m_Head;

    for (int i = 0; i < index; i++)
        current = current->next;
    T* result;

    if (index == 0)
    {
        if (m_Size == 1)
            m_Tail = nullptr;
        m_Head = current->next;
        if (m_Head != nullptr)
            m_Head->prev = nullptr;
        result = new T(current->value);
        delete current;
    }
    else if (index == m_Size - 1)
    {
        m_Tail = current->prev;
        m_Tail->next = nullptr;
        result = new T(current->value);
        delete current;
    }
    else {
        current->next->prev = current->prev;
        current->prev->next = current->next;
        result = new T(current->value);
        delete current;
    }
    m_Size -= 1;
    return std::move(*result);
}

template <class T>
LinkedList<T>* LinkedList<T>::getSubList(int startIndex, int endIndex) const
{
    if (m_Size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (startIndex < 0 || endIndex >= m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T>* current = m_Head;
    int count = 0;
    T items[endIndex - startIndex + 1];

    for (int i = 0; i < startIndex; i++)
        current = current->next;

    for (int i = startIndex; i < endIndex + 1; i++)
    {
        count += 1;
        items[i - startIndex] = current->value;
        current = current->next;
    }

    auto* result = new LinkedList(items, count);
    return result;
}

template <class T>
void LinkedList<T>::append(const T& item)
{
    if (m_Size == 0)
    {
        m_Head = new Node<T>;
        m_Head->value = item;
        m_Head->next = nullptr;
        m_Head->prev = nullptr;
        m_Tail = m_Head;
    }
    else
    {
        m_Tail->next = new Node<T>;
        m_Tail->next->value = item;
        m_Tail->next->prev = m_Tail;
        m_Tail->next->next = nullptr;
        m_Tail = m_Tail->next;
    }
    m_Size += 1;
}

template <class T>
void LinkedList<T>::prepend(const T& item)
{
    if (m_Size == 0)
    {
        m_Head = new Node<T>;
        m_Head->value = item;
        m_Head->next = nullptr;
        m_Head->prev = nullptr;
        m_Tail = m_Head;
    }
    else
    {
        m_Head->prev = new Node<T>;
        m_Head->prev->value = item;
        m_Head->prev->next = m_Head;
        m_Head->prev->prev = nullptr;
        m_Head = m_Head->prev;
    }
    m_Size += 1;
}

template <class T>
void LinkedList<T>::insertAt(const T& item, int index)
{
    if (index < 0 || index > m_Size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    if (index == 0)
        this->prepend(item);

    else if (index == m_Size)
        this->append(item);

    else
    {
        Node<T>* current = m_Head;
        for (int i = 0; i < index; i++)
            current = current->next;
        auto* new_Node = new Node<T>;
        new_Node->next = current;
        new_Node->prev = current->prev;
        new_Node->value = item;
        new_Node->prev->next = new_Node;
        new_Node->next->prev = new_Node;
        m_Size += 1;
    }
}

template <class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* other){
    if (other == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    auto* resultList = new LinkedList<T>;
    *resultList = *this;

    for (int i = 0; i < other->getSize(); i++)
        resultList->append((*other)[i]);

    return resultList;
}

template <class T>
void LinkedList<T>::print() const
{
    if (m_Head != nullptr)
    {
        Node<T>* current = m_Head;
        for (int i = 0; i < m_Size; i++)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
    }
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::reversed_print() const
{
    if (m_Tail != nullptr)
    {
        Node<T>* current = m_Tail;
        for (int i = 0; i < m_Size; i++)
        {
            std::cout << current->value << " ";
            current = current->prev;
        }
    }
    std::cout << std::endl;
}

template <class T>
LinkedList<T>* LinkedList<T>::map(T func(const T&)) const
{
    auto* result = new LinkedList<T>;

    Node<T>* current = m_Head;
    for (int i = 0; i < m_Size; i++)
    {
        result->append(func(current->value));
        current = current->next;
    }

    return result;
}

template <class T>
LinkedList<T>* LinkedList<T>::where(bool func(const T&)) const
{
    auto* result = new LinkedList<T>;

    Node<T>* current = m_Head;
    for (int i = 0; i < m_Size; i++)
    {
        if (func(current->value))
            result->append(current->value);
        current = current->next;
    }

    return result;
}

template <class T>
T LinkedList<T>::reduce(T func(const T&, const T&), const T& startValue) const
{
    T result = startValue;

    Node<T>* current = m_Head;
    for (int i = 0; i < m_Size; i++)
    {
        result = func(current->value, result);
        current = current->next;
    }
    return result;
}

#endif