#include "PriorityQueue.h"
#include "TestPriorityQueue.h"
#include <stdexcept>
#include <cassert>
#include <cstring>

void TestPriorityQueue::testClass() {
    testConstructors();
    testAssignmentOperator();
    testGetSize();
    testExtractRoot();
    testDeleteRoot();
    testInsert();
    testFind();
    testExtractSubTree();
    testFindSubTree();
    testMerge();
    testGetSubsequence();
    testFindSubsequence();
}

void TestPriorityQueue::testConstructors() {
    testCopyConstructor();
    testArrayConstructor();
    testDefaultConstructor();
}
void TestPriorityQueue::testCopyConstructor() {
    PriorityQueue<int> queue(maxArray, size);
    PriorityQueue<int> queueCopy(queue);

    assert(strcmp(queue.getCompareType(), queueCopy.getCompareType()) == 0);
    assert(queue.getSize() == queueCopy.getSize());
    for (int i = 0; i < queue.getSize(); ++i) {
        assert(queue.get(i) == queueCopy.get(i));
    }
    int elem = 100;
    queue.insert(elem);
    assert(queue.getSize() == queueCopy.getSize() + 1);
}

void TestPriorityQueue::testArrayConstructor() {
    int size = 7;
    int notMaxQueue[size] = {1, 2, 3, 4, 5, 6, 7};
    int expectedResult[7] = {7, 4, 6, 1, 3, 2, 5};
    PriorityQueue<int> queue(notMaxQueue, size);

    assert(strcmp(queue.getCompareType(), "max") == 0);
    assert(queue.getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(queue.get(i) == expectedResult[i]);
    }
}

void TestPriorityQueue::testDefaultConstructor() {
    PriorityQueue<int> queue;
    assert(queue.getSize() == 0);
    assert(strcmp(queue.getCompareType(), "max") == 0);
}


void TestPriorityQueue::testAssignmentOperator() {
    PriorityQueue<int> queue(maxArray, size);
    PriorityQueue<int> queueCopy;

    queueCopy = queue;

    assert(queueCopy.getSize() == size);
    assert(strcmp(queueCopy.getCompareType(), "max") == 0);
    for (int i = 0; i < queue.getSize(); ++i) {
        assert(queueCopy.get(i) == queue.get(i));
    }

    int elem = 100;
    queue.insert(elem);
    assert(queueCopy.getSize() + 1 == queue.getSize());
}

void TestPriorityQueue::testGetSize() {
    testGetSizeInFull();
    testGetSizeInEmpty();
}

void TestPriorityQueue::testGetSizeInFull() {
    PriorityQueue<int> queue(maxArray, size);
    assert(queue.getSize() == size);
}

void TestPriorityQueue::testGetSizeInEmpty() {
    PriorityQueue<int> queue;
    assert(queue.getSize() == 0);
}

void TestPriorityQueue::testExtractRoot() {
    testExtractRootInEmpty();
    testExtractRootInFull();
}

void TestPriorityQueue::testExtractRootInEmpty() {
    try {
        PriorityQueue<int> queue;
        queue.extractRoot();
        assert(false);
    } catch (std::out_of_range& ex) {}
}

void TestPriorityQueue::testExtractRootInFull() {
    PriorityQueue<int> queue(maxArray, size);
    assert(queue.extractRoot() == maxArray[0]);
}

void TestPriorityQueue::testDeleteRoot() {
    testDeleteRootInFull();
    testDeleteRootInEmpty();
}

void TestPriorityQueue::testDeleteRootInFull() {
    PriorityQueue<int> queue(maxArray, size);
    int expectedResult[size - 1] = {6, 4, 5, 0, 3, 2, 1};
    queue.deleteRoot();

    assert(queue.getSize() == size - 1);
    for (int i = 0; i < size - 1; ++i) {
        assert(queue.get(i) == expectedResult[i]);
    }
}

void TestPriorityQueue::testDeleteRootInEmpty() {
    PriorityQueue<int> queue;
    try {
        PriorityQueue<int> queue;
        queue.deleteRoot();
        assert(false);
    } catch (std::out_of_range& ex) {}
}

void TestPriorityQueue::testInsert() {
    testInsertRoot();
    testInsertNotRoot();
}

void TestPriorityQueue::testInsertRoot() {
    PriorityQueue<int> queue(maxArray, size);
    int elem = 8;
    int expectedResult[size + 1] = {8, 7, 5, 6, 3, 2, 1, 0, 4};
    queue.insert(elem);

    assert(queue.getSize() == size + 1);
    for (int i = 0; i < size + 1; ++i) {
        assert(queue.get(i) == expectedResult[i]);
    }
}

void TestPriorityQueue::testInsertNotRoot() {
    PriorityQueue<int> queue(maxArray, size);
    int elem = -1;
    int expectedResult[size + 1] = {7, 6, 5, 4, 3, 2, 1, 0, -1};
    queue.insert(elem);

    assert(queue.getSize() == size + 1);
    for (int i = 0; i < size + 1; ++i) {
        assert(queue.get(i) == expectedResult[i]);
    }
}

void TestPriorityQueue::testFind() {
    testFindBottomElement();
    testFindRoot();
    testFindNotRootNotBottomElement();
    testFindUnincludedElement();
}

void TestPriorityQueue::testFindBottomElement() {
    PriorityQueue<int> queue(maxArray, size);
    assert(queue.find(maxArray[size - 1]) == size - 1);
}

void TestPriorityQueue::testFindRoot() {
    PriorityQueue<int> queue(maxArray, size);
    assert(queue.find(maxArray[0]) == 0);
}

void TestPriorityQueue::testFindNotRootNotBottomElement() {
    PriorityQueue<int> queue(maxArray, size);
    assert(queue.find(maxArray[4]) == 4);
}

void TestPriorityQueue::testFindUnincludedElement() {
    PriorityQueue<int> queue(maxArray, size);
    assert(queue.find(-100) == -1);
}

void TestPriorityQueue::testExtractSubTree() {
    testExtractRootSubTree();
    testExtractOneNodeSubTree();
    testExtractNotRootNotOneNodeSubTree();
    testExtractInvalidRootSubTree();
}

void TestPriorityQueue::testExtractRootSubTree() {
    PriorityQueue<int> queue(maxArray, size);
    PriorityQueue<int>* subTree = queue.extractSubTree(queue.extractRoot());

    assert(subTree->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(subTree->get(i) == queue.get(i));
    }
    delete subTree;
}

void TestPriorityQueue::testExtractOneNodeSubTree() {
    PriorityQueue<int> queue(maxArray, size);
    PriorityQueue<int>* subTree = queue.extractSubTree(maxArray[size - 1]);

    assert(subTree->getSize() == 1);
    assert(subTree->get(0) == queue.get(size - 1));
    delete subTree;
}

void TestPriorityQueue::testExtractNotRootNotOneNodeSubTree() {
    PriorityQueue<int> queue(maxArray, size);
    PriorityQueue<int>* subTree = queue.extractSubTree(6);

    assert(strcmp(subTree->getCompareType(), "max") == 0);
    assert(subTree->getSize() == 4);
    assert(subTree->get(0) == 6);
    assert(subTree->get(1) == 4);
    assert(subTree->get(2) == 3);
    assert(subTree->get(3) == 0);
    delete subTree;
}

void TestPriorityQueue::testExtractInvalidRootSubTree() {
    PriorityQueue<int> queue(maxArray, size);
    try {
        PriorityQueue<int>* subTree = queue.extractSubTree(-1);
        assert(false);
    } catch (std::invalid_argument& ex) {}
}

void TestPriorityQueue::testFindSubTree() {
    testFindSubTreeInSmall();
    testFindSubTreeInOverflowed();
    testFindSubTreeInBottom();
    testFindSubTreeInUsualCase();
    testFindSubTreeWithInvalidRoot();
}

void TestPriorityQueue::testFindSubTreeInSmall() {
    PriorityQueue<int> queue(maxArray, size);
    int subTreeSize = 5;
    int subTree[subTreeSize] = {6, 4, 3, 0, 6};
    assert(queue.findSubTree(subTree, subTreeSize) == 0);
}

void TestPriorityQueue::testFindSubTreeInOverflowed() {
    PriorityQueue<int> queue(maxArray, size);
    int subTreeSize = 3;
    int subTree[subTreeSize] = {6, 4, 3};
    assert(queue.findSubTree(subTree, subTreeSize) == 0);
}

void TestPriorityQueue::testFindSubTreeInBottom() {
    PriorityQueue<int> queue(maxArray, size);
    int subTreeSize = 1;
    int subTree[subTreeSize] = {1};
    assert(queue.findSubTree(subTree, subTreeSize) == 1);
}

void TestPriorityQueue::testFindSubTreeInUsualCase() {
    PriorityQueue<int> queue(maxArray, size);
    int subTreeSize = 4;
    int subTree[subTreeSize] = {6, 4, 3, 0};
    assert(queue.findSubTree(subTree, subTreeSize) == 1);
}

void TestPriorityQueue::testFindSubTreeWithInvalidRoot() {
    PriorityQueue<int> queue(maxArray, size);
    int subTreeSize = 1;
    int subTree[subTreeSize] = {-1};
    assert(queue.findSubTree(subTree, subTreeSize) == 0);
}

void TestPriorityQueue::testMerge() {
    testMergeFullWithFull();
    testMergeFullWithEmpty();
    testMergeEmptyWithFull();
    testMergeEmptyWithEmpty();
}

void TestPriorityQueue::testMergeFullWithFull() {
    PriorityQueue<int> fullQueue1(maxArray, size);
    int secondArraySize = 3;
    int secondArray[secondArraySize] = {8, 9, 10};
    PriorityQueue<int> fullQueue2(secondArray, secondArraySize);

    PriorityQueue<int>* result = fullQueue1.merge(fullQueue2);
    int expectedResult[size + secondArraySize] = {10, 9, 5, 6, 8, 2, 1, 0, 4, 3 ,7};
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == size + secondArraySize);
    for (int i = 0; i < size + secondArraySize; ++i) {
        assert(result->get(i) == expectedResult[i]);
    }
    delete result;
}

void TestPriorityQueue::testMergeFullWithEmpty() {
    PriorityQueue<int> fullQueue(maxArray, size);
    PriorityQueue<int> emptyQueue;

    PriorityQueue<int>* result = fullQueue.merge(emptyQueue);
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(result->get(i) == fullQueue.get(i));
    }
    delete result;
}

void TestPriorityQueue::testMergeEmptyWithFull() {
    PriorityQueue<int> fullQueue(maxArray, size);
    PriorityQueue<int> emptyQueue;

    PriorityQueue<int>* result = emptyQueue.merge(fullQueue);
    assert(strcmp(result->getCompareType(),"max") == 0);
    assert(result->getSize() == size);
    for (int i = 0; i < size; ++i) {
        assert(result->get(i) == fullQueue.get(i));
    }
    delete result;
}

void TestPriorityQueue::testMergeEmptyWithEmpty() {
    PriorityQueue<int> emptyQueue1;
    PriorityQueue<int> emptyQueue2;

    PriorityQueue<int>* result = emptyQueue1.merge(emptyQueue2);
    assert(strcmp(result->getCompareType(), "max") == 0);
    assert(result->getSize() == 0);
    delete result;
}

void TestPriorityQueue::testGetSubsequence() {
    testInvalidIndicesInGetSubsequence();
    testValidIndicesInGetSubsequence();
}

void TestPriorityQueue::testInvalidIndicesInGetSubsequence() {
    PriorityQueue<int> queue(maxArray, size);
    int startIndex = -1;
    int endIndex = 4;

    try {
        int* subsequence1 = queue.getSubsequence(startIndex, endIndex);
        assert(false);
    } catch(std::out_of_range& ex) {}

    startIndex = 1;
    endIndex = size;
    try {
        int* subsequence2 = queue.getSubsequence(startIndex, endIndex);
        assert(false);
    } catch(std::out_of_range& ex) {}
}

void TestPriorityQueue::testValidIndicesInGetSubsequence() {
    PriorityQueue<int> queue(maxArray, size);
    int startIndex = 1;
    int endIndex = 4;
    int* subsequence = queue.getSubsequence(startIndex, endIndex);
    for (int i = 0; i <= endIndex - startIndex; ++i) {
        assert(subsequence[i] == queue.get(startIndex + i));
    }
}

void TestPriorityQueue::testFindSubsequence() {
    testFindSubsequenceInSmall();
    testFindSubsequenceWithUnincludedElements();
    testFindSubsequenceInNormal();
}

void TestPriorityQueue::testFindSubsequenceInSmall() {
    PriorityQueue<int> queue(maxArray, size);
    int subsequenceSize = 6;
    int subsequence[subsequenceSize] = {8, 7, 6, 5, 4, 3};
    bool expectedResult = false;
    bool result = queue.findSubsequence(subsequence, subsequenceSize);
    assert(result == expectedResult);
}

void TestPriorityQueue::testFindSubsequenceWithUnincludedElements() {
    PriorityQueue<int> queue(maxArray, size);
    int subsequenceSize = 4;
    int subsequence[4] = {7, 5, 4, 3};
    bool expectedResult = false;
    bool result = queue.findSubsequence(subsequence, subsequenceSize);
    assert(result == expectedResult);
}

void TestPriorityQueue::testFindSubsequenceInNormal() {
    PriorityQueue<int> queue(maxArray, size);
    int subsequenceSize = 4;
    int subsequence[4] = {6, 5, 4, 3};
    bool expectedResult = true;
    bool result = queue.findSubsequence(subsequence, subsequenceSize);
    assert(result == expectedResult);
}

