#include "set.h"

Set::Set(size_t N) : _bit_field(N) {
    if(N == 0) {
        throw std::invalid_argument("Input Error: Set size cannot be zero!");
    }
}

Set::Set(const Set& other) : _bit_field(other._bit_field) {}

Set::Set(Set&& other) noexcept : _bit_field(std::move(other._bit_field)) {}

Set::Set(const BitField& bf) : _bit_field(bf) {}


Set::operator BitField() const {
    return _bit_field;
}


void Set::insert(size_t element) {
    if (element > _bit_field.get_size() || element <= 0) throw std::out_of_range("Element out of range");

    _bit_field.set_bit(element - 1);
}

void Set::erase(size_t element) {
    if (element > _bit_field.get_size() || element <= 0) throw std::out_of_range("Element out of range");

    _bit_field.reset_bit(element - 1);
}


Set Set::operator+(size_t element) const {
    Set result(*this);

    return result += element ;
}

Set Set::operator-(size_t element) const {
    Set result(*this);

    return result -= element;
}


Set& Set::operator+=(size_t element) {
    insert(element);

    return *this;
}

Set& Set::operator-=(size_t element) {
    erase(element);

    return *this;
}


Set& Set::operator=(const Set& other) {
    if (this == &other) return *this;

    _bit_field = other._bit_field;

    return *this;
}

Set& Set::operator=(Set&& other) noexcept {
    if (this == &other) return *this;

    _bit_field = std::move(other._bit_field);

    return *this;
}


Set Set::operator+(const Set& other) const {
    Set result(*this);

    return result += other;
}

Set Set::operator-(const Set& other) const {
    Set result(*this);
    
    return result -= other;
}

Set Set::operator*(const Set& other) const {
    Set result(*this);

    return result *= other;
}

Set Set::operator-() const {
    Set result(*this);

    result._bit_field = ~result._bit_field;

    return result;
}


Set& Set::operator+=(const Set& other) {
    this->_bit_field |= other._bit_field;

    return *this;
}

Set& Set::operator-=(const Set& other) {
    this->_bit_field &= ~other._bit_field;

    return *this;
}

Set& Set::operator*=(const Set& other) {
    this->_bit_field &= other._bit_field;

    return *this;
}


bool Set::operator==(const Set& other) const noexcept {
    return _bit_field == other._bit_field;
}

bool Set::operator!=(const Set& other) const noexcept {
    return !(*this == other);
}


std::ostream& operator<<(std::ostream& os, const Set& other) {
    os << "{";

    bool first = true;

    for (size_t i = 1; i <= other.get_power(); i++) {
        if (other.is_member(i)) {
            os << (first ? " " : ", ") << i;

            first = false;
        }
    }

    return os << " }";
}

std::istream& operator>>(std::istream& is, Set& other) {
    char c;

    if (!(is >> c)) return is;

    if (c != '{') {
        is.setstate(std::ios::failbit);

        return is;
    }

    Set tmp(other.get_power());

    is >> std::ws;

    if (is.peek() == '}') {
        is.get();
    }
    else {
        while (true) {
            long long value;

            if (!(is >> value)) return is;

            if (value < 1 || static_cast<size_t>(value) > tmp.get_power()) {
                is.setstate(std::ios::failbit);

                return is;
            }

            tmp.insert(static_cast<size_t>(value));

            if (!(is >> c)) return is;

            if (c == '}') break;

            if (c != ',') {
                is.setstate(std::ios::failbit);

                return is;
            }
        }
    }

    other = std::move(tmp);

    return is;
}