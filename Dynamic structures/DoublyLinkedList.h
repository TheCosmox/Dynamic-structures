#include <iostream>
using namespace std;

#include "DoublyNode.h"

//Modificare gli errori di Empty() prima dell'utilizzo


template <typename T>
class DoublyLinkedList {
    private:
    DoublyNode <T> * head;
    DoublyNode <T> * tail;

    public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    DoublyNode <T> * getHead(){return this->head;}
    DoublyNode <T> * getTail(){return this->tail;}


    bool isEmpty(){
        return(!head && ! tail);
    }


    void insertHead(T data){
        if(isEmpty()){
            head= new DoublyNode<T>(data);
            tail=head;
            return;
        }

        DoublyNode <T> * toinsert = new DoublyNode<T>(data);
        toinsert->next=head;
        head->prev=toinsert;
        head=toinsert;
        return;
    }

    void insertTail(T data){
        if(isEmpty()){
            insertHead(data);
            return;
        }

        DoublyNode <T> * toinsert = new DoublyNode<T>(data);
        toinsert->prev=tail;
        tail->next=toinsert;
        tail=toinsert;
        return;
    }


    void removeHead(){
        if(isEmpty()){
            cerr<<"Empty list! ";
            return;
        }
        DoublyNode <T> * ptr = head;
        head=ptr->next;
        head->prev = nullptr;
        return;

    }

     void removeTail(){
        if(isEmpty()){
            cerr<<"Empty list! ";
            return;
        }
        DoublyNode <T> * ptr = tail;
        tail=ptr->prev;
        tail->next=nullptr;
        return;
        
        return;

    }

    void insertAsc(T data){

		if(isEmpty() || data <= head->data)
		{
			insertHead(data);
			return;
		}

		if(data >= tail->data)
		{
			insertTail(data);
			return;
		}

		DoublyNode<T>* cur = head;

		while(cur->next && data >= cur->data)
		{
			if(data < cur->next->data)
				break;

			cur = cur->next;
		}

		DoublyNode<T>* toinsert = new DoublyNode<T>(data);

		toinsert->next = cur->next;
		toinsert->prev = cur;

		cur->next->prev = toinsert;
		cur->next = toinsert;
		return;
	}

    void insertDsc(T data){

		if(isEmpty() || data >= head->data)
		{
			insertHead(data);
			return;
		}

		if(data <= tail->data)
		{
			insertTail(data);
			return;
		}

		DoublyNode<T>* cur = head;

		while(cur->next && data <= cur->data)
		{
			if(data > cur->next->data)
				break;

			cur = cur->next;
		}

		DoublyNode<T>* toinsert = new DoublyNode<T>(data);
		
		toinsert->next = cur->next;
		toinsert->prev = cur;

		cur->next->prev = toinsert;
		cur->next = toinsert;
		return;
	}


	DoublyNode<T>* search(T data){

		if(isEmpty())
			throw out_of_range("Empty list,huh and now what?");

		if(head->data == data)
			return head;

		DoublyNode<T>* cur = head;

		while(cur->next && cur->data != data)
			cur = cur->next;
		
		if(cur->data != data)
		{
			cerr << "Element with key " << data << " not found!" << endl;
			return nullptr;
		}
        cout<<"Element with key " << data << " found! "<<endl;
		return cur;
	}


    
	void removeElement(T data){

		if(isEmpty())
		{
			cerr << "Empty List,what do you want to remove... air?" << endl;
			return;
		}
		
		DoublyNode<T>* toremove = search(data);

		if(!toremove)
			return;

		if(toremove->data == head->data){
			removeHead();
			return;
		}

		if(toremove->data == tail->data){
			removeTail();
			return;
		}

		DoublyNode<T>* cur = head;

		while(cur->next && cur->data != toremove->data)
			cur = cur->next;

		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		delete cur;
	}

    friend ostream& operator<<(ostream& os, const  DoublyLinkedList<T>& lista){
        DoublyNode <T> * ptr= lista.head;
        while(ptr){
            if(ptr!=lista.tail){
                os<<*ptr<<"<->";
            }else{
                os<<*ptr<<"->";
            }
            ptr=ptr->getNext();
        }
        return os;
    }

};