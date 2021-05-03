#pragma once
#include "Heap.h"

namespace heap
{
	/********************************** Node Methods ******************************************/

	Node::Node() : left(NULL), right(NULL) {}

	Node::Node(char _char, int freq) : Node(_char, freq, NULL, NULL) {}

	Node::Node(char _char, int freq, Node* _left, Node* _right) : data(_char),
		frequency(freq), left(_left), right(_right) {}

	Node::~Node() 
	{ 
		delete left; 
		delete right; 
	}

	bool Node::setFrequency(const int& _freq)
	{
		frequency = _freq;
		return true;
	}

	bool Node::setData(const char& _data)
	{
		data = _data;
		return true;
	}

	bool Node::setLeftChild(Node* node)
	{
		left = node;
		return true;
	}

	bool Node::setRightChild(Node* node)
	{
		right = node;
		return true;
	}

	int Node::getFrequency()
	{
		return frequency;
	}
		
	char Node::getData()
	{
		return data;
	}

	Node* Node::getLeftChild()
	{
		return left;
	}

	Node* Node::getRightChild()
	{
		return right;
	}

	void Node::operator=(const Node& o)
	{
		frequency = o.frequency;
		data = o.data;
		left = o.left;
		right = o.right;
	}

	/********************************** Heap Methods ******************************************/
	Heap::Heap(const int& size)
	{
		makeEmptyHeap(size);
	}

	Heap::~Heap()
	{
		delete[] data;
	}

	void Heap::makeEmptyHeap(const int& size)
	{
		data = new Node*[size];
		maxSize = size;
		heapSize = 0;
	}

	bool Heap::builedHeap(Node** _data, const int& size)
	{
		data = _data;
		heapSize = maxSize = size;

		for (int i = parent(heapSize); i >= 1; i--)
			fixHeap(i);
		return true;
	}

	void Heap::resize(const int& newSize)
	{
		Node** temp = new Node*[newSize];
		maxSize = newSize;

		for (int i = 0; i < heapSize; i++)
			*temp[i] = *data[i];

		delete[] data;
		data = temp;
	}

	bool Heap::isFull()
	{
		return (heapSize == maxSize);
	}

	bool Heap::isEmpty()
	{
		return (heapSize == 0);
	}

	void Heap::insert(Node* item)
	{
		if (isFull())
			resize(maxSize * 2);
		
		data[heapSize] = item;
		heapSize++;

		int i = heapSize-1;
		while (i > 0 && data[parent(i)]->frequency > data[i]->frequency)
		{
			GPD::swap<Node*>(data[i], data[parent(i)]);
			i = parent(i);
		}
	}

	void Heap::insert(TNode* item)
	{
		Node* newItem = new Node(item->getKey(), item->getData());
		insert(newItem);
	}

	Node Heap::min()
	{
		return (*data[0]);
	}

	Node* Heap::deleteMin()
	{
		if (isEmpty())
			return NULL;
		Node* res = data[0];

		heapSize--;
		data[0] = data[heapSize];

		fixHeap(0);
		return res;
	}

	const int& Heap::leftChild(const int& index)
	{
		return (index * 2 + 1);
	}

	const int& Heap::rightChild(const int& index)
	{
		return (index * 2 + 2);
	}

	const int& Heap::parent(const int& index)
	{
		return ((index-1) / 2);
	}

	void Heap::fixHeap(const int& index)
	{
		int i = index, min;
		bool end = false;

		while (!end)
		{
			if (leftChild(i) < heapSize && data[leftChild(i)]->frequency < data[i]->frequency)
				min = leftChild(i);
			else
				min = i;

			if (rightChild(i) < heapSize && data[rightChild(i)]->frequency < data[min]->frequency)
				min = rightChild(i);

			if (min == i)
				end = true;
			else
			{
				GPD::swap<Node*>(data[i], data[min]);
				i = min;
			}
		}
	}
}