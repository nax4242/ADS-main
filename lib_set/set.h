#include "bit_field.h"

class Set { // [1, N]
	BitField _bit_field;

public:
	Set(size_t N = 1);
	Set(const Set& other);
	Set(Set&& other) noexcept;
	Set(const BitField& bf);

	operator BitField() const;

	inline size_t get_power() const noexcept;
	inline bool is_member(size_t element) const;

	void insert(size_t element);
	void erase(size_t element);

	Set operator+(size_t element) const;
	Set operator-(size_t element) const;

	Set& operator+=(size_t element);
	Set& operator-=(size_t element);

	Set& operator=(const Set& other);
	Set& operator=(Set&& other) noexcept;

	Set operator+(const Set& other) const;
	Set operator-(const Set& other) const;
	Set operator*(const Set& other) const;
	Set operator-() const;

	Set& operator+=(const Set& other);
	Set& operator-=(const Set& other);
	Set& operator*=(const Set& other);

	bool operator==(const Set& other) const noexcept;
	bool operator!=(const Set& other) const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Set& other);
	friend std::istream& operator>>(std::istream& is, Set& other);
};

inline size_t Set::get_power() const noexcept {
	return _bit_field.get_size();
}

inline bool Set::is_member(size_t element) const {
	if (element > _bit_field.get_size() || element <= 0) throw std::out_of_range("Element out of range");

	return _bit_field.get_bit(element - 1);
}