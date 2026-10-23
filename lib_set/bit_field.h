#pragma once
#include <stdexcept>
#include <iostream>

class BitField { // хранит [1; _N]
    unsigned int* _data;
    size_t _N;

public:
    explicit BitField(size_t N = 1);
    BitField(const BitField& other);
    BitField(BitField&& other) noexcept;

    ~BitField();

    void set_bit(size_t pos);
    void reset_bit(size_t pos);

    bool get_bit(size_t pos) const;
    inline size_t get_size() const noexcept;

    BitField& operator=(const BitField& other);
    BitField& operator=(BitField&& other) noexcept;
    
    BitField operator&(const BitField& other) const;
    BitField operator|(const BitField& other) const;
    BitField operator~() const;

    BitField& operator&=(const BitField& other);
    BitField& operator|=(const BitField& other);

    friend std::ostream& operator<<(std::ostream& os, const BitField& other);
    friend std::istream& operator>>(std::istream& is, BitField& other);

private:
    inline unsigned int get_mask(size_t pos) const noexcept;
    inline size_t get_index(size_t pos) const noexcept;
    inline size_t get_data_size() const noexcept;
};

inline unsigned int BitField::get_mask(size_t pos) const noexcept {
    return 1u << (pos % (sizeof(unsigned int) * 8));
}

inline size_t BitField::get_index(size_t pos) const noexcept {
    return pos / (sizeof(unsigned int) * 8);
}

inline size_t BitField::get_data_size() const noexcept {
    return (_N + sizeof(unsigned int) * 8 - 1) / (sizeof(unsigned int) * 8);
}

inline size_t BitField::get_size() const noexcept {
	return _N;
}