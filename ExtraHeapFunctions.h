#pragma once
#include "Heap.h"

template <typename T, typename U, typename... Tail>
Heap<U>* map(const Heap<T>& heap, U (*operation) (const T& root, Tail&... tail), Tail&... tail) {
    Heap<T> buf(heap);
    Heap<U>* result = new Heap<U>(heap.getCompareType());
    for (int i = 0; i < heap.getSize(); ++i) {
        result->insert(operation(buf.extractRoot(), tail...));
        buf.deleteRoot();
    }
    return result;
}

template <typename T,  typename... Tail>
Heap<T>* where(const Heap<T>& heap, bool (*operation) (const T& root, Tail&... tail), Tail&... tail) {
    Heap<T> buf(heap);
    Heap<T>* result = new Heap<T>(heap.getCompareType());
    for (int i = 0; i < heap.getSize(); ++i) {
        if (operation(buf.extractRoot(), tail...)) result->insert(buf.extractRoot());
        buf.deleteRoot();
    }
    return result;
}

template <typename T, typename U>
U reduce(const Heap<T>& heap, U (*operation) (const T& root, U& start), U start) { // пишу T start, чтобы при передаче аргумента в reduce start случайно не изменился
    Heap<T> buf(heap);
    for (int i = 0; i < heap.getSize(); ++i) {
        start = operation(buf.extractRoot(), start);
        buf.deleteRoot();
    }
    return start;
}

// возвращает указатель на массив с двумя указателями на кучи
template <typename T,  typename... Tail>
Heap<T>** separate(const Heap<T>& heap, bool (*operation) (const T& root, Tail&... tail), Tail&... tail) {
    Heap<T>** result = new Heap<T>*[2]; // массив указателей на две кучи
    Heap<int> buf(heap); // копируем переданную кучу
    T firstArray[heap.getSize()];
    int firstSize = 0;
    T secondArray[heap.getSize()];
    int secondSize = 0;
    for (int i = 0; i < heap.getSize(); ++i) {
        if (operation(buf.extractRoot(), tail...)) firstArray[firstSize++] = buf.extractRoot();
        else  secondArray[secondSize++] = buf.extractRoot();
        buf.deleteRoot();
    }
    result[0] = new Heap<T>(heap.getCompareType(), firstArray, firstSize);
    result[1] = new Heap<T>(heap.getCompareType(), secondArray, secondSize);
    return result;
}
