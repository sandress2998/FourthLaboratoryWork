#pragma once
#include "Heap.h"


// отличие от кучи в том, что у приоритетной очереди всегда максимальная куча
template <typename T>
class PriorityQueue: public Heap<T> {
private:
    PriorityQueue(int size): Heap<T>("max", size) {}
public:
    PriorityQueue(const PriorityQueue<T>& other): Heap<T>(other) {}

    PriorityQueue(T* array, int size): Heap<T>("max", array, size) {}

    PriorityQueue(): Heap<T>("max") {}

    PriorityQueue<T>& operator=(const PriorityQueue<T>& other) {
        delete[] this->heap;
        this->size = other.size;
        this->heap = new T[this->size];
        int index = 0;
        while (index < this->size) {
            this->heap[index] = other.heap[index];
            ++index;
        }
        return *this;
    }

    T* getSubsequence(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex >= this->getSize() || endIndex < startIndex) throw std::out_of_range("The entered indices are out of range.\n");
        Heap<T> buf(*this);

        T* result = new T[endIndex - startIndex + 1];
        int index = 0;
        while (index < startIndex) {
            buf.deleteRoot();
            ++index;
        }

        while (index <= endIndex) {
            result[index - startIndex] = buf.extractRoot();
            buf.deleteRoot();
            ++index;
        }
        return result;
    }

    bool findSubsequence(T* array, int size) {
        int startIndex = this->find(array[0]);
        if (startIndex == -1) return false;
        if (this->size - startIndex - size < 0) return false;
        Heap<T> buf(*this);
        for (int index = 0; index < startIndex; ++index) buf.deleteRoot();
        for (int index = startIndex; index < startIndex + size; ++index) {
            if (array[index - startIndex] != buf.extractRoot()) return false;
            buf.deleteRoot();
        }
        return true;
    }

    PriorityQueue<T>* merge(const PriorityQueue<T>& other) {
        PriorityQueue<T>* result = new PriorityQueue<T>(this->size + other.size);
        int i = 0;
        for (; i < this->size; ++i) {
            result->heap[i] = this->heap[i];
        }
        result->size = this->size;
        for (; i < this->size + other.size; ++i) {
            result->heap[i] = other.heap[i - this->size];
            result->pushUp(i);
            ++(result->size);
        }
        return result;
    }

    PriorityQueue<T>* extractSubTree(const T& item) const override {
        int rootIndex = this->find(item);
        if (rootIndex == -1) throw std::invalid_argument("The item wasn't found in heap.\n");

        int subTreeSize = this->getSubTreeSize(rootIndex);

        PriorityQueue<T>* result = new PriorityQueue<T>(subTreeSize);
        result->heap[0] = this->heap[rootIndex];

        this->createSubTree(result, rootIndex);

        return result;
    }
};
