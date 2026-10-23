#include <gtest/gtest.h>
#include "stack_on_mass.h"
#include "parameters.h"


#ifdef STACK_TESTS

TEST(ClassStackOnMass, can_create_with_default_constructor) {
	TStackOnMass<int> stack;
	
	EXPECT_THROW(stack.top(), std::logic_error);
	EXPECT_EQ(stack.size(), 1);
	EXPECT_EQ(stack.is_empty(), true);
}

TEST(ClassStackOnMass, can_create_with_size_constructor) {
	TStackOnMass<int> stack(5);

	EXPECT_THROW(stack.top(), std::logic_error);
	EXPECT_EQ(stack.size(), 5);
	EXPECT_TRUE(stack.is_empty());
}

TEST(ClassStackOnMass, can_create_with_copy_constructor) {
	TStackOnMass<int> stack1(5);

	for (int i = 0; i < stack1.size() - 1; i++) {
		stack1.push(i);
	}

	TStackOnMass stack2(stack1);

	EXPECT_EQ(stack2.top(), 3);
	EXPECT_EQ(stack2.size(), 5);
	EXPECT_FALSE(stack2.is_empty());
	EXPECT_FALSE(stack2.is_full());
}

TEST(ClassStackOnMass, can_push) {
	TStackOnMass<int> stack(5);

	for (int i = 0; i < stack.size(); i++) {
		stack.push(i);
	}

	EXPECT_EQ(stack.top(), 4);
	EXPECT_EQ(stack.is_full(), true);
	EXPECT_FALSE(stack.is_empty());
	EXPECT_TRUE(stack.is_full());
}

TEST(ClassStackOnMass, can_pop) {
	TStackOnMass<int> stack(5);

	for (int i = 0; i < stack.size(); i++) {
		stack.push(i);
	}

	for (int i = 4; i >= 0; i--) {
		EXPECT_EQ(stack.pop(), i);
	}

	EXPECT_THROW(stack.top(), std::logic_error);
	EXPECT_TRUE(stack.is_empty());
}

TEST(ClassStackOnMass, can_throw_when_push_to_full_stack) {
	TStackOnMass<int> stack(5);

	for (int i = 0; i < stack.size(); i++) {
		stack.push(i);
	}

	EXPECT_THROW(stack.push(5), std::overflow_error);
}

TEST(ClassStackOnMass, can_throw_when_pop_from_empty_stack) {
	TStackOnMass<int> stack(5);

	EXPECT_THROW(stack.pop(), std::underflow_error);
}

TEST(ClassStackOnMass, can_throw_when_top_from_empty_stack) {
	TStackOnMass<int> stack(5);

	EXPECT_THROW(stack.top(), std::logic_error);
}

TEST(ClassStackOnMass, can_check_is_empty_and_is_full) {
	TStackOnMass<int> stack(5);

	EXPECT_TRUE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());

	for (int i = 0; i < stack.size(); i++) {
		stack.push(i);
	}

	EXPECT_FALSE(stack.is_empty());
	EXPECT_TRUE(stack.is_full());
}

#endif