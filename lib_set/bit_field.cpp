#include "bit_field.h"

BitField::BitField(size_t N) : _N(N) {
	_data = new unsigned int[get_data_size()]();
}

BitField::BitField(const BitField& other) : _N(other._N) {
	size_t data_size = get_data_size();
	_data = new unsigned int[data_size];

	for (size_t i = 0; i < data_size; i++) {
		_data[i] = other._data[i];
	}
}

BitField::BitField(BitField&& other) noexcept : _N(other._N) {
	_data = other._data;
	other._data = nullptr;
	other._N = 0;
}


BitField::~BitField() {
	delete[]_data;
}


void BitField::set_bit(size_t pos) {
	if (pos >= _N) throw std::out_of_range("Element is greater than set power");

	_data[get_index(pos)] |= get_mask(pos);
}

void BitField::reset_bit(size_t pos){
	if (pos >= _N) throw std::out_of_range("Element is greater than set power");

	_data[get_index(pos)] &= ~get_mask(pos);
}


bool BitField::get_bit(size_t pos) const {
	if (pos >= _N) throw std::out_of_range("Element is greater than set power");

	return _data[get_index(pos)] & get_mask(pos);
}


BitField& BitField::operator=(const BitField& other) {
	if (this == &other) return *this;

	delete[]_data;

	_N = other._N;
	size_t data_size = get_data_size();
	_data = new unsigned int[data_size];

	for (size_t i = 0; i < data_size; i++) {
		_data[i] = other._data[i];
	}

	return *this;
}

BitField& BitField::operator=(BitField&& other) noexcept {
	if (this == &other) return *this;

	delete[]_data;

	_N = other._N;
	_data = other._data;
	
	other._data = nullptr;
	other._N = 0;

	return *this;
}


BitField BitField::operator&(const BitField& other) const {
	BitField result(*this);

	return result &= other;
}

BitField BitField::operator|(const BitField& other) const {
	BitField result(*this);

	return result |= other;
}

BitField BitField::operator~() const {
	BitField result(*this);

	for (size_t i = 0; i < get_data_size(); i++) {
		result._data[i] = ~result._data[i];
	}

	size_t bits_in_last = _N % (sizeof(unsigned int) * 8);

	if (bits_in_last != 0 && get_data_size() > 0) {
		unsigned int mask = (1u << bits_in_last) - 1;
		result._data[get_data_size() - 1] &= mask;
	}

	return result;
}


BitField& BitField::operator&=(const BitField& other) {
	if (_N != other._N) throw std::invalid_argument("Sets powers don't match");

	if (this == &other) return *this;

	for (size_t i = 0; i < get_data_size(); i++) {
		_data[i] &= other._data[i];
	}

	return *this;
}

BitField& BitField::operator|=(const BitField& other) {
	if (_N != other._N) throw std::invalid_argument("Sets powers don't match");

	if (this == &other) return *this;

	for (size_t i = 0; i < get_data_size(); i++) {
		_data[i] |= other._data[i];
	}

	return *this;
}


std::ostream& operator<<(std::ostream& os, const BitField& other) {
	for (size_t i = 0; i < other._N; i++) {
		os << (other.get_bit(i) ? '1' : '0');
	}

	return os;
}

std::istream& operator>>(std::istream& is, BitField& other) {
	for (size_t i = 0; i < other._N; i++) {
		char c;

		if (is >> c) {
			if (c == '1') {
				other.set_bit(i);
			}
			else if (c == '0') {
				other.reset_bit(i);
			}
			else {
				is.setstate(std::ios::failbit);
				break;
			}
		}
		else {
			break;
		}
	}

	return is;
}
