#include <iostream>
using namespace std;



template <typename T>
class DoublyNode {
    private:
    DoublyNode <T> * next;
    DoublyNode <T> * prev;
    T data;

    template <typename W>
    friend class DoublyLinkedList;
    
    public:

    DoublyNode(T data) : next(nullptr), prev(nullptr), data(data) {}


    DoublyNode<T> * getNext(){return this->next;}
    T getData(){return this->data;}

    friend ostream& operator<<(ostream& os,const DoublyNode<T>& n){
        os<< n.data;
        return os;
    }

};