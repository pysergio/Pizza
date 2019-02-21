#include "Error.h"

template<typename T>
class List {
public:
	List();

	void	pushBack(T data);
	void	delBack();
	int		getSize();
	T&		getBack();
	T&		operator[](int index);

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
void List<T>::pushBack(T data) {
	head = new Node(data, head);
	Size++;
}
template<typename T>
void List<T>::delBack() {
	if (head) {
		Node *temp = head;
		head = head->pPrev;

		temp->pPrev = nullptr;
		delete temp->data;
		delete temp;
		Size--;
	}
}
template<typename T>
int List<T>::getSize() {
	return this->Size;
}
template<typename T>
T& List<T>::operator[](int index) {
	Node *current = head;
	// Use negative index to get revers order index (with love from Python)
	if (index < 0 && -index <= this->Size) {
		while (++index)
			current = current->pPrev;
		return current->data;
	}
	else if (index >= 0 && index < this->Size) {
		while (++index < this->Size)
			current = current->pPrev;
		return current->data;
	}
	else {
		cout << "Invalid index. list[" << index << "]" << endl;
		exit(1);
	}
}
template<typename T>
T& List<T>::getBack() {
	return this->head->data;
}
