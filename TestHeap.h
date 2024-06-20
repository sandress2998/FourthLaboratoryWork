#pragma once

class TestHeap {
private:
    int size = 8;
    int maxArray[8] = {7, 6, 5, 4, 3, 2, 1, 0}; // массив, чтобы создавать максимальные кучи
    int minArray[8] = {0, 1, 2, 3, 4, 5, 6, 7}; // массив, чтобы создавать минимальные кучи

public:
    void testClass();

    void testConstructors();
    void testCopyConstructor();
    void testArrayConstructorMax();
    void testArrayConstructorMin();
    void testDefaultConstructorMax();
    void testDefaultConstructorMin();

    void testAssignmentOperator();

    void testGetSize();
    void testGetSizeInFull();
    void testGetSizeInEmpty();

    void testGetCompareType();
    void testGetMaxCompareType();
    void testGetMinCompareType();
    void testGetInvalidCompareType();

    void testExtractRoot();
    void testExtractRootInEmpty();
    void testExtractRootInFullMin();
    void testExtractRootInFullMax();


    void testDeleteRoot();
    void testDeleteRootInFullMax();
    void testDeleteRootInFullMin();
    void testDeleteRootInEmpty();

    void testInsert();
    void testInsertRootMax();
    void testInsertRootMin();
    void testInsertNotRootMax();
    void testInsertNotRootMin();

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

    void testExtraFunctions();
    void testMap();
    void testWhere();
    void testReduce();
    void testSeparate();
};
