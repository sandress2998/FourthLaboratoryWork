#pragma once

#include <stdexcept>
#include "MutableSequence.h"
#include "Sequence.h"
#include "DynamicArray.h"

template <typename T>
class MutableArraySequence: public MutableSequence<T> {
private:
    DynamicArray<T>* array;
public:
    MutableArraySequence(const T* arrayToCopy, int size): array(new DynamicArray<T>(arrayToCopy, size)) {}
    MutableArraySequence(int size): array(new DynamicArray<T>(size)) {}
    MutableArraySequence(): array(new DynamicArray<T>(0)) {}
    MutableArraySequence(const DynamicArray<T>& other): array(new DynamicArray<T>(other)) {}
    MutableArraySequence(const Sequence<T>& other): array(new DynamicArray<T>(other)) {}
    MutableArraySequence(const MutableArraySequence<T>& other): array(new DynamicArray<T>(*(other.array))) {}

    ~MutableArraySequence() override {
        delete array;
    }

    T& operator[](int index) override {
        return (*array)[index];
    }

    const T& operator [] (int index) const override {
        return (*array)[index];
    }

    // Переделано
    MutableArraySequence<T>& operator=(const MutableArraySequence<T>& other) {
       *array = *other.array;
       return *this;
    }

    const T& getFirst() const override {
        return (*array)[0];
    }

    const T& getLast() const override {
        return (*array)[getLength() - 1];
    }

    const T& get(int index) const override {
        return (*array)[index];
    }

    void set(int index, const T& value) override {
        (*array)[index] = value;
    }

    int getLength() const override {
        return array->getSize();
    }

    void append(const T& item) override {
        array->append(item);
    }

    void prepend(const T& item) override {
        array->prepend(item);
    }

    void insertAt(int index, const T& item) override {
        array->insertAt(index, item);
    }

    void popHead() {
        if (array->getSize() == 0) throw std::out_of_range("You can't pop head in empty array.\n");
        array->resize(array->getSize() - 1);
    }

    MutableArraySequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw std::out_of_range("Entered indices are out of range.\n");
        MutableArraySequence<T>* result = new MutableArraySequence<T>(endIndex - startIndex + 1);
        // делаем копирование элементов array
        for (int i = 0; i < result->getLength(); ++i) {
            (*result)[i] = get(i + startIndex);
        }
        return result;
    }

    MutableArraySequence<T>* concat(const Sequence<T>& other) const override {
        MutableArraySequence<T>* result = new MutableArraySequence<T>(other.getLength() + getLength());
        int i = 0;
        int length = getLength();
        for (; i < length; ++i) {
            (*result)[i] = get(i);
        }
        for (; i < length + other.getLength(); ++i) {
            (*result)[i] = other.get(i - length);
        }
        return result;
    }
};
