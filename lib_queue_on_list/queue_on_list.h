#pragma once

// Copyright 2026 Danila Puzanov
#include <stdexcept>
#include "../lib_singly_linked_list/singly_linked_list.h"

template <typename T>
class TQueueOnList {
    List<T> _data;
    size_t _size;

public:
    explicit TQueueOnList(size_t size = 1);
    TQueueOnList(const TQueueOnList& other);

    ~TQueueOnList() = default;

    void push(const T& element);
    T pop();

    inline T& front();
    inline size_t size() const noexcept;

    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

template <typename T>
TQueueOnList<T>::TQueueOnList(size_t size) : _data(), _size(size) {}

template <typename T>
TQueueOnList<T>::TQueueOnList(const TQueueOnList& other) : _data(other._data), _size(other._size) {}


template <typename T>
void TQueueOnList<T>::push(const T& element) {
    if (is_full()) {
        throw std::overflow_error("Queue is full, impossible to push");
    }

    _data.push_back(element);
}

template <typename T>
T TQueueOnList<T>::pop() {
    if (is_empty()) {
        throw std::underflow_error("Queue is empty, impossible to pop");
    }

    return _data.pop_front();
}


template <typename T>
inline size_t TQueueOnList<T>::size() const noexcept {
    return _size;
}

template <typename T>
inline T& TQueueOnList<T>::front() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty, impossible to get front");
    }

    return _data.top();
}

template <typename T>
inline bool TQueueOnList<T>::is_empty() const noexcept {
    return _data.is_empty();
}

template <typename T>
inline bool TQueueOnList<T>::is_full() const noexcept {
    return _data.size() == _size;
}
