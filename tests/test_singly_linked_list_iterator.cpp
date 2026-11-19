// Copyright 2026 Danila Puzanov

#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "../lib_singly_linked_list/singly_linked_list.h"
#include "../tests/parameters.h"

#ifdef SINGLY_LINKED_LIST_ITERATOR_TESTS

TEST(IteratorLoopTest, standart_for_cycle) {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int expected = 1;

    for (auto it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
}

TEST(IteratorLoopTest, range_based_for) {
    List<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int sum = 0;

    for (int x : list) {
        sum += x;
    }

    EXPECT_EQ(sum, 60);
}

TEST(IteratorLoopTest, multiply_in_cycle) {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    for (auto it = list.begin(); it != list.end(); it++) {
        *it *= 10;
    }

    auto it = list.begin();

    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*(it + 1), 20);
    EXPECT_EQ(*(it + 2), 30);
}

TEST(IteratorLoopTest, standart_for_cycle_for_const) {
    List<int> list;

    list.push_back(5);
    list.push_back(15);

    const List<int>& clist = list;
    int sum = 0;

    for (auto it = clist.begin(); it != clist.end(); it++) {
        sum += *it;
    }

    EXPECT_EQ(sum, 20);
}

TEST(IteratorLoopTest, standart_for_cycle_for_empty) {
    List<int> empty_list;

    int count = 0;
    for (auto it = empty_list.begin(); it != empty_list.end(); it++) {
        count++;
    }

    EXPECT_EQ(count, 0);
}

bool is_const(int&) { return false; }
bool is_const(const int&) { return true; }

TEST(IteratorTest, const_iterator_is_const) {
    List<int> list;
    list.push_back(10);

    const List<int>& clist = list;

    EXPECT_FALSE(is_const(*list.begin()));
    EXPECT_TRUE(is_const(*clist.begin()));
}

#endif
