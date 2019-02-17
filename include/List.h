#include "Error.h"

template<typename T>
class List {
public:
	List();
	~List();

	void push_back(T data);
	void push_front(T data);
	void del_front();
	void del_back();
	void clear();
	void removeAt(int index);
	void insertAt(T data, int index);
	int getSize();

	T& operator[](int index);

private:
	class Node {
	public:
		Node *pPrev;
		T data;
		Node(T data = T(), Node *pPrev = nullptr)
		{
			this->data = data;
			this->pPrev = pPrev;
		}
	};
	// "size" is for getting List size without iteration
	int Size;
	Node* head;
};
template<typename T>
List<T>::List() {
	Size = 0;
	head = nullptr;
}
template<typename T>
List<T>::~List() {
	clear();
}
template<typename T>
T& List<T>::operator[](int index) {
	Node *current = head;
	// Use negative index to get revers order index (with love from Python)
	if (index < 0 && (index + Size) > 0) {
		index = -index - 1;
	}
	else {
		index = Size - index - 1;
	}

	if (index >= 0 && index < Size) {
		for (int i = 0; i < index; i++) {
			current = current->pPrev;
		}
		return current->data;
	}
	else {
		cout << "Invalid index. list[" << index << "]" << endl;
		exit(1);
	}
}
template<typename T>
void List<T>::push_front(T data) {
	if (!head) {
		head = new Node(data);
	}
	else {
		Node *current = head;

		while (current->pPrev) {
			current = current->pPrev;
		}
		current->pPrev = new Node(data);
	}
	Size++;
}
template<typename T>
void List<T>::push_back(T data) {
	if (head)
		head = new Node(data, head);
	else
		head = new Node(data);
	Size++;
}
template<typename T>
void List<T>::del_back() {
	if (head) {
		Node *temp = head;
		head = head->pPrev;
		
		temp->pPrev = nullptr;
		delete temp;

		Size--;
	}
}
template<typename T>
void List<T>::del_front() {
	if (head) {
		Node *current = head;
		if (Size == 1) {
			delete current;
			current = nullptr;
		}
		else {
			for (int i = 2; i < Size; i++) {
				current = current->pPrev;
			}
			delete current->pPrev;
			current->pPrev = nullptr;
		}
		Size--;
	}
}
template<typename T>
void List<T>::clear() {
	while (Size) {
		del_front();
	}
}
template<typename T>
void List<T>::removeAt(int index) {
	// Use negative index to get revers order index (with love from Python)
	if (index >= 0 && (index - Size) <= 0) {
		index += Size;
	}

	if (index > 0 && index < Size - 1) {
		Node *current = head;
		for (int i = 0; i < index; i++) {
			current = current->pPrev;
		}
		Node *temp = current->pPrev;
		current->pPrev = current->pPrev->pPrev;
		delete temp;

		Size--;
	}
	else if (index == 0) {
		del_front();
	}
	else if (index == Size - 1) {
		del_back();
	}
	else {
		cout << "Invalid index. list[" << index << "]" << endl;
		exit(1);
	}
}
template<typename T>
void List<T>::insertAt(T data, int index) {
	// Use negative index to get revers order index (with love from Python)
	if (index < 0 && (index + Size) > 0) {
		index += Size;
	}

	if (index > 0 && index < Size - 1) {
		cout << index << endl;
		Node *current = head;

		for (int i = 1; i < index; i++) {
			current = current->pPrev;
		}
		cout << current << endl;
		Node *temp = current->pPrev;
		current->pPrev = new Node(data);
		current = current->pPrev;
		current->pPrev = temp;

		Size++;
	}
	else if (index == 0) {
		del_front();
	}
	else if (index == Size - 1) {
		del_back();
	}
	else {
		cout << "Invalid index. list[" << index << "]" << endl;
		exit(1);
	}
}
template<typename T>
int List<T>::getSize() {
	if (!head)
		return 0;
	else
		return Size;
}