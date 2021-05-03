#pragma once
#include <iostream>
#include "Proj2.h"
#include "BST.h"

using namespace std;
using namespace GPD;
using namespace TREE;

namespace heap
{
	class Node
	{
	private:
		int frequency;
		char data;
		Node* left;
		Node* right;

	public:

		Node();
		Node(char _char, int freq);
		Node(char _char, int freq, Node* _left, Node* _right);
		~Node();

		bool setFrequency(const int& _freq);
		bool setData(const char& _data);
		bool setLeftChild(Node* node);
		bool setRightChild(Node* node);

		int getFrequency();
		char getData();
		Node* getLeftChild();
		Node* getRightChild();
		


		void operator=(const Node& o);

		friend class Heap;
	};

	class Heap
	{
	private:
		Node** data;
		int maxSize;
		int heapSize;

	public:
		Heap(const int& size);
		~Heap();

		void makeEmptyHeap(const int& size);
		bool builedHeap(Node** _data, const int& size);
		void resize(const int& newSize);
		bool isFull();
		bool isEmpty();
		void insert(Node* item);
		void insert(TNode* item);
		Node min();
		Node* deleteMin();

		const int& leftChild(const int& index);
		const int& rightChild(const int& index);
		const int& parent(const int& index);
		void fixHeap(const int& index);
	};
}