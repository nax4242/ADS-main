// Copyright 2026 Danila Puzanov

#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "../lib_doubly_linked_list/doubly_linked_list.h"
#include "../tests/parameters.h"

#ifdef DOUBLY_LINKED_LIST_TESTS

TEST(ClassDoublyLinkedList, DefaultConstructorCreatesEmptyList) {
    DoublyLinkedList<int> l;

    EXPECT_TRUE(l.is_empty());
    EXPECT_EQ(l.size(), 0u);
    EXPECT_EQ(l.find(1), nullptr);
}

TEST(ClassDoublyLinkedList, PopFromEmptyThrows) {
    DoublyLinkedList<int> l;

    EXPECT_THROW(l.pop_front(), std::underflow_error);
    EXPECT_THROW(l.pop_back(), std::underflow_error);
}

TEST(ClassDoublyLinkedList, PushBackKeepsOrder) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.size(), 3u);
    EXPECT_FALSE(l.is_empty());
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, PushBackKeepsOrderFromTail) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, PushFrontReversesOrder) {
    DoublyLinkedList<int> l;

    l.push_front(1);
    l.push_front(2);
    l.push_front(3);

    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 1);
}

TEST(ClassDoublyLinkedList, PushFrontSetsPrevLinks) {
    DoublyLinkedList<int> l;

    l.push_front(1);
    l.push_front(2);
    l.push_front(3);

    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 3);
}

TEST(ClassDoublyLinkedList, PushFrontOnEmptyThenPushBack) {
    DoublyLinkedList<int> l;

    l.push_front(1);
    l.push_back(2);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
}

TEST(ClassDoublyLinkedList, PopFrontReturnsElementsAndShrinks) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.size(), 1u);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_TRUE(l.is_empty());
}

TEST(ClassDoublyLinkedList, PopFrontClearsPrevOfNewHead) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_front();

    auto node = l.find(2);

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_prev, nullptr);
}

TEST(ClassDoublyLinkedList, PopBackReturnsElementsAndShrinks) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.size(), 2u);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ClassDoublyLinkedList, PopBackClearsNextOfNewTail) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_back();

    auto node = l.find(2);

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_next, nullptr);
}

TEST(ClassDoublyLinkedList, PopBackUpdatesTail) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_back();
    l.push_back(9);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 9);
}

TEST(ClassDoublyLinkedList, PopOnlyElementFrontEmptiesList) {
    DoublyLinkedList<int> l;

    l.push_back(1);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_TRUE(l.is_empty());
    EXPECT_THROW(l.pop_back(), std::underflow_error);
}

TEST(ClassDoublyLinkedList, PopOnlyElementBackEmptiesList) {
    DoublyLinkedList<int> l;

    l.push_back(1);

    EXPECT_EQ(l.pop_back(), 1);
    EXPECT_TRUE(l.is_empty());
    EXPECT_THROW(l.pop_front(), std::underflow_error);
}

TEST(ClassDoublyLinkedList, ReusableAfterPopFrontMakesItEmpty) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.pop_front();
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, ReusableAfterPopBackMakesItEmpty) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.pop_back();
    l.push_front(2);
    l.push_back(3);

    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, InsertByIndexIntoEmpty) {
    DoublyLinkedList<int> l;

    auto node = l.insert(5, size_t{ 0 });

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data, 5);
    EXPECT_EQ(node->_prev, nullptr);
    EXPECT_EQ(node->_next, nullptr);
    EXPECT_EQ(l.size(), 1u);
}

TEST(ClassDoublyLinkedList, InsertByIndexAtBeginning) {
    DoublyLinkedList<int> l;

    l.push_back(2);
    l.push_back(3);
    auto node = l.insert(1, size_t{ 0 });

    EXPECT_EQ(node->_data, 1);
    EXPECT_EQ(node->_prev, nullptr);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, InsertByIndexInMiddle) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    auto node = l.insert(2, 1);

    EXPECT_EQ(node->_data, 2);
    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, InsertByIndexInMiddleSetsLinks) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    auto node = l.insert(2, 1);

    ASSERT_NE(node->_prev, nullptr);
    ASSERT_NE(node->_next, nullptr);
    EXPECT_EQ(node->_prev->_data, 1);
    EXPECT_EQ(node->_next->_data, 3);
    EXPECT_EQ(node->_prev->_next, node);
    EXPECT_EQ(node->_next->_prev, node);
}

TEST(ClassDoublyLinkedList, InsertByIndexInMiddleKeepsBackwardOrder) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(4);
    l.insert(3, 2);

    EXPECT_EQ(l.pop_back(), 4);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, InsertByIndexAtEndUpdatesTail) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    auto node = l.insert(3, 2);

    EXPECT_EQ(node->_data, 3);
    EXPECT_EQ(node->_prev->_data, 2);

    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassDoublyLinkedList, InsertByIndexOutOfRangeThrows) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_THROW(l.insert(9, 3), std::out_of_range);
    EXPECT_EQ(l.size(), 2u);
}

TEST(ClassDoublyLinkedList, InsertBeforeHeadNode) {
    DoublyLinkedList<int> l;

    l.push_back(2);
    l.push_back(3);
    auto node = l.insert(1, l.find(2));

    EXPECT_EQ(node->_data, 1);
    EXPECT_EQ(node->_prev, nullptr);
    EXPECT_EQ(l.size(), 3u);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, InsertBeforeHeadNodeSetsPrevOfOldHead) {
    DoublyLinkedList<int> l;

    l.push_back(2);
    l.push_back(3);
    l.insert(1, l.find(2));

    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, InsertBeforeMiddleNode) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    l.push_back(4);
    auto node = l.insert(2, l.find(3));

    EXPECT_EQ(node->_data, 2);
    EXPECT_EQ(node->_prev->_data, 1);
    EXPECT_EQ(node->_next->_data, 3);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassDoublyLinkedList, InsertBeforeTailNodeKeepsTailValid) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(3);
    l.insert(2, l.find(3));
    l.push_back(4);

    EXPECT_EQ(l.pop_back(), 4);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, InsertBeforeNullptrThrows) {
    DoublyLinkedList<int> l;

    l.push_back(1);

    EXPECT_THROW(l.insert(2, nullptr), std::invalid_argument);
    EXPECT_EQ(l.size(), 1u);
}

TEST(ClassDoublyLinkedList, InsertBeforeForeignNodeThrows) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    DoublyLinkedList<int> b;

    b.push_back(7);
    b.push_back(8);

    EXPECT_THROW(a.insert(5, b.find(8)), std::invalid_argument);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 2u);
}

TEST(ClassDoublyLinkedList, EraseByIndexFirst) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(size_t{ 0 }), 1);
    EXPECT_EQ(l.size(), 2u);
    EXPECT_EQ(l.find(2)->_prev, nullptr);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, EraseByIndexMiddle) {
    DoublyLinkedList<int> l;

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

TEST(ClassDoublyLinkedList, EraseByIndexMiddleKeepsBackwardLinks) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.erase(2);

    EXPECT_EQ(l.find(4)->_prev->_data, 2);
    EXPECT_EQ(l.pop_back(), 4);
    EXPECT_EQ(l.pop_back(), 2);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, EraseByIndexSecondOfThree) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(1), 2);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, EraseByIndexLastUpdatesTail) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(2), 3);

    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassDoublyLinkedList, EraseByIndexOnlyElement) {
    DoublyLinkedList<int> l;

    l.push_back(1);

    EXPECT_EQ(l.erase(size_t{ 0 }), 1);
    EXPECT_TRUE(l.is_empty());
}

TEST(ClassDoublyLinkedList, EraseByIndexOutOfRangeThrows) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_THROW(l.erase(2), std::out_of_range);
    EXPECT_THROW(l.erase(100), std::out_of_range);
    EXPECT_EQ(l.size(), 2u);
}

TEST(ClassDoublyLinkedList, EraseByIndexFromEmptyThrows) {
    DoublyLinkedList<int> l;

    EXPECT_THROW(l.erase(size_t{ 0 }), std::out_of_range);
}

TEST(ClassDoublyLinkedList, EraseHeadNode) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(l.find(1)), 1);
    EXPECT_EQ(l.find(2)->_prev, nullptr);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassDoublyLinkedList, EraseTailNodeUpdatesTail) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(l.find(3)), 3);
    EXPECT_EQ(l.find(2)->_next, nullptr);

    l.push_back(4);

    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 2);
    EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassDoublyLinkedList, EraseMiddleNode) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_EQ(l.erase(l.find(2)), 2);
    EXPECT_EQ(l.size(), 2u);
    EXPECT_EQ(l.find(3)->_prev->_data, 1);
    EXPECT_EQ(l.find(1)->_next->_data, 3);
    EXPECT_EQ(l.pop_back(), 3);
    EXPECT_EQ(l.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, EraseNullptrNodeThrows) {
    DoublyLinkedList<int> l;

    l.push_back(1);

    EXPECT_THROW(l.erase(l.find(42)), std::invalid_argument);
    EXPECT_EQ(l.size(), 1u);
}

TEST(ClassDoublyLinkedList, EraseForeignNodeThrows) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DoublyLinkedList<int> b;

    b.push_back(7);
    b.push_back(8);
    b.push_back(9);

    EXPECT_THROW(a.erase(b.find(8)), std::invalid_argument);
    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 3u);
}

TEST(ClassDoublyLinkedList, FindExistingElement) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto node = l.find(2);

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->_data, 2);
    EXPECT_EQ(node->_prev->_data, 1);
    EXPECT_EQ(node->_next->_data, 3);
}

TEST(ClassDoublyLinkedList, FindMissingElementReturnsNullptr) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_EQ(l.find(42), nullptr);
}

TEST(ClassDoublyLinkedList, FindReturnsFirstOfDuplicates) {
    DoublyLinkedList<int> l;

    l.push_back(5);
    l.push_back(1);
    l.push_back(5);

    EXPECT_EQ(l.erase(l.find(5)), 5);
    EXPECT_EQ(l.pop_front(), 1);
    EXPECT_EQ(l.pop_front(), 5);
}

TEST(ClassDoublyLinkedList, FindWorksOnConstList) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    const DoublyLinkedList<int>& cl = l;

    EXPECT_NE(cl.find(2), nullptr);
}

TEST(ClassDoublyLinkedList, CopyConstructorIsDeep) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DoublyLinkedList<int> b(a);

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

TEST(ClassDoublyLinkedList, CopyConstructorSetsPrevLinks) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DoublyLinkedList<int> b(a);

    EXPECT_EQ(b.pop_back(), 3);
    EXPECT_EQ(b.pop_back(), 2);
    EXPECT_EQ(b.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, CopyConstructorOfEmptyList) {
    DoublyLinkedList<int> a;
    DoublyLinkedList<int> b(a);

    EXPECT_TRUE(b.is_empty());

    b.push_back(1);

    EXPECT_EQ(b.pop_front(), 1);
}

TEST(ClassDoublyLinkedList, CopyHasWorkingTail) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    DoublyLinkedList<int> b(a);

    b.push_back(3);

    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.pop_back(), 3);
    EXPECT_EQ(b.pop_back(), 2);
}

TEST(ClassDoublyLinkedList, CopyAssignmentReplacesContent) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DoublyLinkedList<int> b;

    b.push_back(7);
    b.push_back(8);

    b = a;

    EXPECT_EQ(b.size(), 3u);

    b.push_back(4);

    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.pop_back(), 4);
    EXPECT_EQ(b.pop_back(), 3);
    EXPECT_EQ(b.pop_back(), 2);
    EXPECT_EQ(b.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, CopyAssignmentFromEmpty) {
    DoublyLinkedList<int> a;

    DoublyLinkedList<int> b;
    b.push_back(1);
    b.push_back(2);

    b = a;

    EXPECT_TRUE(b.is_empty());

    b.push_back(5);

    EXPECT_EQ(b.pop_front(), 5);
}

TEST(ClassDoublyLinkedList, CopyAssignmentToEmpty) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    DoublyLinkedList<int> b;

    b = a;

    EXPECT_EQ(b.pop_back(), 2);
    EXPECT_EQ(b.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, SelfCopyAssignmentIsSafe) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    DoublyLinkedList<int>& ref = a;

    a = ref;

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(a.pop_front(), 1);
    EXPECT_EQ(a.pop_front(), 2);
}

TEST(ClassDoublyLinkedList, MoveConstructorStealsContent) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DoublyLinkedList<int> b(std::move(a));

    EXPECT_TRUE(a.is_empty());
    EXPECT_EQ(a.size(), 0u);
    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b.pop_back(), 3);
    EXPECT_EQ(b.pop_back(), 2);
    EXPECT_EQ(b.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, MovedFromListIsUsable) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    DoublyLinkedList<int> b(std::move(a));

    a.push_back(10);
    a.push_front(9);

    EXPECT_EQ(a.pop_back(), 10);
    EXPECT_EQ(a.pop_back(), 9);
    EXPECT_EQ(b.pop_front(), 1);
    EXPECT_EQ(b.pop_front(), 2);
}

TEST(ClassDoublyLinkedList, MoveAssignmentStealsContent) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DoublyLinkedList<int> b;

    b.push_back(7);
    b = std::move(a);

    EXPECT_TRUE(a.is_empty());
    EXPECT_EQ(b.size(), 3u);

    b.push_back(4);

    EXPECT_EQ(b.pop_back(), 4);
    EXPECT_EQ(b.pop_back(), 3);
    EXPECT_EQ(b.pop_back(), 2);
    EXPECT_EQ(b.pop_back(), 1);
}

TEST(ClassDoublyLinkedList, SelfMoveAssignmentIsSafe) {
    DoublyLinkedList<int> a;

    a.push_back(1);
    a.push_back(2);

    DoublyLinkedList<int>& ref = a;

    a = std::move(ref);

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(a.pop_front(), 1);
    EXPECT_EQ(a.pop_front(), 2);
}

TEST(ClassDoublyLinkedList, WorksWithStrings) {
    DoublyLinkedList<std::string> l;

    l.push_back("b");
    l.push_front("a");
    l.push_back("c");

    EXPECT_NE(l.find("b"), nullptr);
    EXPECT_EQ(l.find("z"), nullptr);
    EXPECT_EQ(l.pop_back(), "c");
    EXPECT_EQ(l.pop_front(), "a");
    EXPECT_EQ(l.pop_front(), "b");
}

TEST(ClassDoublyLinkedList, ManyElements) {
    DoublyLinkedList<int> l;

    for (int i = 0; i < 10000; ++i) l.push_back(i);

    EXPECT_EQ(l.size(), 10000u);

    for (int i = 0; i < 5000; ++i) EXPECT_EQ(l.pop_front(), i);

    EXPECT_EQ(l.size(), 5000u);
    EXPECT_EQ(l.pop_back(), 9999);
}

#endif