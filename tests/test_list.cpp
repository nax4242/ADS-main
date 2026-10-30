#include <gtest/gtest.h>
#include "list.h"
#include "parameters.h"

#ifdef LIST_TESTS

TEST(ClassList, DefaultConstructorCreatesEmptyList) {
	List<int> l;

	EXPECT_TRUE(l.is_empty());
	EXPECT_EQ(l.size(), 0u);
	EXPECT_EQ(l.find(1), nullptr);
}

TEST(ClassList, PopFromEmptyThrows) {
	List<int> l;

	EXPECT_THROW(l.pop_front(), std::underflow_error);
	EXPECT_THROW(l.pop_back(), std::underflow_error);
}

TEST(ClassList, PushBackKeepsOrder) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.size(), 3u);
	EXPECT_FALSE(l.is_empty());
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, PushFrontReversesOrder) {
	List<int> l;

	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	EXPECT_EQ(l.size(), 3u);
	EXPECT_EQ(l.pop_front(), 3);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 1);
}

TEST(ClassList, PushFrontOnEmptyThenPushBack) {
	List<int> l;

	l.push_front(1);
	l.push_back(2);

	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
}

TEST(ClassList, PopFrontReturnsElementsAndShrinks) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);

	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.size(), 1u);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_TRUE(l.is_empty());
}

TEST(ClassList, PopBackReturnsElementsAndShrinks) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.pop_back(), 3);
	EXPECT_EQ(l.size(), 2u);
	EXPECT_EQ(l.pop_back(), 2);
	EXPECT_EQ(l.pop_back(), 1);
	EXPECT_TRUE(l.is_empty());
}

TEST(ClassList, PopBackUpdatesTail) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.pop_back();
	l.push_back(9);

	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 9);
}

TEST(ClassList, ReusableAfterPopFrontMakesItEmpty) {
	List<int> l;

	l.push_back(1);
	l.pop_front();
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, ReusableAfterPopBackMakesItEmpty) {
	List<int> l;

	l.push_back(1);
	l.pop_back();
	l.push_front(2);
	l.push_back(3);

	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, InsertByIndexIntoEmpty) {
	List<int> l;

	auto node = l.insert(5, size_t{ 0 });

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->_data, 5);
	EXPECT_EQ(l.size(), 1u);
}

TEST(ClassList, InsertByIndexAtBeginning) {
	List<int> l;

	l.push_back(2);
	l.push_back(3);
	auto node = l.insert(1, size_t{ 0 });

	EXPECT_EQ(node->_data, 1);
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, InsertByIndexInMiddle) {
	List<int> l;

	l.push_back(1);
	l.push_back(3);
	auto node = l.insert(2, 1);

	EXPECT_EQ(node->_data, 2);
	EXPECT_EQ(l.size(), 3u);
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, InsertByIndexAtEndUpdatesTail) {
	List<int> l;

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

TEST(ClassList, InsertByIndexOutOfRangeThrows) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);

	EXPECT_THROW(l.insert(9, 3), std::out_of_range);
	EXPECT_EQ(l.size(), 2u);
}

TEST(ClassList, InsertBeforeHeadNode) {
	List<int> l;

	l.push_back(2);
	l.push_back(3);
	auto node = l.insert(1, l.find(2));

	EXPECT_EQ(node->_data, 1);
	EXPECT_EQ(l.size(), 3u);
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, InsertBeforeMiddleNode) {
	List<int> l;

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

TEST(ClassList, InsertBeforeTailNodeKeepsTailValid) {
	List<int> l;

	l.push_back(1);
	l.push_back(3);
	l.insert(2, l.find(3));
	l.push_back(4);

	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
	EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassList, InsertBeforeNullptrThrows) {
	List<int> l;

	l.push_back(1);

	EXPECT_THROW(l.insert(2, nullptr), std::invalid_argument);
	EXPECT_EQ(l.size(), 1u);
}

TEST(ClassList, InsertBeforeForeignNodeThrows) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);

	List<int> b;

	b.push_back(7);
	b.push_back(8);

	EXPECT_THROW(a.insert(5, b.find(8)), std::invalid_argument);
	EXPECT_EQ(a.size(), 2u);
	EXPECT_EQ(b.size(), 2u);
}

TEST(ClassList, EraseByIndexFirst) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.erase(size_t{ 0 }), 1);
	EXPECT_EQ(l.size(), 2u);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, EraseByIndexMiddle) {
	List<int> l;

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

TEST(ClassList, EraseByIndexSecondOfThree) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.erase(1), 2);
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, EraseByIndexLastUpdatesTail) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.erase(2), 3);

	l.push_back(4);

	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassList, EraseByIndexOnlyElement) {
	List<int> l;

	l.push_back(1);

	EXPECT_EQ(l.erase(size_t{ 0 }), 1);
	EXPECT_TRUE(l.is_empty());
}

TEST(ClassList, EraseByIndexOutOfRangeThrows) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);

	EXPECT_THROW(l.erase(2), std::out_of_range);
	EXPECT_THROW(l.erase(100), std::out_of_range);
	EXPECT_EQ(l.size(), 2u);
}

TEST(ClassList, EraseByIndexFromEmptyThrows) {
	List<int> l;

	EXPECT_THROW(l.erase(size_t{ 0 }), std::out_of_range);
}

TEST(ClassList, EraseHeadNode) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.erase(l.find(1)), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, EraseTailNodeUpdatesTail) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.erase(l.find(3)), 3);

	l.push_back(4);

	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 2);
	EXPECT_EQ(l.pop_front(), 4);
}

TEST(ClassList, EraseMiddleNode) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	EXPECT_EQ(l.erase(l.find(2)), 2);
	EXPECT_EQ(l.size(), 2u);
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 3);
}

TEST(ClassList, EraseNullptrNodeThrows) {
	List<int> l;

	l.push_back(1);

	EXPECT_THROW(l.erase(l.find(42)), std::invalid_argument);
	EXPECT_EQ(l.size(), 1u);
}

TEST(ClassList, EraseForeignNodeThrows) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	List<int> b;

	b.push_back(7);
	b.push_back(8);
	b.push_back(9);

	EXPECT_THROW(a.erase(b.find(8)), std::invalid_argument);
	EXPECT_EQ(a.size(), 3u);
	EXPECT_EQ(b.size(), 3u);
}

TEST(ClassList, FindExistingElement) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	auto node = l.find(2);

	ASSERT_NE(node, nullptr);
	EXPECT_EQ(node->_data, 2);
}

TEST(ClassList, FindMissingElementReturnsNullptr) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);

	EXPECT_EQ(l.find(42), nullptr);
}

TEST(ClassList, FindReturnsFirstOfDuplicates) {
	List<int> l;

	l.push_back(5);
	l.push_back(1);
	l.push_back(5);

	EXPECT_EQ(l.erase(l.find(5)), 5);
	EXPECT_EQ(l.pop_front(), 1);
	EXPECT_EQ(l.pop_front(), 5);
}

TEST(ClassList, FindWorksOnConstList) {
	List<int> l;

	l.push_back(1);
	l.push_back(2);
	const List<int>& cl = l;

	EXPECT_NE(cl.find(2), nullptr);
}

TEST(ClassList, CopyConstructorIsDeep) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	List<int> b(a);

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

TEST(ClassList, CopyConstructorOfEmptyList) {
	List<int> a;
	List<int> b(a);

	EXPECT_TRUE(b.is_empty());

	b.push_back(1);

	EXPECT_EQ(b.pop_front(), 1);
}

TEST(ClassList, CopyHasWorkingTail) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);

	List<int> b(a);

	b.push_back(3);

	EXPECT_EQ(b.size(), 3u);
	EXPECT_EQ(a.size(), 2u);
	EXPECT_EQ(b.pop_back(), 3);
	EXPECT_EQ(b.pop_back(), 2);
}

TEST(ClassList, CopyAssignmentReplacesContent) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	List<int> b;

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

TEST(ClassList, CopyAssignmentFromEmpty) {
	List<int> a;

	List<int> b;
	b.push_back(1);
	b.push_back(2);

	b = a;

	EXPECT_TRUE(b.is_empty());

	b.push_back(5);

	EXPECT_EQ(b.pop_front(), 5);
}

TEST(ClassList, CopyAssignmentToEmpty) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);

	List<int> b;

	b = a;

	EXPECT_EQ(b.pop_front(), 1);
	EXPECT_EQ(b.pop_front(), 2);
}

TEST(ClassList, SelfCopyAssignmentIsSafe) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);

	List<int>& ref = a;

	a = ref;

	EXPECT_EQ(a.size(), 2u);
	EXPECT_EQ(a.pop_front(), 1);
	EXPECT_EQ(a.pop_front(), 2);
}

TEST(ClassList, MoveConstructorStealsContent) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	List<int> b(std::move(a));

	EXPECT_TRUE(a.is_empty());
	EXPECT_EQ(a.size(), 0u);
	EXPECT_EQ(b.size(), 3u);
	EXPECT_EQ(b.pop_front(), 1);
	EXPECT_EQ(b.pop_front(), 2);
	EXPECT_EQ(b.pop_front(), 3);
}

TEST(ClassList, MovedFromListIsUsable) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);

	List<int> b(std::move(a));

	a.push_back(10);
	a.push_front(9);

	EXPECT_EQ(a.pop_front(), 9);
	EXPECT_EQ(a.pop_front(), 10);
	EXPECT_EQ(b.pop_front(), 1);
	EXPECT_EQ(b.pop_front(), 2);
}

TEST(ClassList, MoveAssignmentStealsContent) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	List<int> b;

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

TEST(ClassList, SelfMoveAssignmentIsSafe) {
	List<int> a;

	a.push_back(1);
	a.push_back(2);

	List<int>& ref = a;

	a = std::move(ref);

	EXPECT_EQ(a.size(), 2u);
	EXPECT_EQ(a.pop_front(), 1);
	EXPECT_EQ(a.pop_front(), 2);
}

TEST(ClassList, WorksWithStrings) {
	List<std::string> l;

	l.push_back("b");
	l.push_front("a");
	l.push_back("c");

	EXPECT_NE(l.find("b"), nullptr);
	EXPECT_EQ(l.find("z"), nullptr);
	EXPECT_EQ(l.pop_front(), "a");
	EXPECT_EQ(l.pop_front(), "b");
	EXPECT_EQ(l.pop_front(), "c");
}

TEST(ClassList, ManyElements) {
	List<int> l;

	for (int i = 0; i < 10000; ++i) l.push_back(i);

	EXPECT_EQ(l.size(), 10000u);

	for (int i = 0; i < 5000; ++i) EXPECT_EQ(l.pop_front(), i);

	EXPECT_EQ(l.size(), 5000u);
	EXPECT_EQ(l.pop_back(), 9999);
}

#endif