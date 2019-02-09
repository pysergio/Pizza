#include "Error.h"

template<typename T>
class List{
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
        int getSize(){return Size;}

        T& operator[](int index);

    private:
        class Node{
            public:
                Node *pNext;
                T data;
                Node(T data=T(), Node *pNext = nullptr)
                {
                    this->data = data;
                    this->pNext = pNext;
                }
        };
        // "size" is for getting List size without iteration
        int Size;
        Node *head;
};
template<typename T>
List<T>::List(){
    Size = 0;
    head = nullptr;
}
template<typename T>
List<T>::~List(){
    clear();
}
template<typename T>
T& List<T>::operator[](int index){
    Node *current = head;
    // Use negative index to get revers order index (with love from Python)
    if (index < 0 && (index + Size) > 0){
        index += Size;
    }

    if (index >= 0 && index < Size){
        for (int i = 0; i < index; i++){
            current = current->pNext;
        }
        return current->data;
    } else {
        cout << "Invalid index. list[" << index << "]" << endl;
        exit(1);
     }
}
template<typename T>
void List<T>::push_back(T data){
    if (!head){
        head = new Node(data);
    } else {
        Node *current = head;

        while (current->pNext){
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    Size++;
}
template<typename T>
void List<T>::push_front(T data){
    if (!head){
        head = new Node(data);
    } else {
        Node *current = head;
        head = new Node(data);
        head->pNext = current;
    }
    Size++;
}
template<typename T>
void List<T>::del_front(){
    if (head){
        Node *temp = head;
        head = head->pNext;
        delete temp;
        
        Size--;
    }
}
template<typename T>
void List<T>::del_back(){
    if (!head){
        Node *current = head;

        for (int i = 1; i < Size; i++){
            current = current->pNext;
        }
        delete current->pNext;
        current->pNext = nullptr;
    
        Size--;
    }
}
template<typename T>
void List<T>::clear(){
    while (Size){
        del_front();
    }
}
template<typename T>
void List<T>::removeAt(int index){
    // Use negative index to get revers order index (with love from Python)
    if (index < 0 && (index + Size) > 0){
        index += Size;
    }

    if (index > 0 && index < Size - 1){
        Node *current = head;
        for (int i = 0; i < index; i++){
            current = current->pNext;
        }
        Node *temp = current->pNext;
        current->pNext = current->pNext->pNext;
        delete temp;

        Size--;
    }
    else if (index == 0){
        del_front();
    }
    else if (index == Size - 1){
        del_back();
    } else {
        cout << "Invalid index. list[" << index << "]" << endl;
        exit(1);
    }
}
template<typename T>
void List<T>::insertAt(T data, int index){
    // Use negative index to get revers order index (with love from Python)
    if (index < 0 && (index + Size) > 0){
        index += Size;
    }

    if (index > 0 && index < Size - 1){
        cout << index << endl;
        Node *current = head;

        for (int i = 1; i < index; i++){
            current = current->pNext;
        }
        cout << current << endl;
        Node *temp = current->pNext;
        current->pNext = new Node(data);
        current = current->pNext;
        current->pNext = temp;
        
        Size++;
    }
    else if (index == 0){
        del_front();
    }
    else if (index == Size - 1){
        del_back();
    } else {
        cout << "Invalid index. list[" << index << "]" << endl;
        exit(1);
    }
}