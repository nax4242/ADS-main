#pragma once
#include <stdexcept>

template <typename T>
class TStackOnMass {
	T* _data;
	size_t _size;
	size_t _top;

public:
	TStackOnMass(size_t size = 1);
	TStackOnMass(const TStackOnMass& other);

	~TStackOnMass();

	void push(const T& elem);
	T pop();

	inline T& top() const;
	inline size_t size() const noexcept;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
};

template <typename T>
TStackOnMass<T>::TStackOnMass(size_t size) {
	_data = new T[size];
	_size = size;
	_top = -1;
}

template <typename T>
TStackOnMass<T>::TStackOnMass(const TStackOnMass& other) {
	_size = other._size;
	_top = other._top;
	_data = new T[_size];

	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
}

template <typename T>
TStackOnMass<T>::~TStackOnMass() {
	delete[]_data;
	_size = 0;
	_top = -1;
}

template <typename T>
void TStackOnMass<T>::push(const T& elem) {
	if (is_full()) {
		throw std::overflow_error("Stack is full, impossible to push");
	}

	_top++;
	_data[_top] = elem;
}

template <typename T>
T TStackOnMass<T>::pop() {
	if (is_empty()) {
		throw std::underflow_error("Stack is empty, impossible to pop");
	}

	_top--;
	return _data[_top + 1];
}

template <typename T>
inline T& TStackOnMass<T>::top() const {
	if (is_empty()) {
		throw std::logic_error("Stack is empty, impossible to get top");
	}

	return _data[_top];
}

template <typename T>
inline size_t TStackOnMass<T>::size() const noexcept {
	return _size;
}

template <typename T>
inline bool TStackOnMass<T>::is_empty() const noexcept {
	return _top == -1;
}

template <typename T>
inline bool TStackOnMass<T>::is_full() const noexcept {
	return _top == _size - 1;
}