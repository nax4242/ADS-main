// Copyright 2026 Danila Puzanov

#include <gtest/gtest.h>
#include "../lib_queue_on_list/queue_on_list.h"
#include "../tests/parameters.h"

#ifdef QUEUE_ON_LIST_TESTS

TEST(ClassQueueOnList, can_create_with_default_constructor) {
    TQueueOnList<int> queue;

    EXPECT_THROW(queue.front(), std::logic_error);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.is_empty(), true);
}

TEST(ClassQueueOnList, can_create_with_size_constructor) {
    TQueueOnList<int> queue(5);

    EXPECT_THROW(queue.front(), std::logic_error);
    EXPECT_EQ(queue.size(), 5);
    EXPECT_TRUE(queue.is_empty());
}

TEST(ClassQueueOnList, can_create_with_copy_constructor) {
    TQueueOnList<int> queue1(5);

    for (int i = 0; i < queue1.size(); i++) {
        queue1.push(i);
    }

    TQueueOnList queue2(queue1);

    EXPECT_EQ(queue2.front(), 0);
    EXPECT_EQ(queue2.size(), 5);
    EXPECT_FALSE(queue2.is_empty());
    EXPECT_TRUE(queue2.is_full());
}

TEST(ClassQueueOnList, can_push) {
    TQueueOnList<int> queue(5);

    for (int i = 0; i < queue.size(); i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.front(), 0);
    EXPECT_EQ(queue.is_full(), true);
    EXPECT_FALSE(queue.is_empty());
    EXPECT_TRUE(queue.is_full());
}

TEST(ClassQueueOnList, can_pop) {
    TQueueOnList<int> queue(5);

    for (int i = 0; i < queue.size(); i++) {
        queue.push(i);
    }

    for (int i = 0; i < queue.size(); i++) {
        EXPECT_EQ(queue.pop(), i);
    }

    EXPECT_THROW(queue.front(), std::logic_error);
    EXPECT_TRUE(queue.is_empty());
}

TEST(ClassQueueOnList, can_push_and_pop) {
    TQueueOnList<int> queue(5);

    for (int i = 0; i < queue.size(); i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.pop(), 0);
    EXPECT_EQ(queue.front(), 1);

    queue.push(5);

    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.pop(), 1);
    EXPECT_EQ(queue.front(), 2);
}

TEST(ClassQueueOnList, can_push_and_pop_with_wrap_around) {
    TQueueOnList<int> queue(5);

    for (int i = 0; i < queue.size(); i++) {
        queue.push(i);
    }

    EXPECT_EQ(queue.pop(), 0);
    EXPECT_EQ(queue.pop(), 1);

    queue.push(5);
    queue.push(6);

    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.pop(), 2);
    EXPECT_EQ(queue.front(), 3);
}

TEST(ClassQueueOnList, can_throw_when_push_to_full_queue) {
    TQueueOnList<int> queue(5);

    for (int i = 0; i < queue.size(); i++) {
        queue.push(i);
    }

    EXPECT_THROW(queue.push(5), std::overflow_error);
}

TEST(ClassQueueOnList, can_throw_when_pop_from_empty_queue) {
    TQueueOnList<int> queue(5);

    EXPECT_THROW(queue.pop(), std::underflow_error);
}

TEST(ClassQueueOnList, can_throw_when_front_from_empty_queue) {
    TQueueOnList<int> queue(5);

    EXPECT_THROW(queue.front(), std::logic_error);
}

TEST(ClassQueueOnList, can_check_is_empty_and_is_full) {
    TQueueOnList<int> queue(5);

    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());

    for (int i = 0; i < queue.size(); i++) {
        queue.push(i);
    }

    EXPECT_FALSE(queue.is_empty());
    EXPECT_TRUE(queue.is_full());
}

#endif
