#include <iostream>
template <class T>
class SinglyLinkedList {
	struct LinkNode {
		LinkNode(T data, LinkNode* ptr = nullptr) : data(data), next(ptr) {};
		T data;
		LinkNode* next;
	};
	LinkNode* head;
	LinkNode* tail;
	void free() {
		LinkNode* it = head;
		while (it) {
			LinkNode* temp = it;
			it = it->next;
			delete temp;
		}
	}
	void copyFrom(const SinglyLinkedList<T>& other) {
		LinkNode* it = head;
		while (it) {
			other.pushBack(it->data);
			it = it->next;
		}
	}
public:
	class Iterator {
	
		LinkNode* current;
	public:
		Iterator(LinkNode* node) {
			current = node;
		}
		Iterator& operator=(const Iterator& other) {
			current = other.current;
		}
		Iterator peek() const {
			return current->next;
		}
		Iterator& operator++(int) {
			if (current)
				current = current->next;
			return *this;
		}
		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}
		T& operator*() const {
			return current->data;
		}
	};
	bool isEmpty() {
		return head == nullptr;
	}
	void pushBack(T data) {
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
	T popBack() {
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
	Iterator begin() const {
		return head;
	}
	Iterator end() const {
		return tail->next;
	}
	SinglyLinkedList() {
		head = tail = nullptr;
	}
	~SinglyLinkedList() {
		std::cout << "calling destructor";
		free();
	}
	SinglyLinkedList(const SinglyLinkedList<T>& other) {
		copyFrom(other);
	}
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other) {
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const SinglyLinkedList<T>& sll) {
		LinkNode* it = sll.head;
		for (Iterator it = sll.begin(); it != sll.end(); it++)
			out << *it << " ";
		return out;
	}
};