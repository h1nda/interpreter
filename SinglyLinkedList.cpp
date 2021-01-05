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
	void copyFrom(const SinglyLinkedList& other) {
		LinkNode* it = head;
		while (it) {
			other.pushBack(it->data);
			it = it->next;
		}
	}
public:
	bool isEmpty() {
		return head == tail == nullptr;
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

			LinkNode* prev = head;
			LinkNode* it = head->next;
			while (it != tail) {
				prev = prev->next;
				it = it->next;
			}
			delete tail;
			tail = prev;
			prev->next = nullptr;
			
			return data;

		}
	}
	LinkNode* start() {
		return head;
	}
	LinkNode* end() {
		return tail;
	}
	SinglyLinkedList() {
		head = tail = nullptr;
	}
	SinglyLinkedList(const SinglyLinkedList& other) {
		copyFrom(other);
	}
	SinglyLinkedList& operator=(const SinglyLinkedList& other) {
		if (this != &other)
		{
			free();
			copyFrom(other);
		}
		return *this;
	}
};