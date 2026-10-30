#pragma once
#include <stdexcept>

template <typename T>
class List {

	struct Node {
		T _data;
		Node* _next;

		Node(const T& data, Node* next = nullptr);
		Node(const Node&) = default;
		Node(Node&&) = default;

		~Node() = default;
	};

	Node* _head;
	Node* _tail;
	size_t _size;

public:
	List();
	List(const List& other);
	List(List&& other) noexcept;

	~List();

	List& operator=(const List& other);
	List& operator=(List&& other) noexcept;

	void push_front(const T& element);
	void push_back(const T& element);
	Node* insert(const T& element, size_t index);
	Node* insert(const T& element, Node* pos);

	T pop_front();
	T pop_back();
	T erase(size_t index);
	T erase(Node* pos);

	Node* find(const T& element) const noexcept;

	inline size_t size() const noexcept;
	inline bool is_empty() const noexcept;

private:
	void clear() noexcept;
};


template <typename T>
List<T>::Node::Node(const T& data, Node* next) {
	_data = data;
	_next = next;
}


template <typename T>
List<T>::List() {
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}

template <typename T>
List<T>::List(const List& other) {
	if (!other._head) {
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
		return;
	}

	_head = new Node(other._head->_data);

	Node* current_this = _head;
	Node* current_other = other._head->_next;

	while (current_other != nullptr) {
		current_this->_next = new Node(current_other->_data);
		current_this = current_this->_next;
		current_other = current_other->_next;
	}

	_tail = current_this;
	_size = other._size;
}

template <typename T>
List<T>::List(List&& other) noexcept {
	_head = other._head;
	_tail = other._tail;
	_size = other._size;

	other._head = nullptr;
	other._tail = nullptr;
	other._size = 0;
}


template <typename T>
List<T>::~List() {
	clear();
}


template <typename T>
List<T>& List<T>::operator=(const List& other) {
	if (this == &other) return *this;

	this->clear();

	if (!other._head) {
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
		return *this;
	}

	_head = new Node(other._head->_data);

	Node* current_this = _head;
	Node* current_other = other._head->_next;

	while (current_other != nullptr) {
		current_this->_next = new Node(current_other->_data);
		current_this = current_this->_next;
		current_other = current_other->_next;
	}

	_tail = current_this;
	_size = other._size;

	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
	if (this == &other) return *this;

	this->clear();

	_head = other._head;
	_tail = other._tail;
	_size = other._size;

	other._head = nullptr;
	other._tail = nullptr;
	other._size = 0;

	return *this;
}

template <typename T>
void List<T>::push_front(const T& element) {
	Node* new_node = new Node(element, _head);

	if (is_empty()) _tail = new_node;

	_head = new_node;

	_size++;
}

template <typename T>
void List<T>::push_back(const T& element) {
	Node* new_node = new Node(element);

	if (is_empty()) {
		_head = new_node;
		_tail = new_node;
		_size++;
		return;
	}

	_tail->_next = new_node;
	_tail = new_node;

	_size++;
}

template <typename T>
typename List<T>::Node* List<T>::insert(const T& element, size_t index) {
	if (index > _size) throw std::out_of_range("Index is out of range");
	if (index == 0) {
		push_front(element);
		return _head;
	}
	if (index == _size) {
		push_back(element);
		return _tail;
	}
	
	Node* current_element = _head;
	for (size_t i = 0; i < index - 1; i++) {
		current_element = current_element->_next;
	}

	Node* new_node = new Node(element, current_element->_next);

	current_element->_next = new_node;

	_size++;
	return new_node;
}

template <typename T>
typename List<T>::Node* List<T>::insert(const T& element, Node* pos) {
	if (pos == nullptr) throw std::invalid_argument("Can't insert before nullptr");
	if (pos == _head) {
		push_front(element);
		return _head;
	}

	Node* current_element = _head;
	while (current_element != nullptr && current_element->_next != pos) {
		current_element = current_element->_next;
	}
	if (current_element == nullptr) throw std::invalid_argument("Invalid pos to insert");

	Node* new_node = new Node(element, pos);
	current_element->_next = new_node;

	_size++;
	return new_node;
}


template <typename T>
T List<T>::pop_front() {
	if (is_empty()) throw std::underflow_error("Can't pop in empty list");

	Node* old_head = _head;
	T popped = old_head->_data;

	_head = _head->_next;
	delete old_head;

	if (_size == 1) _tail = nullptr;

	_size--;
	return popped;
}

template <typename T>
T List<T>::pop_back() {
	if (is_empty()) throw std::underflow_error("Can't pop in empty list");

	T popped = _tail->_data;

	if (_size == 1) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_size--;
		return popped;
	}

	Node* current_element = _head;
	while (current_element->_next != _tail) {
		current_element = current_element->_next;
	}

	_tail = current_element;

	delete current_element->_next;
	current_element->_next = nullptr;

	_size--;
	return popped;
}

template <typename T>
T List<T>::erase(size_t index) {
	if (index >= _size) throw std::out_of_range("Index is out of range");
	if (index == 0) return pop_front();
	if (index == _size - 1) return pop_back();

	Node* current_element = _head;
	for (size_t i = 0; i < index - 1; i++) {
		current_element = current_element->_next;
	}

	Node* to_pop = current_element->_next;
	T popped = to_pop->_data;

	current_element->_next = to_pop->_next;
	delete to_pop;

	_size--;
	return popped;
}

template <typename T>
T List<T>::erase(Node* pos) {
	if (pos == nullptr) throw std::invalid_argument("Can't erase nullptr");
	if (pos == _head) return pop_front();
	if (pos == _tail) return pop_back();

	Node* current_element = _head;
	while (current_element != nullptr && current_element->_next != pos) {
		current_element = current_element->_next;
	}
	if (current_element == nullptr) throw std::invalid_argument("Invalid pos to erase");

	T popped = pos->_data;
	current_element->_next = pos->_next;

	delete pos;

	_size--;
	return popped;
}

template <typename T>
typename List<T>::Node* List<T>::find(const T& element) const noexcept {
	Node* currentElement = _head;

	while (currentElement != nullptr) {
		if (currentElement->_data == element) {
			return currentElement;
		}

		currentElement = currentElement->_next;
	}

	return nullptr;
}


template <typename T>
inline size_t List<T>::size() const noexcept {
	return _size;
}

template <typename T>
inline bool List<T>::is_empty() const noexcept {
	return _size == 0;
}


template <typename T>
void List<T>::clear() noexcept {
	Node* currentElement = _head;
	Node* elementToDelete;

	while (currentElement != nullptr) {
		elementToDelete = currentElement;
		currentElement = currentElement->_next;
		delete elementToDelete;
	}

	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}