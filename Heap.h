#pragma once
#include <stdexcept>
#include <cstring>
#include "MutableArraySequence.h"

template <typename T>
bool isGreater(const T& first, const T& second) {
    return first > second;
}

template <typename T>
bool isLess(const T& first, const T& second) {
    return first < second;
}

template <typename T>
class Heap {

protected:
    MutableArraySequence<T>* heap = nullptr;

    // используется в методах для создания массива определенной длины и кучи определенной направленности.
    // protected, потому что используется в PriorityQueue в методе merge
    Heap(bool isMax, int size): heap(MutableArraySequence<T>(size)) {
        if (isMax == true) chooseHeapType("max");
        else chooseHeapType("min");
    }

    // protected, потому что используется в PriorityQueue в методе merge
    void pushUp(int currentIndex) {
        // к примеру, если newElem < topElem && compare = isLess, тогда newElem и topElem меняются местами.
        while ((currentIndex != 0) && compare((*heap)[currentIndex], (*heap)[(currentIndex - 1) / 2])) {
            swap((*heap)[currentIndex], (*heap)[(currentIndex - 1) / 2]);
            currentIndex = (currentIndex - 1) / 2;
        }
    }

    // метод для extractSubTree во избежание копипаста в производном классе PriorityQueue
    void createSubTree(Heap<T>* result, int rootIndex) const {
        int subTreeIndex = 2 * rootIndex + 1;
        int levelCapacity = 2;
        int levelCapacityCurrent = 0;

        int index = 1;
        while (subTreeIndex < heap->getSize()) {
            result->(*heap)[index++] = (*heap)[subTreeIndex];
            ++levelCapacityCurrent;
            if (levelCapacityCurrent == levelCapacity) {
                subTreeIndex = (subTreeIndex - levelCapacity + 1) * 2 + 1;
                levelCapacity *= 2;
                levelCapacityCurrent = 0;
            } else {
                ++subTreeIndex;
            }
        }
    }

    // метод для extractSubTree во избежание копипаста в производном классе PriorityQueue
    int getSubTreeSize(int rootIndex) const {
        int subTreeSize = 1; // размер поддерева
        int subTreeIndex = 2 * rootIndex + 1; // индекс в текущей куче следующего (если он существует) элемента
        int levelCapacity = 2; // вместимость уровня поддерева, где рассматривается следующий элемент
        int levelCapacityCurrent = 0; // текущая заполненность уровня поддерева, где рассматривается следующий элемент

        // узнаем, сколько элементов содержится в поддереве (чтобы установить определенный размер дерева).
        while (subTreeIndex < heap->getSize()) { // проверяем, не вышли ли мы за пределы дерева
            ++subTreeSize;
            ++levelCapacityCurrent;
            if (levelCapacityCurrent == levelCapacity) {
                subTreeIndex = (subTreeIndex - levelCapacity + 1) * 2 + 1;
                levelCapacity *= 2;
                levelCapacityCurrent = 0;
            } else {
                ++subTreeIndex;
            }
        }
        return subTreeSize;
    }
private:

    bool isMax; // если куча максимальная, то isMax == true.

    // функция, которая зависит от типа кучи - минимальная или максимальная
    bool (*compare) (const T& first, const T& second); // isLess -> arg1 < arg2 ; isGreater -> arg1 > arg2.

    int getPriorityHeritantIndex(int index, MutableArraySequence<T>* heap) const { // функция для нахождения максимального/минимального ближайшего потомка у узла(maxHeap -> максимального, minHeap -> минимального)
        if (index + 1 >= heap->getSize()) return index; // в этом случае потомок у узла единственный
        return compare((*heap)[index], (*heap)[index + 1]) ? index : index + 1;
    }

    void swap(T& first, T& second) {
        T buf = first;
        first = second;
        second = buf;
    }

    void pushDown() {
        int currentIndex = 0;
        int priorityIndex = getPriorityHeritantIndex(1, heap);
        while ((currentIndex * 2 + 1 < heap->getSize()) && compare((*heap)[priorityIndex], (*heap)[currentIndex])) {
            swap((*heap)[currentIndex], (*heap)[priorityIndex]);
            currentIndex = priorityIndex;
            priorityIndex = getPriorityHeritantIndex(2 * currentIndex + 1, heap);
        }
    }

    // выбираем, какую кучу реализовывать - максимальную или минимальную.
    void chooseHeapType(char* compareType) {
        if (strcmp(compareType, "max") == 0) {
            isMax = true;
            compare = isGreater;
        } else if (strcmp(compareType, "min") == 0) {
            isMax = false;
            compare = isLess;
        } else throw std::invalid_argument("You entered invalid compare-word.\n");
    }

public:

    Heap(const Heap<T>& other): heap(new MutableArraySequence((*other.heap)) {
        compare = other.compare;
        for (int i = 0; i < other->getSize(); ++i) {
            (*heap)[i] = (*other.heap)[i];
        }
    }

    Heap(char* compareType, T* array, int size): heap(new MutableArraySequence(array, size) {
        chooseHeapType(compareType);
        for (int i = 0; i < size; ++i) {
            pushUp(i);
        }
    }

    Heap(char* compare) {
        chooseHeapType(compare);
    }

    virtual ~Heap() { // в нашем случае можно было сделать и не виртуальный конструктор, т.к. в PriorityQueue поля не добавляются, но пусть будет.
        delete heap;
    }

    Heap<T>& operator=(const Heap<T>& other) {
        delete heap;
        heap = new MutableArraySequence<T>(*other.heap);
        chooseHeapType(other.getCompareType());
        int index = 0;
        while (index < heap->getSize()) {
            (*heap)[index] = (*other.heap)[index];
            ++index;
        }
        return *this;
    }

    int getSize() const {
        return heap->getSize();
    }

    char* getCompareType() const {
        if (isMax) {
            return "max";
        }
        return "min";
    }

    T& extractRoot() {
        if (heap->getSize() == 0) throw std::out_of_range("The heap is empty");
        return (*heap)[0];
    }

    void deleteRoot() {
        if (heap->getSize() == 0) throw std::out_of_range("You tried to decrease size of empty heap.\n");
        (*heap)[0] = (*heap)[heap->getSize() - 1];
        heap->popHead(heap->getSize() - 1);
        pushDown();
    }

    void insert(const T& item) {
        heap->append(item);
        pushUp(heap->getSize() - 1);
    }

    // возвращает индекс элемента в куче. Если такового не находится, возвращает -1
    int find(const T& item) const {
        for (int i = 0; i < heap->getSize(); ++i) {
            if ((*heap)[i] == item) return i;
        }
        return -1;
    }

    // проверяет, есть ли поддерево в дереве
    // немного отличается от getSubTreeSize, поэтому не копипастить сложно.
    bool findSubTree(T* subTree, int subTreeSize) const {
        int rootIndex = find(subTree[0]); // т.е. наличие корневого элемента поддерева проверять уже не надо.
        if (rootIndex == -1) return false;

        int subTreeIndex = 2 * rootIndex + 1; // индекс в текущей куче следующего, быть может, элемента
        int levelCapacity = 2; // вместимость уровня поддерева, где рассматривается следующий элемент
        int levelCapacityCurrent = 0; // текущая заполненность уровня поддерева, где рассматривается следующий элемент

        int index = 1;
        while (subTreeIndex < heap->getSize() && index < subTreeSize) {
            if (subTree[index++] != (*heap)[subTreeIndex]) return false;
            ++levelCapacityCurrent;
            if (levelCapacityCurrent == levelCapacity) {
                subTreeIndex = (subTreeIndex - levelCapacity + 1) * 2 + 1;
                levelCapacity *= 2; // по заполнении последнего узла на уровне, переходим на следующий уровень и увеличиваем емкость в 2 раза
                levelCapacityCurrent = 0;
            } else {
                ++subTreeIndex;
            }
        }

        if (subTreeIndex < heap->getSize()) return false; // случай, когда поддерево не содержит нижние элементы дерева
        if (index < subTreeSize) return false; // случай, когда поддерево имеет элементы, которые не имеет дерево.
        return true;
    }

    virtual Heap<T>* extractSubTree(const T& item) const {
        int rootIndex = find(item);
        if (rootIndex == -1) throw std::invalid_argument("The item wasn't found in heap.\n");

        int subTreeSize = getSubTreeSize(rootIndex);

        Heap<T>* result = new Heap<T>(isMax, subTreeSize);
        (*result->heap)[0] = (*heap)[rootIndex];

        createSubTree(result, rootIndex);
        return result;
    }

    Heap<T>* merge(const Heap<T>& other) {
        // кучи сливаются даже тогда, когда они макс/мин или мин/макс. Тип кучи = тип объекта
        Heap<T>* result = new Heap<T>(isMax, heap->getSize() + other.getSize());
        int i = 0;
        for (; i < heap->getSize(); ++i) {
            (*result->heap)[i] = (*heap)[i];
        }
        for (; i < heap->getSize() + other.getSize(); ++i) {
            (*result->heap)[i] = (*other.heap)[i - heap->getSize()];
            result->pushUp(i);
        }
        return result;
    }

    const T& get(int index) const {
        return (*heap)[index];
    }
};
