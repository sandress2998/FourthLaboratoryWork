#include "Test.h"
#include "TestHeap.h"
#include "TestPriorityQueue.h"

void Test::startTest() {
    testHeap();
    testPriorityQueue();
}

void Test::testHeap() {
    TestHeap testHeap;
    testHeap.testClass();
}

void Test::testPriorityQueue() {
    TestPriorityQueue testPriorityQueue;
    testPriorityQueue.testClass();
}
