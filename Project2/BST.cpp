#pragma once
#include "BST.h"

namespace TREE
{
/********************************** TNode Methods ******************************************/
	
	TNode::TNode() :left(NULL), right(NULL) {}

	TNode::TNode(const Item& _item) : TNode(_item, NULL, NULL) {}
	
	TNode::TNode(const Item& _item, TNode* _left, TNode* _right)
		: val(_item), left(_left), right(_right) {}

	TNode::~TNode()
	{
		if (left != NULL)
			delete[] left;
		if (right != NULL)
			delete[] right;
	}

	bool TNode::setVal(const Item& newVal)
	{
		val = newVal;
		return true;
	}

	bool TNode::setVal(const int& _data, const char& _key)
	{
		return (setData(_data) && setKey(_key));
	}

	bool TNode::setData(const int& _data)
	{
		val.data = _data;
		return true;
	}

	bool TNode::setKey(const char& _key)
	{
		val.key = _key;
		return true;
	}

	bool TNode::setLeft(TNode* node)
	{
		left = node;
		return true;
	}

	bool TNode::setRight(TNode* node)
	{
		right = node;
		return true;
	}

	Item TNode::getVal()
	{
		return val;
	}

	int TNode::getData()
	{
		return val.data;
	}

	char TNode::getKey()
	{
		return val.key;
	}

	TNode* TNode::getLeft()
	{
		return left;
	}

	TNode* TNode::getRight()
	{
		return right;
	}


	void TNode::inOrder()
	{
		if (left != NULL)
			left->inOrder();

		cout << val;

		if (right != NULL)
			right->inOrder();
	}

	void TNode::preOrder()
	{
		cout << val;

		if (left != NULL)
			left->preOrder();

		if (right != NULL)
			right->preOrder();
	}

	void TNode::postOrder()
	{
		if (left != NULL)
			left->postOrder();

		if (right != NULL)
			right->postOrder();

		cout << val;
	}

	void TNode::operator=(const TNode& o)
	{
		val = o.val;
		left = o.left;
		right = o.right;
	}



/********************************** BTree Methods ******************************************/

	BTree::BTree() : BTree(NULL) {}

	BTree::BTree(TNode* t_node) : root(t_node) {}

	BTree::BTree(BTree& o) : root(o.root) {}

	BTree::~BTree()
	{
		makeEmpty();
	}

	void BTree::makeEmpty()
	{
		DeleteSubTree(root);
		root = NULL;
	}

	void BTree::DeleteSubTree(TNode* _root)
	{
		if (_root != NULL)
		{
			DeleteSubTree(_root->left);
			_root->left = NULL;
			DeleteSubTree(_root->right);
			_root->right = NULL;
			delete _root;

		}
	}

	bool BTree::isEmpty() 
	{
		return (root == NULL);
	}


	/********************************** BTree Methods ******************************************/



	BSTree::BSTree() : BTree(NULL) { size = 0; }

	BSTree::BSTree(TNode* t_node, int _numOfElements) : BTree(t_node) { size = _numOfElements; }

	BSTree::BSTree(BSTree& o) : BTree(o) { size = o.size; }

	BSTree::~BSTree() {}

	int BSTree::getNumOfObjects() 
	{
		return size;
	}

	TNode* BSTree::find(const int& key) 
	{
		TNode* temp = root;

		while (temp != NULL)
		{
			if (temp->val.key == key)
				return temp;
			else if (temp->val.key < key)
				temp = temp->right;
			else
				temp = temp->left;
		}
		return temp;
	}

	bool BSTree::insert(const Item& _item) 
	{
		 TNode* temp = find(_item.key);
		if (temp != NULL)
		{
			temp->val.data++;
			return false;
		}

		temp = root;
		TNode* parent = NULL;
		TNode* newNode = new TNode(_item);

		while (temp != NULL)
		{
			parent = temp;
			if (_item.key > temp->val.key)
				temp = temp->right;
			else
				temp = temp->left;
		}

		if (isEmpty())
			root = newNode;
		else if (_item.key > parent->val.key)
			parent->right = newNode;
		else
			parent->left = newNode;

		size++;
		return true;
	}

	bool BSTree::remove(const int& key)
	{
		if (isEmpty())
			return false;


		TNode* toDelete = root;
		TNode* parent = NULL;
		bool leftChild;


		while ((toDelete != NULL) && (toDelete->val.key != key))
		{
			parent = toDelete;
			if (key > toDelete->val.key)
			{
				toDelete = toDelete->right;
				leftChild = false;
			}
			else
			{
				toDelete = toDelete->left;
				leftChild = true;
			}
		}

		if (toDelete == NULL)
			return false;

		if (toDelete->left == NULL && toDelete->right == NULL) //0 children exists
		{
			delete toDelete;
			if (parent != NULL) //toDelete is not root
			{
				if (leftChild)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
		}

		else if (toDelete->left != NULL && toDelete->right == NULL)//only left child exist
		{
			if (parent != NULL) //toDelete is not root
			{
				if (leftChild)
					parent->left = toDelete->left;

				else
					parent->right = toDelete->left;
			}

			else //toDelete is root
			{
				root = toDelete->left;
			}

			toDelete->left = NULL;
			delete toDelete;
		}

		else if (toDelete->left == NULL && toDelete->right != NULL)//only right child exist
		{
			if (parent != NULL) //toDelete is not root
			{
				if (leftChild)
					parent->left = toDelete->right;

				else
					parent->right = toDelete->right;
			}
			else //toDelete is root
			{
				root = toDelete->right;
			}

			toDelete->right = NULL;
			delete toDelete;
		}

		else //both childern exists
		{
			TNode* temp = toDelete->left;
			TNode* p_temp = toDelete;
			while (temp->right != NULL)
			{
				p_temp = temp;
				temp = temp->right;
			}

			toDelete->val = temp->val;
			p_temp->left = temp->left;
			temp->left = NULL;
			delete temp;
		}
		size--;
		return true;
	}

	TNode* BSTree::max()
	{
		if (isEmpty())
		{
			return NULL;
		}

		TNode* temp = root;

		while (temp->right != NULL)
			temp = temp->right;
		return temp;
	}

	TNode* BSTree::min()
	{
		if (isEmpty())
		{
			return NULL;
		}

		TNode* temp = root;

		while (temp->left != NULL)
			temp = temp->left;
		return temp;
	}

}

