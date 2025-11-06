#pragma once
#include <iostream>
using namespace std;

template <typename T>
	struct Node {
		T data;
		Node* prev;
		Node* next;
		explicit Node() : data(), next(nullptr), prev(nullptr) {}
		Node(const T& data) : data(data), next(nullptr), prev(nullptr)  {}
	};

template <typename T>
class LinkedList {
public:
 	// Behaviors
	void printForward() const {
		Node* currentNode = head;
		while (currentNode) {
			std::cout << currentNode->data << " ";
			currentNode = currentNode->next;
		}
	}
	void printReverse() const {
		Node* currentNode = tail;
		while (currentNode) {
			std::cout << currentNode->data << " ";
			currentNode = currentNode->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}

	Node* getHead() {
		return head;
	}

	const Node* getHead() const {
		return head;
	}

	Node* getTail() {
		return tail;
	}

	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* newNode = new Node(data);
		newNode->next = head;
		if (head) {
			head->prev = newNode;
		}
		head = newNode;
		if (!tail) {
			tail = newNode;
		}
		count++;
	}

	void addTail(const T& data) {
		Node* newNode = new Node(data);
		newNode->prev = tail;
		if (tail) {
			tail->next = newNode;
		}
		tail = newNode;
		if (!head) {
			head = newNode;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (!head) {
			return false;
		}
		Node* tempNode = head;
		head = head->next;
		if (head) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}
		delete tempNode;
		count--;
		return true;
	}
	bool removeTail() {
		if (!tail) {
			return false;
		}
		Node* tempNode = tail;
		tail = tail->prev;
		if (tail) {
			tail->next = nullptr;
		}
		else {
			head = nullptr;
		}
		delete tempNode;
		count--;
		return true;
	}

	void Clear() {
		while(head) {
			removeHead();
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		Clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		Clear();
		Node* currentNode = rhs.head;
		while (currentNode) {
			addTail(currentNode->data);
			currentNode = currentNode->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}

	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
		Node* currentNode = list.head;
		while (currentNode) {
			addTail(currentNode->data);
			currentNode = currentNode->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	~LinkedList() {
		Clear();
	}



private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;


};
