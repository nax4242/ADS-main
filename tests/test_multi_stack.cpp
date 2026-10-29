#include <gtest/gtest.h>
#include "multi_stack.h"
#include "parameters.h"

#ifdef MULTI_STACK_TESTS

TEST(MultiStackCtor, DefaultIsEmpty) {
	MultiStack<int> s;
	EXPECT_TRUE(s.is_empty(0));
	EXPECT_FALSE(s.is_full(0));
	EXPECT_FALSE(s.is_overflow());
}

TEST(MultiStackCtor, InvalidArgsThrow) {
	EXPECT_THROW(MultiStack<int>(0, 5), std::invalid_argument);
	EXPECT_THROW(MultiStack<int>(3, 0), std::invalid_argument);
}

TEST(MultiStackCtor, SizeIsCapacityOfOneStack) {
	MultiStack<int> s(3, 4);
	EXPECT_EQ(s.size(0), 4u);
	EXPECT_EQ(s.size(1), 4u);
	EXPECT_EQ(s.size(2), 4u);
}

TEST(MultiStackBasic, PushTop) {
	MultiStack<int> s(2, 3);
	s.push(10, 0);
	EXPECT_EQ(s.top(0), 10);
	s.push(20, 0);
	EXPECT_EQ(s.top(0), 20);
	EXPECT_FALSE(s.is_empty(0));
	EXPECT_TRUE(s.is_empty(1));
}

TEST(MultiStackBasic, PopIsLifo) {
	MultiStack<int> s(2, 3);
	s.push(1, 0);
	s.push(2, 0);
	s.push(3, 0);
	EXPECT_EQ(s.pop(0), 3);
	EXPECT_EQ(s.pop(0), 2);
	EXPECT_EQ(s.pop(0), 1);
	EXPECT_TRUE(s.is_empty(0));
}

TEST(MultiStackBasic, StacksAreIndependent) {
	MultiStack<int> s(3, 3);
	s.push(1, 0);
	s.push(2, 1);
	s.push(3, 2);
	EXPECT_EQ(s.top(0), 1);
	EXPECT_EQ(s.top(1), 2);
	EXPECT_EQ(s.top(2), 3);
}

TEST(MultiStackBasic, IsFull) {
	MultiStack<int> s(2, 2);
	s.push(1, 0);
	EXPECT_FALSE(s.is_full(0));
	s.push(2, 0);
	EXPECT_TRUE(s.is_full(0));
	EXPECT_FALSE(s.is_full(1));
}

TEST(MultiStackErrors, PopEmptyThrows) {
	MultiStack<int> s(2, 3);
	EXPECT_THROW(s.pop(0), std::underflow_error);
}

TEST(MultiStackErrors, TopEmptyThrows) {
	MultiStack<int> s(2, 3);
	EXPECT_THROW(s.top(1), std::underflow_error);
}

TEST(MultiStackErrors, InvalidIndexThrows) {
	MultiStack<int> s(2, 3);
	EXPECT_THROW(s.push(1, 2), std::invalid_argument);
	EXPECT_THROW(s.pop(2), std::invalid_argument);
	EXPECT_THROW(s.top(2), std::invalid_argument);
	EXPECT_THROW(s.size(2), std::invalid_argument);
	EXPECT_THROW(s.is_empty(2), std::invalid_argument);
	EXPECT_THROW(s.is_full(2), std::invalid_argument);
}

TEST(MultiStackErrors, OverflowThrows) {
	MultiStack<int> s(2, 2);
	for (int i = 0; i < 4; i++) s.push(i, i % 2);

	EXPECT_TRUE(s.is_overflow());
	EXPECT_THROW(s.push(100, 0), std::overflow_error);
	EXPECT_THROW(s.push(100, 1), std::overflow_error);
}

TEST(MultiStackRepack, PushIntoFullStackUsesNeighbourSpace) {
	MultiStack<int> s(2, 3);
	for (int i = 1; i <= 5; i++) s.push(i, 0);

	EXPECT_FALSE(s.is_overflow());
	for (int i = 5; i >= 1; i--) EXPECT_EQ(s.pop(0), i);
}

TEST(MultiStackRepack, ProportionalDistribution) {
	MultiStack<int> s(3, 8);
	for (int i = 1; i <= 8; i++) s.push(i, 0);
	s.push(100, 1);
	s.push(200, 2);

	s.push(9, 0);

	EXPECT_EQ(s.size(0), 20u);
	EXPECT_EQ(s.size(1), 2u);
	EXPECT_EQ(s.size(2), 2u);
}

TEST(MultiStackRepack, DataPreserved) {
	MultiStack<int> s(3, 8);
	for (int i = 1; i <= 8; i++) s.push(i, 0);
	s.push(100, 1);
	s.push(200, 2);
	s.push(9, 0);

	EXPECT_EQ(s.top(1), 100);
	EXPECT_EQ(s.top(2), 200);
	for (int i = 9; i >= 1; i--) EXPECT_EQ(s.pop(0), i);
	EXPECT_TRUE(s.is_empty(0));
	EXPECT_EQ(s.pop(1), 100);
	EXPECT_EQ(s.pop(2), 200);
}

TEST(MultiStackRepack, EmptyFirstStackAndRepackBack) {
	MultiStack<int> s(2, 3);
	for (int i = 1; i <= 4; i++) s.push(i, 1);

	EXPECT_TRUE(s.is_empty(0));

	s.push(50, 0);
	EXPECT_EQ(s.top(0), 50);
	for (int i = 4; i >= 1; i--) EXPECT_EQ(s.pop(1), i);
	EXPECT_EQ(s.pop(0), 50);
}

TEST(MultiStackRepack, FillCompletelyThroughOneStack) {
	MultiStack<int> s(3, 3);
	for (int i = 0; i < 9; i++) s.push(i, 0);

	EXPECT_TRUE(s.is_overflow());
	EXPECT_THROW(s.push(9, 0), std::overflow_error);
	for (int i = 8; i >= 0; i--) EXPECT_EQ(s.pop(0), i);
}

TEST(MultiStackCopy, CopyConstructorIsIndependent) {
	MultiStack<int> a(2, 3);
	a.push(1, 0);
	a.push(2, 1);

	MultiStack<int> b(a);
	b.push(3, 0);

	EXPECT_EQ(a.top(0), 1);
	EXPECT_EQ(b.top(0), 3);
	EXPECT_EQ(b.top(1), 2);
}

TEST(MultiStackCopy, CopyAssignment) {
	MultiStack<int> a(2, 3);
	a.push(1, 0);
	a.push(2, 1);

	MultiStack<int> b(4, 2);
	b = a;
	b.push(3, 0);

	EXPECT_EQ(a.top(0), 1);
	EXPECT_EQ(b.top(0), 3);
	EXPECT_EQ(b.top(1), 2);
	EXPECT_EQ(b.size(0), a.size(0));
}

TEST(MultiStackMove, MoveConstructor) {
	MultiStack<int> a(2, 3);
	a.push(1, 0);
	a.push(2, 1);

	MultiStack<int> b(std::move(a));

	EXPECT_EQ(b.top(0), 1);
	EXPECT_EQ(b.top(1), 2);
}

TEST(MultiStackMove, MoveAssignment) {
	MultiStack<int> a(2, 3);
	a.push(1, 0);
	a.push(2, 1);

	MultiStack<int> b(4, 2);
	b = std::move(a);

	EXPECT_EQ(b.top(0), 1);
	EXPECT_EQ(b.top(1), 2);
	b.push(3, 0);
	EXPECT_EQ(b.top(0), 3);
}

TEST(MultiStackRepack, ExtremeSkewGivesAllSpaceToOneStack) {
	MultiStack<int> s(4, 5);
	for (int i = 0; i < 6; i++) s.push(i, 2);

	EXPECT_EQ(s.size(0), 0u);
	EXPECT_EQ(s.size(1), 0u);
	EXPECT_EQ(s.size(2), 20u);
	EXPECT_EQ(s.size(3), 0u);

	for (int i = 6; i < 20; i++) s.push(i, 2);
	EXPECT_TRUE(s.is_overflow());
	EXPECT_THROW(s.push(0, 0), std::overflow_error);
	EXPECT_THROW(s.top(0), std::underflow_error);

	for (int i = 19; i >= 0; i--) EXPECT_EQ(s.pop(2), i);
}

TEST(MultiStackRepack, CapacitySumIsConserved) {
	MultiStack<int> s(4, 5);
	for (int i = 0; i < 3; i++) s.push(i, 0);
	for (int i = 0; i < 5; i++) s.push(i, 1);
	s.push(1, 2);
	s.push(99, 1);

	size_t sum = 0;
	for (size_t i = 0; i < 4; i++) sum += s.size(i);
	EXPECT_EQ(sum, 20u);
}

TEST(MultiStackRepack, TargetIsFirstStack) {
	MultiStack<int> s(3, 4);
	for (int i = 1; i <= 4; i++) s.push(i, 0);
	s.push(10, 1);
	s.push(20, 1);
	s.push(100, 2);
	s.push(200, 2);

	s.push(5, 0);

	EXPECT_EQ(s.size(0), 8u);
	EXPECT_EQ(s.size(1), 2u);
	EXPECT_EQ(s.size(2), 2u);

	for (int i = 5; i >= 1; i--) EXPECT_EQ(s.pop(0), i);
	EXPECT_EQ(s.pop(1), 20);
	EXPECT_EQ(s.pop(1), 10);
	EXPECT_EQ(s.pop(2), 200);
	EXPECT_EQ(s.pop(2), 100);
}

TEST(MultiStackRepack, TargetIsMiddleStack) {
	MultiStack<int> s(3, 8);
	s.push(111, 0);
	s.push(333, 2);
	for (int i = 1; i <= 8; i++) s.push(i, 1);

	s.push(9, 1);

	EXPECT_EQ(s.size(0), 2u);
	EXPECT_EQ(s.size(1), 20u);
	EXPECT_EQ(s.size(2), 2u);

	EXPECT_EQ(s.top(0), 111);
	EXPECT_EQ(s.top(2), 333);
	for (int i = 9; i >= 1; i--) EXPECT_EQ(s.pop(1), i);
}

TEST(MultiStackRepack, TargetIsLastStack) {
	MultiStack<int> s(3, 8);
	s.push(111, 0);
	s.push(222, 1);
	for (int i = 1; i <= 8; i++) s.push(i, 2);

	s.push(9, 2);

	EXPECT_EQ(s.size(0), 2u);
	EXPECT_EQ(s.size(1), 2u);
	EXPECT_EQ(s.size(2), 20u);

	EXPECT_EQ(s.top(0), 111);
	EXPECT_EQ(s.top(1), 222);
	for (int i = 9; i >= 1; i--) EXPECT_EQ(s.pop(2), i);
}

TEST(MultiStackRepack, OrderPreservedInAllStacks) {
	MultiStack<int> s(3, 5);
	for (int v : {1, 2, 3}) s.push(v, 0);
	for (int v : {10, 20, 30, 40, 50}) s.push(v, 1);
	for (int v : {100, 200}) s.push(v, 2);

	s.push(60, 1);

	EXPECT_EQ(s.size(0), 4u);
	EXPECT_EQ(s.size(1), 9u);
	EXPECT_EQ(s.size(2), 2u);

	for (int v : {60, 50, 40, 30, 20, 10}) EXPECT_EQ(s.pop(1), v);
	for (int v : {3, 2, 1}) EXPECT_EQ(s.pop(0), v);
	for (int v : {200, 100}) EXPECT_EQ(s.pop(2), v);
}

TEST(MultiStackRepack, EmptyNeighbourShrinksToZero) {
	MultiStack<int> s(2, 5);
	for (int i = 0; i < 6; i++) s.push(i, 0);

	EXPECT_EQ(s.size(0), 10u);
	EXPECT_EQ(s.size(1), 0u);
	EXPECT_TRUE(s.is_empty(1));
	EXPECT_TRUE(s.is_full(1));

	for (int i = 6; i < 10; i++) s.push(i, 0);
	EXPECT_TRUE(s.is_overflow());
	EXPECT_THROW(s.push(1, 1), std::overflow_error);
}

TEST(MultiStackRepack, InterleavedPushPopWithRepack) {
	MultiStack<int> s(2, 3);
	for (int i = 1; i <= 4; i++) s.push(i, 0);
	EXPECT_EQ(s.pop(0), 4);
	EXPECT_EQ(s.pop(0), 3);

	s.push(10, 1);
	EXPECT_EQ(s.size(0), 4u);
	EXPECT_EQ(s.size(1), 2u);
	s.push(20, 1);

	s.push(30, 1);
	EXPECT_EQ(s.size(0), 2u);
	EXPECT_EQ(s.size(1), 4u);

	EXPECT_EQ(s.pop(1), 30);
	EXPECT_EQ(s.pop(1), 20);
	EXPECT_EQ(s.pop(1), 10);
	EXPECT_EQ(s.pop(0), 2);
	EXPECT_EQ(s.pop(0), 1);
}

TEST(MultiStackRepack, ManyRepacksKeepAllData) {
	const size_t N = 4;
	MultiStack<int> s(N, 3);
	std::vector<int> expected[N];

	for (int i = 0; i < 12; i++) {
		size_t st = static_cast<size_t>(i * i + i / 3) % N;
		s.push(i, st);
		expected[st].push_back(i);
	}

	EXPECT_TRUE(s.is_overflow());
	EXPECT_THROW(s.push(0, 0), std::overflow_error);

	for (size_t st = 0; st < N; st++) {
		while (!expected[st].empty()) {
			EXPECT_EQ(s.pop(st), expected[st].back());
			expected[st].pop_back();
		}
		EXPECT_TRUE(s.is_empty(st));
	}
}

TEST(MultiStackRepack, WorksWithStrings) {
	MultiStack<std::string> s(2, 2);
	s.push("first long string to avoid small buffer", 0);
	s.push("second long string to avoid small buffer", 0);
	s.push("third long string to avoid small buffer", 1);

	s.push("fourth long string to avoid small buffer", 0); // repack

	EXPECT_EQ(s.pop(0), "fourth long string to avoid small buffer");
	EXPECT_EQ(s.pop(0), "second long string to avoid small buffer");
	EXPECT_EQ(s.pop(0), "first long string to avoid small buffer");
	EXPECT_EQ(s.pop(1), "third long string to avoid small buffer");
}

TEST(MultiStackRepack, SingleStackOverflowsWithoutRepack) {
	MultiStack<int> s(1, 3);
	for (int i = 0; i < 3; i++) s.push(i, 0);

	EXPECT_TRUE(s.is_overflow());
	EXPECT_THROW(s.push(3, 0), std::overflow_error);
}

#endif