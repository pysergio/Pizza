#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;

template<typename T>
class SliceList{
public:
    SliceList();
    ~SliceList();

    void push_back(T data);

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
public:
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
void SliceList<T>::push_back(T data){
    if (!head){
        head = new Node(data);
    } else {

    }
}