#pragma once
#include <stdexcept>

template <typename T>
class MultiStack {
	static const size_t DEFAULT_ONE_STACK_SIZE = 5;

	T* _data;
	size_t _N;
	size_t _full_size;
	size_t* _ls;
	size_t* _rs;
	size_t* _tops;

public:
	MultiStack(size_t N = 1, size_t one_stack_size = DEFAULT_ONE_STACK_SIZE);
	MultiStack(const MultiStack& other);
	MultiStack(MultiStack&& other) noexcept;

	~MultiStack();

	MultiStack<T>& operator=(const MultiStack<T>& other);
	MultiStack<T>& operator=(MultiStack<T>&& other) noexcept;

	void push(const T& elem, size_t index_of_stack);
	T pop(size_t index_of_stack);

	inline T& top(size_t index_of_stack) const;
	inline size_t size(size_t index_of_stack) const noexcept;

	inline bool is_empty(size_t index_of_stack) const noexcept;
	inline bool is_full(size_t index_of_stack) const noexcept;
	bool is_overflow() const noexcept;

private:
	void repack();
};

template <typename T>
MultiStack<T>& MultiStack<T>::operator=(const MultiStack<T>& other) {
	if (this == &other) return *this;

	_N = other._N;
	_full_size = other._full_size;

	_data = new T[_full_size];
	_ls = new size_t[_N];
	_rs = new size_t[_N];
	_tops = new size_t[_N];

	for (size_t i = 0; i < _full_size; i++) {
		_data[i] = other._data[i];
	}

	for (size_t i = 0; i < _N; i++) {
		_ls[i] = other._ls[i];
		_rs[i] = other._rs[i];
		_tops[i] = other._tops[i];
	}

	return *this;
}

template <typename T>
MultiStack<T>& MultiStack<T>::operator=(MultiStack<T>&& other) noexcept {
	if (this == &other) return *this;

	_N = other._N;
	_full_size = other._full_size;

	_data = other._data;
	_ls = other._ls;
	_rs = other._rs;
	_tops = other._tops;

	other = MultiStack(_N, DEFAULT_ONE_STACK_SIZE);

	return *this;
}

template <typename T>
MultiStack<T>::MultiStack(size_t N, size_t one_stack_size) {
	if (N == 0) throw std::invalid_argument("Stack count must be more than 0");
	if (one_stack_size == 0) throw std::invalid_argument("One stack size must be more than 0");

	_N = N;
	_full_size = one_stack_size * _N;

	_data = new T[_full_size];
	_ls = new size_t[_N];
	_rs = new size_t[_N];
	_tops = new size_t[_N];

	for (size_t i = 0; i < _N; i++) {
		_ls[i] = i * one_stack_size;
		_rs[i] = one_stack_size - 1 + i * one_stack_size;
		_tops[i] = _ls[i] - 1;
	}
}

template <typename T>
MultiStack<T>::MultiStack(const MultiStack& other) {
	_N = other._N;
	_full_size = other._full_size;

	_data = new T[_full_size];
	_ls = new size_t[_N];
	_rs = new size_t[_N];
	_tops = new size_t[_N];

	for (size_t i = 0; i < _full_size; i++) {
		_data[i] = other._data[i];
	}

	for (size_t i = 0; i < _N; i++) {
		_ls[i] = other._ls[i];
		_rs[i] = other._rs[i];
		_tops[i] = other._tops[i];
	}
}

template <typename T>
MultiStack<T>::MultiStack(MultiStack&& other) noexcept {
	_N = other._N;
	_full_size = other._full_size;

	_data = other._data;
	_ls = other._ls;
	_rs = other._rs;
	_tops = other._tops;

	other = MultiStack(_N, DEFAULT_ONE_STACK_SIZE);
}

template <typename T>
MultiStack<T>::~MultiStack() {
	delete[]_data;
	delete[]_ls;
	delete[]_rs;
	delete[]_tops;
}

template <typename T>
void MultiStack<T>::push(const T& elem, size_t index_of_stack) {
	if (index_of_stack >= _N) throw std::invalid_argument("Invalid index of stack");
	if (is_overflow()) throw std::overflow_error("All stacks are full");
	if (is_full(index_of_stack)) repack();

	_tops[index_of_stack]++;
	_data[_tops[index_of_stack]] = elem;
}

template <typename T>
T MultiStack<T>::pop(size_t index_of_stack) {
	if (index_of_stack >= _N) throw std::invalid_argument("Invalid index of stack");
	if (is_empty(index_of_stack)) throw std::underflow_error("Stack is empty");

	_tops[index_of_stack]--;
	return _data[_tops[index_of_stack] + 1];
}

template <typename T>
inline T& MultiStack<T>::top(size_t index_of_stack) const {
	return _data[_tops[index_of_stack]];
}

template <typename T>
inline size_t MultiStack<T>::size(size_t index_of_stack) const noexcept {
	return _rs[index_of_stack] - _ls[index_of_stack] + 1;
}

template <typename T>
inline bool MultiStack<T>::is_empty(size_t index_of_stack) const noexcept {
	return _tops[index_of_stack] == _ls[index_of_stack] - 1
}

template <typename T>
inline bool MultiStack<T>::is_full(size_t index_of_stack) const noexcept {
	return _tops[index_of_stack] == _rs[index_of_stack];
}

template <typename T>
bool MultiStack<T>::is_overflow() const noexcept {
	for (size_t i = 0; i < _N; i++) {
		if (!(is_full(i))) return false;
	}

	return true;
}

template <typename T>
void MultiStack<T>::repack() {

}