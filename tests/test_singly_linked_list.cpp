// Copyright 2026 Danila Puzanov

#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "../lib_singly_linked_list/singly_linked_list.h"
#include "../tests/parameters.h"

#ifdef SINGLY_LINKED_LIST_TESTS

TEST(ClassSinglyLinkedList, DefaultConstructorCreatesEmptyList) {
    SinglyLinkedList<int> l;

    EXPECT_TRUE(l.is_empty());
    EXPECT_EQ(l.size(), 0u);
    EXPECT_EQ(l.find(1), nullptr);
}

TEST(ClassSinglyLinkedList, PopFromEmptyThrows) {
    SinglyLinkedList<int> l;

    EXPECT_THROW(l.pop_front(), std::underflow_error);
    EXPECT_THROW(l.pop_back(), std::underflow_error);
}

TEST(ClassSinglyLinkedList, PushBackKeepsOrder) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.size(), 3u);
    EXPECT_FALSE(l.is_empty());
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, PushFrontReversesOrder) {
    SinglyLinkedList<int> l;

    l.push_front(1);
    l.push_front(2);
    l.push_front(3);

    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 1);
}

TEST(ClassSinglyLinkedList, PushFrontOnEmptyThenPushBack) {
    SinglyLinkedList<int> l;

    l.push_front(1);
    l.push_back(2);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
}

TEST(ClassSinglyLinkedList, PopFrontReturnsElementsAndShrinks) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.size(), 1u);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_TRUE(l.is_empty());
}

TEST(ClassSinglyLinkedList, PopBackReturnsElementsAndShrinks) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.size(), 2u);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ClassSinglyLinkedList, PopBackUpdatesTail) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_back();
    l.push_back(9);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 9);
}

TEST(ClassSinglyLinkedList, ReusableAfterPopFrontMakesItEmpty) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.pop_front();
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, ReusableAfterPopBackMakesItEmpty) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.pop_back();
    l.push_front(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, InsertByIndexIntoEmpty) {
    SinglyLinkedList<int> l;

    auto node = l.insert(5, size_t{ 0 });

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data, 5);
    EXPECT_EQ(l.size(), 1u);
}

TEST(ClassSinglyLinkedList, InsertByIndexAtBeginning) {
    SinglyLinkedList<int> l;

    l.push_back(2);
    l.push_back(3);
    auto node = l.insert(1, size_t{ 0 });

    EXPECT_EQ(node->_data, 1);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, InsertByIndexInMiddle) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    auto node = l.insert(2, 1);

    EXPECT_EQ(node->_data, 2);
    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, InsertByIndexAtEndUpdatesTail) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    auto node = l.insert(3, 2);

    EXPECT_EQ(node->_data, 3);

    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, InsertByIndexOutOfRangeThrows) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_THROW(l.insert(9, 3), std::out_of_range);
    EXPECT_EQ(l.size(), 2u);
}

TEST(ClassSinglyLinkedList, InsertBeforeHeadNode) {
    SinglyLinkedList<int> l;

    l.push_back(2);
    l.push_back(3);
    auto node = l.insert(1, l.find(2));

    EXPECT_EQ(node->_data, 1);
    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, InsertBeforeMiddleNode) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    l.push_back(4);
    auto node = l.insert(2, l.find(3));

    EXPECT_EQ(node->_data, 2);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, InsertBeforeTailNodeKeepsTailValid) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    l.insert(2, l.find(3));
    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, InsertBeforeNullptrThrows) {
    SinglyLinkedList<int> l;

    l.push_back(1);

    EXPECT_THROW(l.insert(2, nullptr), std::invalid_argument);
    EXPECT_EQ(l.size(), 1u);
}

TEST(ClassSinglyLinkedList, InsertBeforeForeignNodeThrows) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int> b;

    b.push_back(7);
    b.push_back(8);

    EXPECT_THROW(a.insert(5, b.find(8)), std::invalid_argument);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(ClassSinglyLinkedList, EraseByIndexFirst) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(size_t{ 0 }), 1);
    EXPECT_EQ(l.size(), 2u);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, EraseByIndexMiddle) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);

    EXPECT_EQ(l.erase(2), 3);
    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, EraseByIndexSecondOfThree) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(1), 2);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, EraseByIndexLastUpdatesTail) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(2), 3);

    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, EraseByIndexOnlyElement) {
    SinglyLinkedList<int> l;

    l.push_back(1);

    EXPECT_EQ(l.erase(size_t{ 0 }), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ClassSinglyLinkedList, EraseByIndexOutOfRangeThrows) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_THROW(l.erase(2), std::out_of_range);
    EXPECT_THROW(l.erase(100), std::out_of_range);
    EXPECT_EQ(l.size(), 2u);
}

TEST(ClassSinglyLinkedList, EraseByIndexFromEmptyThrows) {
    SinglyLinkedList<int> l;

    EXPECT_THROW(l.erase(size_t{ 0 }), std::out_of_range);
}

TEST(ClassSinglyLinkedList, EraseHeadNode) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(l.find(1)), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, EraseTailNodeUpdatesTail) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(l.find(3)), 3);

    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, EraseMiddleNode) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(l.find(2)), 2);
    EXPECT_EQ(l.size(), 2u);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, EraseNullptrNodeThrows) {
    SinglyLinkedList<int> l;

    l.push_back(1);

    EXPECT_THROW(l.erase(l.find(42)), std::invalid_argument);
    EXPECT_EQ(l.size(), 1u);
}

TEST(ClassSinglyLinkedList, EraseForeignNodeThrows) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    SinglyLinkedList<int> b;

    b.push_back(7);
    b.push_back(8);
    b.push_back(9);

    EXPECT_THROW(a.erase(b.find(8)), std::invalid_argument);
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(ClassSinglyLinkedList, FindExistingElement) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto node = l.find(2);

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data, 2);
}

TEST(ClassSinglyLinkedList, FindMissingElementReturnsNullptr) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_EQ(l.find(42), nullptr);
}

TEST(ClassSinglyLinkedList, FindReturnsFirstOfDuplicates) {
    SinglyLinkedList<int> l;

    l.push_back(5);
    l.push_back(1);
    l.push_back(5);

    EXPECT_EQ(l.erase(l.find(5)), 5);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 5);
}

TEST(ClassSinglyLinkedList, FindWorksOnConstList) {
    SinglyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    const SinglyLinkedList<int>& cl = l;

    EXPECT_NE(cl.find(2), nullptr);
}

TEST(ClassSinglyLinkedList, CopyConstructorIsDeep) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    SinglyLinkedList<int> b(a);

    EXPECT_EQ(b.size(), 3u);

    a.pop_front();
    a.push_back(99);

    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
    EXPECT_EQ(b.pop_front(), 3);
    EXPECT_EQ(a.pop_front(), 2);
    EXPECT_EQ(a.pop_front(), 3);
    EXPECT_EQ(a.pop_front(), 99);
}

TEST(ClassSinglyLinkedList, CopyConstructorOfEmptyList) {
    SinglyLinkedList<int> a;
    SinglyLinkedList<int> b(a);

    EXPECT_TRUE(b.is_empty());

    b.push_back(1);

    EXPECT_EQ(b.pop_front(), 1);
}

TEST(ClassSinglyLinkedList, CopyHasWorkingTail) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int> b(a);

    b.push_back(3);

    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.pop_back(), 3);
    EXPECT_EQ(b.pop_back(), 2);
}

TEST(ClassSinglyLinkedList, CopyAssignmentReplacesContent) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    SinglyLinkedList<int> b;

    b.push_back(7);
    b.push_back(8);

    b = a;

    EXPECT_EQ(b.size(), 3u);

    b.push_back(4);

    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
    EXPECT_EQ(b.pop_front(), 3);
    EXPECT_EQ(b.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, CopyAssignmentFromEmpty) {
    SinglyLinkedList<int> a;

    SinglyLinkedList<int> b;
    b.push_back(1);
    b.push_back(2);

    b = a;

    EXPECT_TRUE(b.is_empty());

    b.push_back(5);

    EXPECT_EQ(b.pop_front(), 5);
}

TEST(ClassSinglyLinkedList, CopyAssignmentToEmpty) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int> b;

    b = a;

    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
}

TEST(ClassSinglyLinkedList, SelfCopyAssignmentIsSafe) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int>& ref = a;

    a = ref;

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(a.pop_front(), 1);
    EXPECT_EQ(a.pop_front(), 2);
}

TEST(ClassSinglyLinkedList, MoveConstructorStealsContent) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    SinglyLinkedList<int> b(std::move(a));

    EXPECT_TRUE(a.is_empty());
    EXPECT_EQ(a.size(), 0u);
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
    EXPECT_EQ(b.pop_front(), 3);
}

TEST(ClassSinglyLinkedList, MovedFromListIsUsable) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int> b(std::move(a));

    a.push_back(10);
    a.push_front(9);

    EXPECT_EQ(a.pop_front(), 9);
    EXPECT_EQ(a.pop_front(), 10);
    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
}

TEST(ClassSinglyLinkedList, MoveAssignmentStealsContent) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    SinglyLinkedList<int> b;

    b.push_back(7);
    b = std::move(a);

    EXPECT_TRUE(a.is_empty());
    EXPECT_EQ(b.size(), 3u);

    b.push_back(4);

    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
    EXPECT_EQ(b.pop_front(), 3);
    EXPECT_EQ(b.pop_front(), 4);
}

TEST(ClassSinglyLinkedList, SelfMoveAssignmentIsSafe) {
    SinglyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    SinglyLinkedList<int>& ref = a;

    a = std::move(ref);

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(a.pop_front(), 1);
    EXPECT_EQ(a.pop_front(), 2);
}

TEST(ClassSinglyLinkedList, WorksWithStrings) {
    SinglyLinkedList<std::string> l;

    l.push_back("b");
    l.push_front("a");
    l.push_back("c");

    EXPECT_NE(l.find("b"), nullptr);
    EXPECT_EQ(l.find("z"), nullptr);
    EXPECT_EQ(l.pop_front(), "a");
    EXPECT_EQ(l.pop_front(), "b");
    EXPECT_EQ(l.pop_front(), "c");
}

TEST(ClassSinglyLinkedList, ManyElements) {
    SinglyLinkedList<int> l;

    for (int i = 0; i < 10000; ++i) l.push_back(i);

    EXPECT_EQ(l.size(), 10000u);

    for (int i = 0; i < 5000; ++i) EXPECT_EQ(l.pop_front(), i);

    EXPECT_EQ(l.size(), 5000u);
    EXPECT_EQ(l.pop_back(), 9999);
}

#endif