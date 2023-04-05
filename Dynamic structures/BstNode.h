
#include <iostream>
using namespace std;

template<typename T>
class BstNode{

	T data;
	BstNode<T>* parent;
	BstNode<T>* right;
	BstNode<T>* left;
	bool verbose;

	template<typename C>
	friend class BinarySearchTree;

public:

	BstNode(T data, bool verbose = false) : data(data), verbose(verbose){
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}


	BstNode<T>* getParent(){return this->parent;}
	BstNode<T>* getRight(){return this->right;}
	BstNode<T>* getLeft(){return this->left;}
	T getdata(){return this->data;}

	
	void setParent(BstNode<T>* parent){this->parent = parent;}
	void setRight(BstNode<T>* right){this->right = right;}
	void setLeft(BstNode<T>* left){this->left = left;}
	void setdata(T data){this->data = data;}

	friend ostream& operator<< (ostream& os, const BstNode<T>& b){

		if(b.verbose){
			os << "BstNode: " << &b << endl;
			os << "Key =" << b.data << endl;
			os << "left->" << b.left << "\t right->" << b.right << "\t parent->" << b.parent << endl;
			return os;
		}

		return os << "key = " << b.data ;
	}
	
};
