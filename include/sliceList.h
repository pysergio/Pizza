#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>
#include <typeinfo>

using namespace std;

template<typename T>
class SliceList{
public:
    SliceList();
    ~SliceList();

    void push_back(T data);
    int getSize(){return Size;}

    T& operator[](const int index);

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
SliceList<T>::SliceList(){
    Size = 0;
    head = nullptr;
}

template<typename T>
SliceList<T>::~SliceList(){
    Size = 0;
    head = nullptr;
}

template<typename T>
T& SliceList<T>::operator[](const int index){
    Node *current = this->head;
    // Use negative index to get revers order index (with love from Python)
    if (index < 0){
        index += Size;
    }

    if (index >= 0 && index < Size){
        for (int i; i < index; i++){
            current = current->pNext;
        }
        return current->data;
    } else {
        cout << "Invalid index. list[index]." << endl;
     }
}

template<typename T>
void SliceList<T>::push_back(T data){
    if (!head){
        head = new Node(data);
    } else {
        Node *current = this->head;

        while (current->pNext){
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }

    Size++;
}