#include <gtest/gtest.h>
#include "set.h"
#include "parameters.h"

#ifdef SET_TESTS

TEST(TestSet, can_create_with_default_constructor) {
	Set s;

	EXPECT_EQ(s.get_power(), 1);
	EXPECT_FALSE(s.is_member(1));
}

TEST(TestSet, can_throw_with_default_constructor) {
	EXPECT_THROW(Set s2(0), std::invalid_argument);
}

TEST(TestSet, can_create_with_size_constructor) {
	Set s(5);

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		EXPECT_FALSE(s.is_member(i));
	}
}

TEST(TestSet, can_create_with_copy_constructor) {
	Set s1(5);

	s1.insert(2);
	s1.insert(4);

	Set s2(s1);

	EXPECT_EQ(s2.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s2.is_member(i));
		}
		else {
			EXPECT_FALSE(s2.is_member(i));
		}
	}
}

TEST(TestSet, can_create_with_move_constructor) {
	Set s1(5);

	s1.insert(2);
	s1.insert(4);

	Set s2(std::move(s1));

	EXPECT_EQ(s2.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s2.is_member(i));
		}
		else {
			EXPECT_FALSE(s2.is_member(i));
		}
	}

	EXPECT_EQ(s1.get_power(), 0);
}

TEST(TestSet, can_create_with_bitfield_constructor) {
	BitField bf(5);

	bf.set_bit(1);
	bf.set_bit(3);

	Set s(bf);

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_bitfield_operator) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	BitField bf = s;

	EXPECT_EQ(bf.get_size(), 5);

	for (size_t i = 0; i < 5; i++) {
		if (i == 1 || i == 3) {
			EXPECT_TRUE(bf.get_bit(i));
		}
		else {
			EXPECT_FALSE(bf.get_bit(i));
		}
	}
}

TEST(TestSet, can_insert_elements) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_insert_elements) {
	Set s(5);

	EXPECT_THROW(s.insert(0), std::out_of_range);
	EXPECT_THROW(s.insert(6), std::out_of_range);
}

TEST(TestSet, can_erase_elements) {
	Set s(5);

	s.insert(2);
	s.insert(4);
	s.erase(2);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_erase_elements) {
	Set s(5);

	EXPECT_THROW(s.erase(0), std::out_of_range);
	EXPECT_THROW(s.erase(6), std::out_of_range);
}

TEST(TestSet, can_add_element) {
	Set s(5);
	Set s2 = s + 3;

	EXPECT_EQ(s2.get_power(), 5);
	EXPECT_TRUE(s2.is_member(3));
}

TEST(TestSet, can_throw_add_element) {
	Set s(5);

	EXPECT_THROW(Set s2 = s + 6, std::out_of_range);
}

TEST(TestSet, can_subtract_element) {
	Set s(5);

	s.insert(3);

	Set s2 = s - 3;

	EXPECT_EQ(s2.get_power(), 5);
	EXPECT_FALSE(s2.is_member(3));
}

TEST(TestSet, can_throw_subtract_element) {
	Set s(5);

	EXPECT_THROW(Set s2 = s - 6, std::out_of_range);
}

TEST(TestSet, can_add_assign_element) {
	Set s(5);

	s += 3;

	EXPECT_EQ(s.get_power(), 5);
	EXPECT_TRUE(s.is_member(3));
}

TEST(TestSet, can_throw_add_assign_element) {
	Set s(5);

	EXPECT_THROW(s += 6, std::out_of_range);
}

TEST(TestSet, can_subtract_assign_element) {
	Set s(5);

	s.insert(3);

	s -= 3;

	EXPECT_EQ(s.get_power(), 5);
	EXPECT_FALSE(s.is_member(3));
}

TEST(TestSet, can_throw_subtract_assign_element) {
	Set s(5);

	EXPECT_THROW(s -= 6, std::out_of_range);
}

TEST(TestSet, can_assign_with_copy) {
	Set s1(5);

	s1.insert(2);
	s1.insert(4);

	Set s2(3);

	s2 = s1;

	EXPECT_EQ(s2.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s2.is_member(i));
		}
		else {
			EXPECT_FALSE(s2.is_member(i));
		}
	}
}

TEST(TestSet, can_assign_with_move) {
	Set s1(5);

	s1.insert(2);
	s1.insert(4);

	Set s2(3);

	s2 = std::move(s1);

	EXPECT_EQ(s2.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s2.is_member(i));
		}
		else {
			EXPECT_FALSE(s2.is_member(i));
		}
	}

	EXPECT_EQ(s1.get_power(), 0);
}

TEST(TestSet, can_plus_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	Set s3 = s1 + s2;

	EXPECT_EQ(s3.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 3 || i == 4) {
			EXPECT_TRUE(s3.is_member(i));
		}
		else {
			EXPECT_FALSE(s3.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_plus_operator) {
	Set s1(5);
	Set s2(6);

	EXPECT_THROW(Set s3 = s1 + s2, std::invalid_argument);
}

TEST(TestSet, can_minus_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	Set s3 = s1 - s2;

	EXPECT_EQ(s3.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2) {
			EXPECT_TRUE(s3.is_member(i));
		}
		else {
			EXPECT_FALSE(s3.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_minus_operator) {
	Set s1(5);
	Set s2(6);

	EXPECT_THROW(Set s3 = s1 - s2, std::invalid_argument);
}

TEST(TestSet, can_multiply_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	Set s3 = s1 * s2;

	EXPECT_EQ(s3.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 4) {
			EXPECT_TRUE(s3.is_member(i));
		}
		else {
			EXPECT_FALSE(s3.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_multiply_operator) {
	Set s1(5);
	Set s2(6);

	EXPECT_THROW(Set s3 = s1 * s2, std::invalid_argument);
}

TEST(TestSet, can_negate_operator) {
	Set s1(5);

	s1.insert(2);
	s1.insert(4);

	Set s2 = -s1;

	EXPECT_EQ(s2.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_FALSE(s2.is_member(i));
		}
		else {
			EXPECT_TRUE(s2.is_member(i));
		}
	}
}

TEST(TestSet, can_plus_assign_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	s1 += s2;

	EXPECT_EQ(s1.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 3 || i == 4) {
			EXPECT_TRUE(s1.is_member(i));
		}
		else {
			EXPECT_FALSE(s1.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_plus_assign_operator) {
	Set s1(5);
	Set s2(6);

	EXPECT_THROW(s1 += s2, std::invalid_argument);
}

TEST(TestSet, can_minus_assign_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	s1 -= s2;

	EXPECT_EQ(s1.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2) {
			EXPECT_TRUE(s1.is_member(i));
		}
		else {
			EXPECT_FALSE(s1.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_minus_assign_operator) {
	Set s1(5);
	Set s2(6);

	EXPECT_THROW(s1 -= s2, std::invalid_argument);
}

TEST(TestSet, can_multiply_assign_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	s1 *= s2;

	EXPECT_EQ(s1.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 4) {
			EXPECT_TRUE(s1.is_member(i));
		}
		else {
			EXPECT_FALSE(s1.is_member(i));
		}
	}
}

TEST(TestSet, can_throw_multiply_assign_operator) {
	Set s1(5);
	Set s2(6);

	EXPECT_THROW(s1 *= s2, std::invalid_argument);
}

TEST(TestSet, can_equality_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(2);
	s2.insert(4);

	EXPECT_TRUE(s1 == s2);
}

TEST(TestSet, can_inequality_operator) {
	Set s1(5);
	Set s2(5);

	s1.insert(2);
	s1.insert(4);
	s2.insert(3);
	s2.insert(4);

	EXPECT_TRUE(s1 != s2);
}

TEST(TestSet, can_inequality_with_different_sizes) {
	Set s1(5);
	Set s2(6);

	s1.insert(2);
	s1.insert(4);
	s2.insert(2);
	s2.insert(4);

	EXPECT_TRUE(s1 != s2);
}

TEST(TestSet, can_output_operator) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::ostringstream os;

	os << s;

	EXPECT_EQ(os.str(), "{ 2, 4 }");
}

TEST(TestSet, can_input_operator) {
	Set s(5);

	std::istringstream is("{ 2, 4 }");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_input_operator_with_empty_set) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is("{ }");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		EXPECT_FALSE(s.is_member(i));
	}
}

TEST(TestSet, can_input_operator_error_over_range) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is("{ 7, 5}");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_input_operator_error_under_range) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is("{ -3, 5 }");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_input_operator_error_missing_open_brace) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is(" 1, 5 }");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_input_operator_error_missing_close_brace) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is("{ 1, 5");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_input_operator_error_missing_comma) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is("{ 1 5 }");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

TEST(TestSet, can_input_operator_error_alpha) {
	Set s(5);

	s.insert(2);
	s.insert(4);

	std::istringstream is("{ a, b }");

	is >> s;

	EXPECT_EQ(s.get_power(), 5);

	for (size_t i = 1; i <= 5; i++) {
		if (i == 2 || i == 4) {
			EXPECT_TRUE(s.is_member(i));
		}
		else {
			EXPECT_FALSE(s.is_member(i));
		}
	}
}

#endif