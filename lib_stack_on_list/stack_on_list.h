#pragma once

// Copyright 2026 Danila Puzanov
#include <stdexcept>
#include "../lib_singly_linked_list/singly_linked_list.h"

template <typename T>
class TStackOnList {
    List<T> _data;
    size_t _size;

public:
    explicit TStackOnList(size_t size = 1);
    TStackOnList(const TStackOnList& other);

    ~TStackOnList() = default;

    void push(const T& elem);
    T pop();

    inline T& top() const;
    inline size_t size() const noexcept;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

template <typename T>
TStackOnList<T>::TStackOnList(size_t size) : _data(), _size(size) {}

template <typename T>
TStackOnList<T>::TStackOnList(const TStackOnList& other) : _data(other._data), _size(other._size) {}


template <typename T>
void TStackOnList<T>::push(const T& elem) {
    if (is_full()) {
        throw std::overflow_error("Stack is full, impossible to push");
    }

    _data.push_front(elem);
}

template <typename T>
T TStackOnList<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Stack is empty, impossible to pop");
    }

    return _data.pop_front();
}


template <typename T>
inline T& TStackOnList<T>::top() const {
    if (is_empty()) {
        throw std::logic_error("Stack is empty, impossible to get top");
    }

    return _data.top();
}

template <typename T>
inline size_t TStackOnList<T>::size() const noexcept {
    return _size;
}


template <typename T>
inline bool TStackOnList<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template <typename T>
inline bool TStackOnList<T>::is_full() const noexcept {
    return _size == _data.size();
}