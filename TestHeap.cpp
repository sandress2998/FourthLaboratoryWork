#include "TestHeap.h"
#include "Heap.h"
#include "ExtraHeapFunctions.h"
#include <stdexcept>
#include <cassert>
#include <cstring>

void TestHeap::testClass() {
    testConstructors();
    testAssignmentOperator();
    testGetSize();
    testGetCompareType();
    testExtractRoot();
    testDeleteRoot();
    testInsert();
    testFind();
    testExtractSubTree();
    testFindSubTree();
    testMerge();
    testMap();
    testWhere();
    testReduce();
    testSeparate();
}

void TestHeap::testConstructors() {
    testCopyConstructor();
    testArrayConstructorMax();
    testArrayConstructorMin();
    testDefaultConstructorMax();
    testDefaultConstructorMin();
}

void TestHeap::testCopyConstructor() {
    Heap<int> heap("max", maxArray, size);
    Heap<int> heapCopy(heap);

    assert(strcmp(heap.getCompareType(), heapCopy.getCompareType()) == 0);
    assert(heap.getSize() == heapCopy.getSize());
    for (int i = 0; i < heap.getSize(); ++i) {
        assert(heap.get(i) == heapCopy.get(i));
    }
    int elem = 100;
    heap.insert(elem);
    assert(heap.getSize() == heapCopy.getSize() + 1);
}

void TestHeap::testArrayConstructorMax() {
    int size = 7;
    int notMaxHeap[size] = {1, 2, 3, 4, 5, 6, 7};
    int expectedResult[7] = {7, 4, 6, 1, 3, 2, 5};
    Heap<int> heap("max", notMaxHeap, size);

    assert(strcmp(heap.getCompareType(), "max") == 0);
    assert(heap.getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testArrayConstructorMin() {
    int size = 7;
    int notMinHeap[size] = {7, 6, 5, 4, 3, 2, 1};
    int expectedResult[7] = {1, 4, 2, 7, 5, 6, 3};
    Heap<int> heap("min", notMinHeap, size);

    assert(strcmp(heap.getCompareType(), "min") == 0);
    assert(heap.getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testDefaultConstructorMax() {
    Heap<int> heap("max");
    assert(heap.getSize() == 0);
    assert(strcmp(heap.getCompareType(), "max") == 0);
}

void TestHeap::testDefaultConstructorMin() {
    Heap<int> heap("min");
    assert(heap.getSize() == 0);
    assert(strcmp(heap.getCompareType(), "min") == 0);
}

void TestHeap::testAssignmentOperator() {
    Heap<int> heap("max", maxArray, size);
    Heap<int> heapCopy("min");

    heapCopy = heap;

    assert(heapCopy.getSize() == size);
    assert(strcmp(heapCopy.getCompareType(), "max") == 0);
    for (int i = 0; i < heap.getSize(); ++i) {
        assert(heapCopy.get(i) == heap.get(i));
    }

    int elem = 100;
    heap.insert(elem);
    assert(heapCopy.getSize() + 1 == heap.getSize());
}

void TestHeap::testGetSize() {
    testGetSizeInFull();
    testGetSizeInEmpty();
}

void TestHeap::testGetSizeInFull() {
    Heap<int> heap("max", maxArray, size);
    assert(heap.getSize() == size);
}

void TestHeap::testGetSizeInEmpty() {
    Heap<int> heap("max");
    assert(heap.getSize() == 0);
}

void TestHeap::testGetCompareType() {
    testGetMaxCompareType();
    testGetMinCompareType();
    testGetInvalidCompareType();
}

void TestHeap::testGetMaxCompareType() {
    Heap<int> heap("max");
    assert(strcmp(heap.getCompareType(), "max") == 0);
}

void TestHeap::testGetMinCompareType() {
    Heap<int> heap("min");
    assert(strcmp(heap.getCompareType(), "min") == 0);
}

void TestHeap::testGetInvalidCompareType() {
    try {
        Heap<int> heap("someWord");
        assert(false);
    } catch (std::invalid_argument& ex) {}
}

void TestHeap::testExtractRoot() {
    testExtractRootInEmpty();
    testExtractRootInFullMin();
    testExtractRootInFullMax();
}

void TestHeap::testExtractRootInEmpty() {
    try {
        Heap<int> heap("max");
        heap.extractRoot();
        assert(false);
    } catch (std::out_of_range& ex) {}
}

void TestHeap::testExtractRootInFullMin() {
    Heap<int> heap("min", minArray, size);
    assert(heap.extractRoot() == minArray[0]);
}

void TestHeap::testExtractRootInFullMax() {
    Heap<int> heap("max", maxArray, size);
    assert(heap.extractRoot() == maxArray[0]);
}

void TestHeap::testDeleteRoot() {
    testDeleteRootInFullMax();
    testDeleteRootInFullMin();
    testDeleteRootInEmpty();
}

void TestHeap::testDeleteRootInFullMax() {
    Heap<int> heap("max", maxArray, size);
    int expectedResult[size - 1] = {6, 4, 5, 0, 3, 2, 1};
    heap.deleteRoot();

    assert(heap.getSize() == size - 1);
    for (int i = 0; i < size - 1; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testDeleteRootInFullMin() {
    Heap<int> heap("min", minArray, size);
    heap.deleteRoot();
    int expectedResult[size - 1] = {1, 3, 2, 7, 4, 5, 6};

    assert(heap.getSize() == size - 1);
    for (int i = 0; i < size - 1; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}
void TestHeap::testDeleteRootInEmpty() {
    Heap<int> heap("min");
    try {
        Heap<int> heap("min");
        heap.deleteRoot();
        assert(false);
    } catch (std::out_of_range& ex) {}
}

void TestHeap::testInsert() {
    testInsertRootMax();
    testInsertRootMin();
    testInsertNotRootMax();
    testInsertNotRootMin();
}

void TestHeap::testInsertRootMax() {
    Heap<int> heap("max", maxArray, size);
    int elem = 8;
    int expectedResult[size + 1] = {8, 7, 5, 6, 3, 2, 1, 0, 4};
    heap.insert(elem);

    assert(heap.getSize() == size + 1);
    for (int i = 0; i < size + 1; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testInsertRootMin() {
    Heap<int> heap("min", minArray, size);
    int elem = -1;
    int expectedResult[size + 1] = {-1, 0, 2, 1, 4, 5, 6, 7, 3};
    heap.insert(elem);

    assert(heap.getSize() == size + 1);
    for (int i = 0; i < size + 1; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testInsertNotRootMax() {
    Heap<int> heap("max", maxArray, size);
    int elem = -1;
    int expectedResult[size + 1] = {7, 6, 5, 4, 3, 2, 1, 0, -1};
    heap.insert(elem);

    assert(heap.getSize() == size + 1);
    for (int i = 0; i < size + 1; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testInsertNotRootMin() {
    Heap<int> heap("min", minArray, size);
    int elem = 8;
    int expectedResult[size + 1] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    heap.insert(elem);

    assert(heap.getSize() == size + 1);
    for (int i = 0; i < size + 1; ++i) {
        assert(heap.get(i) == expectedResult[i]);
    }
}

void TestHeap::testFind() {
    testFindBottomElement();
    testFindRoot();
    testFindNotRootNotBottomElement();
    testFindUnincludedElement();
}

void TestHeap::testFindBottomElement() {
    Heap<int> heap("max", maxArray, size);
    assert(heap.find(maxArray[size - 1]) == size - 1);
}

void TestHeap::testFindRoot() {
    Heap<int> heap("max", maxArray, size);
    assert(heap.find(maxArray[0]) == 0);
}

void TestHeap::testFindNotRootNotBottomElement() {
    Heap<int> heap("max", maxArray, size);
    assert(heap.find(maxArray[4]) == 4);
}

void TestHeap::testFindUnincludedElement() {
    Heap<int> heap("max", maxArray, size);
    assert(heap.find(-100) == -1);
}

void TestHeap::testExtractSubTree() {
    testExtractRootSubTree();
    testExtractOneNodeSubTree();
    testExtractNotRootNotOneNodeSubTree();
    testExtractInvalidRootSubTree();
}

void TestHeap::testExtractRootSubTree() {
    Heap<int> heap("max", maxArray, size);
    Heap<int>* subTree = heap.extractSubTree(heap.extractRoot());

    assert(subTree->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(subTree->get(i) == heap.get(i));
    }
    delete subTree;
}

void TestHeap::testExtractOneNodeSubTree() {
    Heap<int> heap("max", maxArray, size);
    Heap<int>* subTree = heap.extractSubTree(maxArray[size - 1]);

    assert(subTree->getSize() == 1);
    assert(subTree->get(0) == heap.get(size - 1));
    delete subTree;
}

void TestHeap::testExtractNotRootNotOneNodeSubTree() {
    Heap<int> heap("max", maxArray, size);
    Heap<int>* subTree = heap.extractSubTree(6);

    assert(strcmp(subTree->getCompareType(), "max") == 0);
    assert(subTree->getSize() == 4);
    assert(subTree->get(0) == 6);
    assert(subTree->get(1) == 4);
    assert(subTree->get(2) == 3);
    assert(subTree->get(3) == 0);
    delete subTree;
}

void TestHeap::testExtractInvalidRootSubTree() {
    Heap<int> heap("max", maxArray, size);
    try {
        Heap<int>* subTree = heap.extractSubTree(-1);
        assert(false);
    } catch (std::invalid_argument& ex) {}
}

void TestHeap::testFindSubTree() {
    testFindSubTreeInSmall();
    testFindSubTreeInOverflowed();
    testFindSubTreeInBottom();
    testFindSubTreeInUsualCase();
    testFindSubTreeWithInvalidRoot();
}

void TestHeap::testFindSubTreeInSmall() {
    Heap<int> heap("max", maxArray, size);
    int subTreeSize = 5;
    int subTree[subTreeSize] = {6, 4, 3, 0, 6};
    assert(heap.findSubTree(subTree, subTreeSize) == 0);
}

void TestHeap::testFindSubTreeInOverflowed() {
    Heap<int> heap("max", maxArray, size);
    int subTreeSize = 3;
    int subTree[subTreeSize] = {6, 4, 3};
    assert(heap.findSubTree(subTree, subTreeSize) == 0);
}

void TestHeap::testFindSubTreeInBottom() {
    Heap<int> heap("max", maxArray, size);
    int subTreeSize = 1;
    int subTree[subTreeSize] = {1};
    assert(heap.findSubTree(subTree, subTreeSize) == 1);
}

void TestHeap::testFindSubTreeInUsualCase() {
    Heap<int> heap("max", maxArray, size);
    int subTreeSize = 4;
    int subTree[subTreeSize] = {6, 4, 3, 0};
    assert(heap.findSubTree(subTree, subTreeSize) == 1);
}

void TestHeap::testFindSubTreeWithInvalidRoot() {
    Heap<int> heap("max", maxArray, size);
    int subTreeSize = 1;
    int subTree[subTreeSize] = {-1};
    assert(heap.findSubTree(subTree, subTreeSize) == 0);
}

void TestHeap::testMerge() {
    testMergeFullWithFull();
    testMergeFullWithEmpty();
    testMergeEmptyWithFull();
    testMergeEmptyWithEmpty();
}

void TestHeap::testMergeFullWithFull() {
    Heap<int> fullHeap1("max", maxArray, size);
    int secondArraySize = 3;
    int secondArray[secondArraySize] = {8, 9, 10};
    Heap<int> fullHeap2("min", secondArray, secondArraySize);

    Heap<int>* result = fullHeap1.merge(fullHeap2);
    int expectedResult[size + secondArraySize] = {10, 9, 5, 6, 8, 2, 1, 0, 4, 3 ,7};
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == size + secondArraySize);
    for (int i = 0; i < size + secondArraySize; ++i) {
        assert(result->get(i) == expectedResult[i]);
    }
    delete result;
}

void TestHeap::testMergeFullWithEmpty() {
    Heap<int> fullHeap("max", maxArray, size);
    Heap<int> emptyHeap("min");

    Heap<int>* result = fullHeap.merge(emptyHeap);
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(result->get(i) == fullHeap.get(i));
    }
    delete result;
}

void TestHeap::testMergeEmptyWithFull() {
    Heap<int> fullHeap("max", maxArray, size);
    Heap<int> emptyHeap("max");

    Heap<int>* result = emptyHeap.merge(fullHeap);
    assert(strcmp(result->getCompareType(),"max") == 0);
    assert(result->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(result->get(i) == fullHeap.get(i));
    }
    delete result;
}

void TestHeap::testMergeEmptyWithEmpty() {
    Heap<int> emptyHeap1("max");
    Heap<int> emptyHeap2("min");

    Heap<int>* result = emptyHeap1.merge(emptyHeap2);
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == 0);
    delete result;
}

double mapFunction(const int& elemToChange, int& a, double& b) {
    return elemToChange * a + b;
}

void TestHeap::testMap() {
    Heap<int> heap("max", maxArray, size);
    int a = 3;
    double b = 5.3;
    Heap<double>* result = map(heap, &mapFunction, a, b);
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(result->get(i) == heap.get(i) * a + b);
    }
    delete result;
}

bool whereFunction(const int& elemToCheck, int& a, double& b) {
    return elemToCheck + a > b;
}

void TestHeap::testWhere() {
    Heap<int> heap("max", maxArray, size);
    int a = 3;
    double b = 5.3;
    Heap<int>* result = where(heap, &whereFunction, a, b);
    assert(strcmp(result->getCompareType(), "max") == 0);
    for (int i = 0; i < result->getSize(); ++i) {
        assert((result->get(i) + a > b) == (maxArray[i] * a > b));
    }
    delete result;
}

double reduceFunction(const int& elemToOperation, double& b) {
    return elemToOperation * b - b;
}

void TestHeap::testReduce() {
    Heap<int> heap("max", maxArray, size);
    double b = 5.3;
    double result = reduce(heap, &reduceFunction, b);
    double expectedResult = b;
    for (int i = 0; i < heap.getSize(); ++i) {
        expectedResult = heap.get(i) * expectedResult - expectedResult;
    }
    assert(result == expectedResult);
}

bool separateFunction(const int& elemToCheck, int& a, double& b) {
    return elemToCheck + a - b > 0;
}

void TestHeap::testSeparate() {
    Heap<int> heap("max", maxArray, size);
    int a = 1;
    double b = 5.3;
    Heap<int>** result = separate(heap, &separateFunction, a, b);
    assert(strcmp(result[0]->getCompareType(), "max") == 0);
    assert(strcmp(result[1]->getCompareType(), "max") == 0);
    assert(result[0]->getSize() + result[1]->getSize() == size);
    for (int i = 0; i < size; ++i) {
        if (heap.get(i) + a - b > 0) assert(result[0]->find(heap.get(i)) != -1);
        else assert(result[1]->find(heap.get(i)) != -1);
    }
    delete[] result;
}
