#include <gtest/gtest.h>
#include "bit_field.h"
#include "parameters.h"

#ifdef BITFIELD_TESTS

TEST(BitFieldTest, can_create_with_default_constructor) {
    BitField bf;

    EXPECT_EQ(bf.get_size(), 1);
}

TEST(BitFieldTest, can_create_with_size_constructor) {
    BitField bf(10);

    EXPECT_EQ(bf.get_size(), 10);
}

TEST(BitFieldTest, can_create_with_copy_constructor) {
    BitField bf1(10);

    bf1.set_bit(3);
    BitField bf2(bf1);

    EXPECT_EQ(bf2.get_size(), 10);
    EXPECT_TRUE(bf2.get_bit(3));
}

TEST(BitFieldTest, can_create_with_move_constructor) {
    BitField bf1(10);

    bf1.set_bit(3);
    BitField bf2(std::move(bf1));

    EXPECT_EQ(bf2.get_size(), 10);
    EXPECT_TRUE(bf2.get_bit(3));
    EXPECT_EQ(bf1.get_size(), 0);
}

TEST(BitFieldTest, can_set_and_get_bit) {
    BitField bf(10);

    bf.set_bit(3);

    EXPECT_TRUE(bf.get_bit(3));
    EXPECT_FALSE(bf.get_bit(2));
}

TEST(BitFieldTest, can_throw_set_bit) {
    BitField bf(10);

    EXPECT_THROW(bf.set_bit(90), std::out_of_range);
}

TEST(BitFieldTest, can_reset_and_get_bit) {
    BitField bf(10);

    bf.set_bit(5);
    bf.reset_bit(5);

    EXPECT_FALSE(bf.get_bit(5));
}

TEST(BitFieldTest, can_throw_reset_bit) {
    BitField bf(10);

    EXPECT_THROW(bf.reset_bit(90), std::out_of_range);
}

TEST(BitFieldTest, can_throw_get_bit) {
    BitField bf(10);

    EXPECT_THROW(bf.get_bit(90), std::out_of_range);
}

TEST(BitFieldTest, can_assign_operator) {
    BitField bf1(10);
    BitField bf2(10);

    bf1.set_bit(3);
    bf2 = bf1;

    EXPECT_EQ(bf2.get_size(), 10);
    EXPECT_TRUE(bf2.get_bit(3));
    EXPECT_EQ(bf1.get_size(), 10);
    EXPECT_TRUE(bf1.get_bit(3));
}

TEST(BitFieldTest, can_move_assign_operator) {
    BitField bf1(10);
    BitField bf2(10);

    bf1.set_bit(3);
    bf2 = std::move(bf1);

    EXPECT_EQ(bf2.get_size(), 10);
    EXPECT_TRUE(bf2.get_bit(3));
    EXPECT_EQ(bf1.get_size(), 0);
}

TEST(BitFieldTest, can_and_operator) {
	BitField bf1(10);
	BitField bf2(10);

	bf1.set_bit(3);
	bf2.set_bit(3);
	bf2.set_bit(5);

	BitField bf3 = bf1 & bf2;

	EXPECT_EQ(bf3.get_size(), 10);
	EXPECT_TRUE(bf3.get_bit(3));
	EXPECT_FALSE(bf3.get_bit(5));
}

TEST(BitFieldTest, can_throw_and_operator) {
    BitField bf1(10);
    BitField bf2(20);
    EXPECT_THROW(bf1 & bf2, std::invalid_argument);
}

TEST(BitFieldTest, can_or_operator) {
	BitField bf1(10);
	BitField bf2(10);

	bf1.set_bit(3);
	bf2.set_bit(5);

	BitField bf3 = bf1 | bf2;

	EXPECT_EQ(bf3.get_size(), 10);
	EXPECT_TRUE(bf3.get_bit(3));
	EXPECT_TRUE(bf3.get_bit(5));
}

TEST(BitFieldTest, can_throw_or_operator) {
	BitField bf1(10);
	BitField bf2(20);
	EXPECT_THROW(bf1 | bf2, std::invalid_argument);
}

TEST(BitFieldTest, can_not_operator) {
	BitField bf1(10);

	bf1.set_bit(3);
	bf1.set_bit(5);

	BitField bf2 = ~bf1;

	EXPECT_EQ(bf2.get_size(), 10);
	for (size_t i = 0; i < bf2.get_size(); i++) {
		if (i == 3 || i == 5) {
			EXPECT_FALSE(bf2.get_bit(i));
		}
		else {
			EXPECT_TRUE(bf2.get_bit(i));
		}
	}
}

TEST(BitFieldTest, can_and_assign_operator) {
	BitField bf1(10);
	BitField bf2(10);

	bf1.set_bit(3);
	bf2.set_bit(3);
	bf2.set_bit(5);

	bf1 &= bf2;

	EXPECT_EQ(bf1.get_size(), 10);
	EXPECT_TRUE(bf1.get_bit(3));
	EXPECT_FALSE(bf1.get_bit(5));
}

TEST(BitFieldTest, can_throw_and_assign_operator) {
	BitField bf1(10);
	BitField bf2(20);

	EXPECT_THROW(bf1 &= bf2, std::invalid_argument);
}

TEST(BitFieldTest, can_or_assign_operator) {
	BitField bf1(10);
	BitField bf2(10);

	bf1.set_bit(3);
	bf2.set_bit(5);

	bf1 |= bf2;

	EXPECT_EQ(bf1.get_size(), 10);
	EXPECT_TRUE(bf1.get_bit(3));
	EXPECT_TRUE(bf1.get_bit(5));
}

TEST(BitFieldTest, can_throw_or_assign_operator) {
	BitField bf1(10);
	BitField bf2(20);

	EXPECT_THROW(bf1 |= bf2, std::invalid_argument);
}

TEST(BitFieldTest, can_equality_operator) {
	BitField bf1(10);
	BitField bf2(10);

	bf1.set_bit(3);
	bf2.set_bit(3);

	EXPECT_TRUE(bf1 == bf2);
}

TEST(BitFieldTest, can_inequality_operator) {
	BitField bf1(10);
	BitField bf2(10);

	bf1.set_bit(3);
	bf2.set_bit(5);

	EXPECT_TRUE(bf1 != bf2);
}

TEST(BitFieldTest, can_inequality_with_different_sizes) {
	BitField bf1(10);
	BitField bf2(20);

	bf1.set_bit(3);
	bf2.set_bit(3);

	EXPECT_TRUE(bf1 != bf2);
}	

TEST(BitFieldTest, can_output_operator) {
	BitField bf(10);

	bf.set_bit(3);
	bf.set_bit(5);

	std::ostringstream os;
	os << bf;

	EXPECT_EQ(os.str(), "0001010000");
}

TEST(BitFieldTest, can_input_operator) {
	BitField bf(10);
	std::istringstream is("0001010000");

	is >> bf;

	for (size_t i = 0; i < bf.get_size(); i++) {
		if (i == 3 || i == 5) {
			EXPECT_TRUE(bf.get_bit(i));
		}
		else {
			EXPECT_FALSE(bf.get_bit(i));
		}
	}
}

TEST(BitFieldTest, can_input_operator_error_alpha) {
	BitField bf(10);

	bf.set_bit(3);
	bf.set_bit(5);

	std::istringstream is("000a1010000");

	is >> bf;

	EXPECT_EQ(10, bf.get_size());

	for(size_t i = 0; i < bf.get_size(); i++) {
		if (i == 3 || i == 5) {
			EXPECT_TRUE(bf.get_bit(i));
		}
		else {
			EXPECT_FALSE(bf.get_bit(i));
		}
	}
}

TEST(BitFieldTest, can_input_operator_error_space) {
	BitField bf(10);

	bf.set_bit(3);
	bf.set_bit(5);

	std::istringstream is("000 1010000");

	is >> bf;

	EXPECT_EQ(10, bf.get_size());

	for (size_t i = 0; i < bf.get_size(); i++) {
		if (i == 3 || i == 5) {
			EXPECT_TRUE(bf.get_bit(i));
		}
		else {
			EXPECT_FALSE(bf.get_bit(i));
		}
	}
}


#endif