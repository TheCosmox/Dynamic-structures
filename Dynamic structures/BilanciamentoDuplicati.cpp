#include <iostream>
using namespace std;

//Bilanciamento ordinati in modo randomico
//Per farlo diventare alternato aggiungere un contatore che conti partendo da 1 , dispari=left pari=right e incrementare, ovviamente modificare il metodo random.
template<typename T>
class BstNode{

	T key;
	BstNode<T>* parent;
	BstNode<T>* right;
	BstNode<T>* left;
	bool verbose;

	template<typename C>
	friend class BST;

public:

	BstNode(T key, bool verbose = false) : key(key), verbose(verbose){
		parent = nullptr;
		right = nullptr;
		left = nullptr;
	}

	//Getter
	BstNode<T>* getParent(){return this->parent;}
	BstNode<T>* getRight(){return this->right;}
	BstNode<T>* getLeft(){return this->left;}
	T getKey(){return this->key;}

	//Setter
	void setParent(BstNode<T>* parent){this->parent = parent;}
	void setRight(BstNode<T>* right){this->right = right;}
	void setLeft(BstNode<T>* left){this->left = left;}
	void setKey(T key){this->key = key;}

	friend ostream& operator<< (ostream& os, const BstNode<T>& b){

		if(b.verbose){
			os << "BstNode: " << &b << endl;
			os << "Key =" << b.key << endl;
			os << "left->" << b.left << "\t right->" << b.right << "\t parent->" << b.parent << endl;
			return os;
		}

		return os << "Key = " << b.key << endl;
	}
	
};

template <typename T>
class BST {
private:
    BstNode<T>* root;

   
public:


   
    BST() : root(nullptr) {}

    bool isEmpty() {return(!root);}

    void insert(T val) {
         insert(val, root);
    }

     void insert(T val, BstNode<T>*& node) {
        if (node == nullptr) {
            node = new BstNode<T>(val);
        } else if (val < node->key) {
             insert(val, node->left);
        } else if (val > node->key) {
             insert(val, node->right);
        } else {  // Duplicate key
            if (node->left == nullptr) {
                node->left = new BstNode<T>(val);
            } else if (node->right == nullptr) {
                node->right = new BstNode<T>(val);
            } else if (rand() % 2 == 0) {
                 insert(val, node->left);
            } else {
                 insert(val, node->right);
            }
        }
    }

  

   void visit(BstNode<T>* ptr) { cout << *ptr ; }

   void in_order(BstNode<T>* ptr){

			if(!ptr)
				return;

			in_order(ptr->left);
			visit(ptr);
			in_order(ptr->right);
		}

		void in_order(){in_order(root);}

    friend ostream& operator<< (ostream& os, BST<T>& bst){

			if(bst.isEmpty())
				return os << "\nEmpty BST!" << endl;

			os<<endl;
			bst.in_order();
			return os;
		}
};

int main() {
    BST<int> bst_int;
    bst_int.insert(3);
    bst_int.insert(2);
    bst_int.insert(4);
    bst_int.insert(3);
    bst_int.insert(3);
    std::cout << "BST of integers: " << bst_int << std::endl;

    BST<char> bst_char;
    bst_char.insert('c');
    bst_char.insert('b');
    bst_char.insert('d');
    bst_char.insert('c');
    bst_char.insert('c');
    std::cout << "BST of chars: " << bst_char << std::endl;

    return 0;
}
