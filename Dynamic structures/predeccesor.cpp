#include <iostream>
using namespace std;

// creating the node of my BinarySearchTree
template <typename T>
class BstNode
{
    T key;
    BstNode<T> *parent;
    BstNode<T> *right;
    BstNode<T> *left;
    bool verbose;

    template <typename C>
    friend class BinarySearchTree;

public:
    BstNode(T key, bool verbose = false) : key(key), verbose(verbose)
    {
        parent = nullptr;
        right = nullptr;
        left = nullptr;
    }

    // Creating getter methods
    BstNode<T> *getParent() { return this->parent; }
    BstNode<T> *getRight() { return this->right; }
    BstNode<T> *getLeft() { return this->left; }
    T getKey() { return this->key; }

    // Creating Setter  methods
    void setParent(BstNode<T> *parent) { this->parent = parent; }
    void setRight(BstNode<T> *right) { this->right = right; }
    void setLeft(BstNode<T> *left) { this->left = left; }
    void setKey(T key) { this->key = key; }

    // overloading operator<< so I can print node element
    friend ostream &operator<<(ostream &os, const BstNode<T> &b)
    {

        if (b.verbose)
        {
            os << "BstNode: " << &b << endl;
            os << "Key =" << b.key;
            os << "left->" << b.left << "\t right->" << b.right << "\t parent->" << b.parent << endl;
            return os;
        }

        return os << "Key = " << b.key;
    }
};
// Creating the binary search tree
template <typename T>
class BinarySearchTree
{

    BstNode<T> *root;

public:
    BinarySearchTree() { root = nullptr; }

    BstNode<T> *getRoot() { return this->root; }

    bool isEmpty() { return root == nullptr; }

    void insert(T key)
    {

        if (isEmpty())
        {
            root = new BstNode<T>(key);
            return;
        }

        insert(root, key);
    }
    // Creating insert method
    void insert(BstNode<T> *ptr, T key)
    {

        if (!ptr->left && key <= ptr->key)
        {
            ptr->left = new BstNode<T>(key);
            ptr->left->setParent(ptr);
            return;
        }

        if (!ptr->right && key > ptr->key)
        {
            ptr->right = new BstNode<T>(key);
            ptr->right->setParent(ptr);
            return;
        }

        if (key <= ptr->key)
            insert(ptr->left, key);

        else
            insert(ptr->right, key);
    }

    void visit(BstNode<T> *ptr) { cout << "\n"
                                       << *ptr; }

    // Creating the pre_order, it's going to print the BinarySearchTree in a specific order
    void pre_order(BstNode<T> *ptr)
    {

        if (!ptr)
            return;

        visit(ptr);
        pre_order(ptr->left);
        pre_order(ptr->right);
    }

    void pre_order() { pre_order(root); }

    BstNode<T> *search(T key)
    {
        if (isEmpty())
            throw out_of_range("Empty bst...");

        return search(root, key);
    }
    // Creating the search method, It's going to search the BinarySearchTree for an element
    BstNode<T> *search(BstNode<T> *ptr, T key)
    {

        if (!ptr)
            return nullptr;

        if (ptr->key == key)
            return ptr;

        if (key <= ptr->key)
            return search(ptr->left, key);

        else
            return search(ptr->right, key);
    }

    BstNode<T> *max() { return max(root); }
    // Creating the max method,It's going to give me the max element of the BinarySearchTree
    BstNode<T> *max(BstNode<T> *from)
    {

        if (isEmpty())
            throw out_of_range("Empty bst...");

        BstNode<T> *ptr = from;
        while (ptr->right)
            ptr = ptr->right;

        return ptr;
    }

    BstNode<T> *min() { return min(root); }
    // Creating the min method,It's going to give me the min element of the BinarySearchTree
    BstNode<T> *min(BstNode<T> *from)
    {

        if (isEmpty())
            throw out_of_range("Empty bst...");

        BstNode<T> *ptr = from;
        while (ptr->left)
            ptr = ptr->left;

        return ptr;
    }

   
   
        BstNode<T>* predecessor(T key){

            BstNode<T>* ptr = search(key);
            if(!ptr || ptr == min())
                return nullptr;

            return predecessor(ptr);
        }

		BstNode<T>* predecessor(BstNode<T>* x){

			if(isEmpty())
				return nullptr;

			if(x->left)
				return max(x->left);

			BstNode<T>* y = x->parent;
			while(x && x == y->left)  
			{
				x = y;
				y = y->parent;
			}
			
			return y;
		}


    // Overloading operator<< to print the BinarySearchTree
    friend ostream &operator<<(ostream &os, BinarySearchTree<T> &bst)
    {

        if (bst.isEmpty())
            return os << "\nEmpty BST!" << endl;

        bst.pre_order();
        return os;
    }
};

int main()
{
    // Creating an integer BinarySearchTree
    BinarySearchTree<int> int_bst;
    int_bst.insert(12);
    int_bst.insert(23);
    int_bst.insert(47);
    int_bst.insert(14);
    int_bst.insert(41);
    int_bst.insert(6);
    int_bst.insert(9);
    int_bst.insert(11);
    // Output BinarySearchTree
    cout << int_bst << endl;

    // Find the predecessor between 3 and 5 in the integer BST
        BstNode<int> *int_predecessor = int_bst.predecessor(47);
        if (int_predecessor == nullptr)
        {
            cout << "predecessor of given element is null";
        }
        else
        {
            cout << "The predecessor is: " << int_predecessor->getKey() << endl;
        }
        // Creating an character BinarySearchTree
        BinarySearchTree<char> char_bst;
        char_bst.insert('g');
        char_bst.insert('e');
        char_bst.insert('k');
        char_bst.insert('i');
        char_bst.insert('b');
        char_bst.insert('f');
        char_bst.insert('h');
        char_bst.insert('j');

    // Output BinarySearchTree
    cout << char_bst << endl;

    // Find the predecessor between 'e' and 'g' in the character BST
    BstNode<char> *char_predecessor = char_bst.predecessor('h');
    if (char_predecessor == nullptr)
    {
        cout << "predecessor of given element is null";
    }
    else
    {
        cout << "The predecessor is: " << char_predecessor->getKey() << endl;
    }

    cout << endl;

    return 0;
}