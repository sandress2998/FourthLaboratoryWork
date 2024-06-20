#pragma once

class TestPriorityQueue {
private:
    int size = 8;
    int maxArray[8] = {7, 6, 5, 4, 3, 2, 1, 0}; // массив, чтобы создавать максимальные кучи

public:
    void testClass();

    void testConstructors();
    void testCopyConstructor();
    void testArrayConstructor();
    void testDefaultConstructor();

    void testAssignmentOperator();

    void testGetSize();
    void testGetSizeInFull();
    void testGetSizeInEmpty();

    void testExtractRoot();
    void testExtractRootInEmpty();
    void testExtractRootInFull();

    void testDeleteRoot();
    void testDeleteRootInFull();
    void testDeleteRootInEmpty();

    void testInsert();
    void testInsertRoot();
    void testInsertNotRoot();

    void testFind();
    void testFindBottomElement();
    void testFindRoot();
    void testFindNotRootNotBottomElement();
    void testFindUnincludedElement();

    void testExtractSubTree();
    void testExtractRootSubTree();
    void testExtractOneNodeSubTree();
    void testExtractNotRootNotOneNodeSubTree();
    void testExtractInvalidRootSubTree();

    void testFindSubTree();
    void testFindSubTreeInSmall();
    void testFindSubTreeInOverflowed();
    void testFindSubTreeInBottom();
    void testFindSubTreeInUsualCase();
    void testFindSubTreeWithInvalidRoot();

    void testMerge();
    void testMergeFullWithFull();
    void testMergeFullWithEmpty();
    void testMergeEmptyWithFull();
    void testMergeEmptyWithEmpty();

    void testGetSubsequence();
    void testInvalidIndicesInGetSubsequence();
    void testValidIndicesInGetSubsequence();

    void testFindSubsequence();
    void testFindSubsequenceInSmall();
    void testFindSubsequenceWithUnincludedElements();
    void testFindSubsequenceInNormal();
};
