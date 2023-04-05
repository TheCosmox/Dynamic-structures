#include <iostream>
using namespace std;

#include "BstNode.h"

template <typename T>
class BinarySearchTree
{

	BstNode<T> *root;

public:
	BinarySearchTree() { root = nullptr; }

	BstNode<T> *getRoot() { return this->root; }

	bool isEmpty() { return root == nullptr; }

	void insert(T data)
	{

		if (isEmpty())
		{
			root = new BstNode<T>(data);
			return;
		}

		insert(root, data);
	}

	void insert(BstNode<T> *ptr, T data)
	{

		if (!ptr->left && data <= ptr->data)
		{
			ptr->left = new BstNode<T>(data);
			ptr->left->setParent(ptr);
			return;
		}

		if (!ptr->right && data > ptr->data)
		{
			ptr->right = new BstNode<T>(data);
			ptr->right->setParent(ptr);
			return;
		}

		if (data <= ptr->data)
			insert(ptr->left, data);

		else
			insert(ptr->right, data);
	}

	void visit(BstNode<T> *ptr) { cout << *ptr << endl; }

	void pre_order(BstNode<T> *ptr)
	{

		if (!ptr)
			return;

		visit(ptr);
		pre_order(ptr->left);
		pre_order(ptr->right);
	}

	void pre_order() { pre_order(root); }

	void in_order(BstNode<T> *ptr)
	{

		if (!ptr)
			return;

		in_order(ptr->left);
		visit(ptr);
		in_order(ptr->right);
	}

	void in_order() { in_order(root); }

	void post_order(BstNode<T> *ptr)
	{

		if (!ptr)
			return;

		post_order(ptr->left);
		post_order(ptr->right);
		visit(ptr);
	}

	void post_order() { post_order(root); }

	BstNode<T> *max() { return max(root); }

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

	BstNode<T> *min(BstNode<T> *from)
	{

		if (isEmpty())
			throw out_of_range("Empty bst...");

		BstNode<T> *ptr = from;
		while (ptr->left)
			ptr = ptr->left;

		return ptr;
	}

	BstNode<T> *successor(T data)
	{

		BstNode<T> *ptr = search(data);
		if (!ptr || ptr == max())
			throw out_of_range("...successor doesn't exist...");

		return successor(ptr);
	}

	BstNode<T> *successor(BstNode<T> *x)
	{

		if (isEmpty())
			return nullptr;

		if (x->right)
			return min(x->right);

		BstNode<T> *y = x->parent;
		while (x && x == y->right)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	BstNode<T> *predecessor(T data)
	{

		BstNode<T> *ptr = search(data);
		if (!ptr || ptr == min())
			throw out_of_range("...predecessor doesn't exist...");

		return predecessor(ptr);
	}

	BstNode<T> *predecessor(BstNode<T> *x)
	{

		if (isEmpty())
			return nullptr;

		if (x->left)
			return max(x->left);

		BstNode<T> *y = x->parent;
		while (x && x == y->left)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

	BstNode<T> *search(T data)
	{
		if (isEmpty())
			throw out_of_range("Empty bst...");

		return search(root, data);
	}

	BstNode<T> *search(BstNode<T> *ptr, T data)
	{

		if (!ptr)
			return nullptr;

		if (ptr->data == data)
			return ptr;

		if (data <= ptr->data)
			return search(ptr->left, data);

		else
			return search(ptr->right, data);
	}

	int from_successor(T data)
	{

		int count = 0;
		BstNode<T> *ptr = search(data);

		if (!ptr || ptr == max())
			throw out_of_range("...successor doesn't exist...");

		// node has a right subtree
		if (ptr->right)
		{
			ptr = ptr->right;
			count++;

			while (ptr->left)
			{
				ptr = ptr->left;
				count++;
			}

			return count;
		}

		// node is a leaf

		BstNode<T> *y = ptr->parent;
		count++;

		while (ptr && ptr == y->right)
		{
			ptr = ptr->parent;
			y = y->parent;
			count++;
		}

		return count;
	}

	int from_root(BstNode<T> *nodo_h, BstNode<T> *partenza)
	{

		if (partenza->data == nodo_h->data)
			return 0;

		BstNode<T> *tmp = partenza;
		int counter = 0;

		while (tmp && tmp->data != nodo_h->data)
		{
			if (nodo_h->data > tmp->data)
				tmp = tmp->right;
			else
				tmp = tmp->left;

			counter++;
		}

		if (!tmp)
			return -1;
		else
			return counter;
	}

	int between_nodes(T k, T h)
	{

		BstNode<T> *nodo_k = search(k);
		BstNode<T> *nodo_h = search(h);

		int counter = 0;

		if (!nodo_k || !nodo_h)
			throw out_of_range("Wrong keys!");

		if (k <= h)
		{
			BstNode<T> *tmp = nodo_k;
			bool flag = true;

			while (tmp && flag)
			{
				int distance = from_root(nodo_h, tmp);

				if (distance == 0)
					flag = false;

				else if (distance == -1)
				{
					tmp = tmp->parent;
					counter++;
				}
				else
				{
					counter += distance;
					flag = false;
				}
			}

			return counter;
		}
		else
			return between_nodes(h, k);
	}

	BstNode<T> *remove(BstNode<T> *node)
	{

		// node is a leaf
		if (!node->left && !node->right)
		{
			if (node == node->parent->left)
				node->parent->left = nullptr;

			else if (node == node->parent->right)
				node->parent->right = nullptr;

			return node;
		}

		// node has only 1 child
		if (!node->right && node->left)
		{
			node->left->setParent(node->parent);

			if (node == node->parent->left)
				node->parent->left = node->left;

			else if (node == node->parent->right)
				node->parent->right = node->left;

			return node;
		}

		if (!node->left && node->right)
		{
			node->right->setParent(node->parent);

			if (node == node->parent->left)
				node->parent->left = node->right;

			else if (node == node->parent->right)
				node->parent->right = node->right;

			return node;
		}

		return nullptr;
	}

	BstNode<T> *remove(T data)
	{

		if (isEmpty())
			return nullptr;

		BstNode<T> *node = search(data);

		if (!node)
			return nullptr;

		BstNode<T> *toDelete = remove(node);

		if (toDelete != nullptr)
			return toDelete;

		// Node has 2 childrens

		BstNode<T> *next = successor(node);

		T swap = node->data;
		node->data = next->data;
		next->data = swap;

		toDelete = remove(next);
		return toDelete;
	}

	void cancel_below(BstNode<T> *ptr, T data)
	{
		if (ptr->data <= data)
			remove(ptr->data);
	}

	void remove_below(BstNode<T> *ptr, T data)
	{
		if (!ptr)
			return;

		remove_below(ptr->right, data);
		cancel_below(ptr, data);
		remove_below(ptr->left, data);
	}

	void remove_below(T data) { remove_below(root, data); }

	void cancel_above(BstNode<T> *ptr, T data)
	{
		if (ptr->data >= data)
			remove(ptr->data);
	}

	void remove_above(BstNode<T> *ptr, T data)
	{
		if (!ptr)
			return;

		remove_above(ptr->right, data);
		cancel_above(ptr, data);
		remove_above(ptr->left, data);
	}

	void remove_above(T data) { remove_above(root, data); }

	void cancel_equal(BstNode<T> *ptr, T data)
	{
		if (ptr->data == data)
			remove(ptr->data);
	}

	void remove_equal(BstNode<T> *ptr, T data)
	{

		if (!ptr)
			return;

		remove_equal(ptr->right, data);
		cancel_equal(ptr, data);
		remove_equal(ptr->left, data);
	}

	void remove_equal(T data) { remove_equal(root, data); }

	friend ostream &operator<<(ostream &os, BinarySearchTree<T> &bst)
	{

		if (bst.isEmpty())
			return os << "\nThe bst is empty!" << endl;

		bst.in_order();
		return os;
	}
};