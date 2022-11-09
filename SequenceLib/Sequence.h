#ifndef HPP_SEQUENCE
#define HPP_SEQUENCE

#include <iostream>

// Does not work

/*template <class T>
class SequenceIterator
{
    virtual SequenceIterator& operator++() = 0;
    virtual SequenceIterator&& operator++(int) = 0;
    virtual SequenceIterator& operator--() = 0;
    virtual SequenceIterator&& operator--(int) = 0;
    //virtual SequenceIterator& operator =(const SequenceIterator<T>& other);
    //virtual bool operator ==(const SequenceIterator<T>& other) const = 0;
    //virtual bool operator !=(const SequenceIterator<T>& other) const = 0;
    virtual T& operator*() = 0;

};*/

// Does not work

template <class T> class Sequence;
template <class T> std::ostream& operator<<(std::ostream& out, const Sequence<T>& seq);

template <class T>
class Sequence
{
public:
    virtual const T& getFirst() const = 0;
    virtual const T& getLast() const = 0;
    virtual const T& get(int index)  const= 0;
    virtual int find(const T& item) const = 0; // returns index of the first occurrence; returns -1 if nothing was found
    virtual Sequence<T>* getSubSequence(int startIndex, int endIndex) const = 0;
    virtual int getLength() const = 0;
    virtual ~Sequence() = default;

public:
    virtual T& operator[](int index) = 0;
    virtual Sequence<T>& operator =(const Sequence<T>& other) = 0;
    virtual Sequence<T>& operator =(const std::initializer_list<T>&) = 0;
    virtual bool operator ==(const Sequence<T>& other) const = 0;

public:
    virtual void set(const T& item, int index) = 0;
    virtual void append(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insertAt(const T& item, int index) = 0;
    virtual Sequence<T>* concat(Sequence<T>* list) const = 0;
    virtual T&& pop(int index) = 0;
    virtual void print() const = 0;

public:
    virtual Sequence<T>* map(T func(const T&)) const = 0;
    virtual Sequence<T>* where(bool func(const T&)) const = 0;
    virtual T reduce(T func(const T&, const T&), const T& startValue) const = 0;

public:
    friend std::ostream& operator<< <> (std::ostream& out, const Sequence<T>& seq);

};


#endif