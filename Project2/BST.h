#pragma once

#include <iostream>
#include "Proj2.h"

using namespace std;
using namespace GPD;

namespace TREE
{

	struct TNode 
	{
	private:
		Item val;
		TNode* left;
		TNode* right;

	public:
		TNode();
		TNode(const Item& _item);
		TNode(const Item& _item, TNode* _left, TNode* _right);
		~TNode();

		bool setVal(const Item& newVal);
		bool setVal(const int& _data, const char& _key);
		bool setData(const int& _data);
		bool setKey(const char& _key);
		bool setLeft(TNode* node);
		bool setRight(TNode* node);


		Item getVal();
		int getData();
		char getKey();
		TNode* getLeft();
		TNode* getRight();


		void inOrder();
		void preOrder();
		void postOrder();

		void operator=(const TNode& o);

		friend class BTree;
		friend class BSTree;
};

	class BTree
	{
	protected:
		TNode* root;

	public:
		BTree();
		BTree(TNode* node);
		BTree(BTree& o);
		virtual ~BTree();

		bool isEmpty();
		void makeEmpty();
		void DeleteSubTree(TNode* _root);
		//insert implementation
	};

	class BSTree : public BTree
	{
		int size;

	public:
		BSTree();
		BSTree(TNode* t_node, int _numOfElements);
		BSTree(BSTree& o);
		virtual ~BSTree();

		int getNumOfObjects() ;
		TNode* find(const int& key) ;
		bool insert(const Item& _item) ; //return false if key data already exists
		bool remove(const int& key) ;
		TNode* max() ;
		TNode* min() ;

		//void operator=(const BSTree& o);
	};



}
