#pragma once
#include <iostream>

template <class T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual const T& getFirst() const = 0;
    virtual const T& getLast() const = 0;
    virtual const T& get(int index) const = 0; // int

    virtual int getLength() const = 0;

    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* concat(const Sequence<T>& secondSequence) const = 0;

    virtual const T& operator [] (int index) const = 0;
};

