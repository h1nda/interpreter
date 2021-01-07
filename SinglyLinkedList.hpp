#pragma once //DELETE L8R
#include <iostream>
template <class T>
class SinglyLinkedList {
	struct LinkNode {
		LinkNode(T data, LinkNode* ptr = nullptr);
		T data;
		LinkNode* next;
	};
	LinkNode* head;
	LinkNode* tail;
	void free();
	void copyFrom(const SinglyLinkedList& other);
public:
	class Iterator {
		LinkNode* current;
	public:
		Iterator();
		Iterator(LinkNode* node);
		Iterator(const Iterator& other);

		Iterator& operator=(const Iterator& other);
		Iterator peek() const;
		Iterator& operator++(int);
		bool operator!=(const Iterator& other) const;
		T& operator*() const;
	};
	bool isEmpty();
	void pushBack(T data);
	T popBack();
	Iterator begin() const;
	Iterator end() const;
	SinglyLinkedList();
	~SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList& other);
	SinglyLinkedList& operator=(const SinglyLinkedList& other);
	friend std::ostream& operator<<(std::ostream& out, const SinglyLinkedList& sll) {
		{
			for (SinglyLinkedList<T>::Iterator it = sll.begin(); it != sll.end(); it++)
				out << *it << " ";
			return out;
		}
	}
};

template <class T>
SinglyLinkedList<T>::LinkNode::LinkNode(T data, LinkNode* ptr) : data(data), next(ptr) {};
template <class T>
void SinglyLinkedList<T>::free() {
	LinkNode* it = head;
	while (it) {
		LinkNode* temp = it;
		it = it->next;
		delete temp;
	}
}
template <class T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList& other) {
	LinkNode* it = other.head;
	while (it) {
		pushBack(it->data);
		it = it->next;
	}
}
template <class T>
SinglyLinkedList<T>::Iterator::Iterator() {
	current = nullptr;
}
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(LinkNode* node) {
	current = node;
}
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(const Iterator& other) {
	current = other.current;
}
template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator=(const Iterator& other)
{
	if (this != &other) {
		delete current;
		current = other.current;
	}
	return *this;
}
template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::peek() const {
	return current->next;
}
template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++(int) {
	if (current)
		current = current->next;
	return *this;
}
template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
	return current != other.current;
}
template <class T>
T& SinglyLinkedList<T>::Iterator::operator*() const {
	return current->data;
}
template <class T>
bool SinglyLinkedList<T>::isEmpty() {
	return head == nullptr &&  tail == nullptr;
}
template <class T>
void SinglyLinkedList<T>::pushBack(T data) {
	LinkNode* el = new LinkNode(data);
	if (isEmpty())
	{
		head = el;
		tail = el;
	}
	else {
		tail->next = el;
		tail = el;
	}
}
template <class T>
T SinglyLinkedList<T>::popBack() {
	if (isEmpty())
		throw "Empty";
	else if (head == tail) {
		T data = tail->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return data;
	}
	else
	{
		T data = tail->data;
		//it = begin();
		LinkNode* it_prev = head;
		LinkNode* it = head->next;
		while (it != tail) {
			it = it->next;
			it_prev = it_prev->next;
		}

		delete tail;
		tail = it_prev;
		it_prev->next = nullptr;

		return data;

	}
}
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const {
	return head;
}
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const {
	return nullptr;
}
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
	head = nullptr;
	tail = nullptr;
}
template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
	//std::cout << "calling destructor";
	free();
}
template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other) {
	copyFrom(other);
}
template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
