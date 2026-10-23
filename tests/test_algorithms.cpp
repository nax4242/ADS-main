// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_algorithms/algorithms.h"
#include "parameters.h"

#define EPSILON 0.000001

#ifdef ALGORITHM_TESTS

TEST(TestEasyExampleLib, can_div) {
  // Arrange
  int x = 10;
  int y = 2;

  // Act & Assert
  ASSERT_NO_THROW(division(x, y));
}

TEST(TestEasyExampleLib, can_div_correctly) {
    // Arrange
    int x = 6;
    int y = 2;

    // Act
    int actual_result = division(x, y);

    // Assert
    int expected_result = 3;
    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestEasyExampleLib, can_div_correctly_with_remainder) {
    // Arrange
    int x = 5;
    int y = 4;

    // Act
    float actual_result = division(x, y);

    // Assert
    float expected_result = 1.25;
    EXPECT_NEAR(expected_result, actual_result, EPSILON);
}

TEST(TestEasyExampleLib, throw_when_try_div_by_zero) {
  // Arrange
  int x = 10;
  int y = 0;

  // Act & Assert
  ASSERT_ANY_THROW(division(x, y));
}

TEST(TestCheckBrackets, new_algorithm_test1) {
    EXPECT_TRUE(check_brackets("(()()()()(()()))"));
}

TEST(TestCheckBrackets, new_algorithm_test2) {
    EXPECT_TRUE(check_brackets("[{}(){()[]}]"));
}

TEST(TestCheckBrackets, new_algorithm_test3) {
    EXPECT_FALSE(check_brackets("[{}(){()[]{{{}]"));
}

TEST(TestCheckBrackets, new_algorithm_test4) {
    EXPECT_FALSE(check_brackets("))))[{}()()[]{}]"));
}

TEST(TestCheckBrackets, empty_string_is_correct) {
    EXPECT_TRUE(check_brackets(""));
}

TEST(TestCheckBrackets, single_pair_round) {
    EXPECT_TRUE(check_brackets("()"));
}

TEST(TestCheckBrackets, single_pair_square) {
    EXPECT_TRUE(check_brackets("[]"));
}

TEST(TestCheckBrackets, single_pair_curly) {
    EXPECT_TRUE(check_brackets("{}"));
}

TEST(TestCheckBrackets, sequence_of_different_pairs) {
    EXPECT_TRUE(check_brackets("()[]{}"));
}

TEST(TestCheckBrackets, nested_same_type) {
    EXPECT_TRUE(check_brackets("((()))"));
}

TEST(TestCheckBrackets, nested_different_types) {
    EXPECT_TRUE(check_brackets("{[()]}"));
}

TEST(TestCheckBrackets, nested_and_sequential_mixed) {
    EXPECT_TRUE(check_brackets("{[()()]([])}[]"));
}

TEST(TestCheckBrackets, deep_nesting) {
    std::string str(500, '(');
    str += std::string(500, ')');

    EXPECT_TRUE(check_brackets(str));
}

TEST(TestCheckBrackets, single_opening_bracket) {
    EXPECT_FALSE(check_brackets("("));
}

TEST(TestCheckBrackets, single_closing_bracket) {
    EXPECT_FALSE(check_brackets(")"));
}

TEST(TestCheckBrackets, only_opening_brackets) {
    EXPECT_FALSE(check_brackets("([{"));
}

TEST(TestCheckBrackets, only_closing_brackets) {
    EXPECT_FALSE(check_brackets(")]}"));
}

TEST(TestCheckBrackets, wrong_order_closing_before_opening) {
    EXPECT_FALSE(check_brackets(")("));
}

TEST(TestCheckBrackets, mismatched_round_and_square) {
    EXPECT_FALSE(check_brackets("(]"));
}

TEST(TestCheckBrackets, mismatched_curly_and_round) {
    EXPECT_FALSE(check_brackets("{)"));
}

TEST(TestCheckBrackets, mismatched_square_and_curly) {
    EXPECT_FALSE(check_brackets("[}"));
}

TEST(TestCheckBrackets, intersecting_pairs) {
    EXPECT_FALSE(check_brackets("([)]"));
}

TEST(TestCheckBrackets, extra_closing_bracket_at_end) {
    EXPECT_FALSE(check_brackets("())"));
}

TEST(TestCheckBrackets, extra_opening_bracket_at_start) {
    EXPECT_FALSE(check_brackets("(()"));
}

TEST(TestCheckBrackets, extra_closing_after_valid_prefix) {
    EXPECT_FALSE(check_brackets("{}]"));
}

TEST(TestCheckBrackets, unclosed_bracket_inside_nesting) {
    EXPECT_FALSE(check_brackets("{[(])}"));
}

TEST(TestCheckBrackets, deep_nesting_missing_one_closing) {
    std::string str(500, '(');
    str += std::string(499, ')');

    EXPECT_FALSE(check_brackets(str));
}

#endif