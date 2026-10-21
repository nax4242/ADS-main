#pragma once
#include <stdexcept>

template <typename T>
class TQueueOnMass {
	T* _data;
	size_t _size;
	size_t _count;
	size_t _front;
	size_t _back;

public:
	TQueueOnMass(size_t size = 1);
	TQueueOnMass(const TQueueOnMass& other);

	~TQueueOnMass();

	void push(const T& element);
	T pop();

	inline T& front();
	inline size_t size() const noexcept;

	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
};

template <typename T>
TQueueOnMass<T>::TQueueOnMass(size_t size) : _size(size), _count(0), _front(0), _back(0) {
	_data = new T[_size];
}

template <typename T>
TQueueOnMass<T>::TQueueOnMass(const TQueueOnMass& other) : _size(other._size), _count(other._count), _front(other._front), _back(other._back) {
	_data = new T[_size];

	for (size_t i = 0; i < _count; i++) {
		_data[(_front + i) % _size] = other._data[(other._front + i) % other._size];
	}
}

template <typename T>
TQueueOnMass<T>::~TQueueOnMass() {
	delete[] _data;
}

template <typename T>
void TQueueOnMass<T>::push(const T& element) {
	if (is_full()) {
		throw std::overflow_error("Queue is full, impossible to push");
	}

	_data[_back] = element;
	_back = (_back + 1) % _size;
	_count++;
}

template <typename T>
T TQueueOnMass<T>::pop() {
	if (is_empty()) {
		throw std::underflow_error("Queue is empty, impossible to pop");
	}

	T popped = _data[_front];
	_front = (_front + 1) % _size;
	_count--;
	return popped;
}

template <typename T>
inline size_t TQueueOnMass<T>::size() const noexcept {
	return _size;
}

template <typename T>
inline T& TQueueOnMass<T>::front() {
	if (is_empty()) {
		throw std::logic_error("Queue is empty, impossible to get front");
	}

	return _data[_front];
}	

template <typename T>
inline bool TQueueOnMass<T>::is_empty() const noexcept {
	return _count == 0;
}

template <typename T>	
inline bool TQueueOnMass<T>::is_full() const noexcept {
	return _count == _size;
}