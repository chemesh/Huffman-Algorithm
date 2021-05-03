

#include <iomanip>
#include "BST.h"
#include "Proj2.h"
#include "Heap.h"

using namespace std;
using namespace heap;
using namespace TREE;

/// function that recieve a text file name and return a binary search tree built from the characters in the file.
/// a member (tree node) of the binary search tree holds the char lexicographic value as key,
/// and its number of appearences in the file as the satelite data, using struct 'Item' (proj2.h)
BSTree& buildTree(string& filename);


/// function recieves the binary search tree built from 'buildTree' func and return a Huffman tree.
/// new tree nodes holds a char member as satelite data, and an int member for char appearences as frequency
Node* huffman(BSTree& tr);


/// recursive function. recieves the Huffman tree built in 'huffman' func and returns the encoded file weight
/// Node* tr = huffman tree
/// depth = the depth of each subtree sent in the recursive call
/// code = empty, externally allocated int array to visualize the encoded version of each character
int printEncoded(Node* tr, int depth, int* code);




int main()
{
	string filename;

	cout << "please enter name of file: " << endl;
	cin >> filename;



	BSTree tr = buildTree(filename);

	int* code = new int[tr.getNumOfObjects()];

	Node* res = huffman(tr);

	cout << "Character encoding: " << endl;
	int weight = printEncoded(res,0,code);

	cout << endl <<endl
		<<"Encoded file weight : " << weight << " bits" << endl;

	return 0;
}





BSTree& buildTree(string& filename)
{
	//creating the Binary Search tree that'll hold all the characther types in the file
	//and their number of instances

	BSTree* tr = new BSTree;
	Item new_char('0',1);

	ifstream infile(filename.c_str());
	
	
	if (!infile.is_open())
	{
		cout << "error reding file" << endl;
		exit(-1);
	}

	infile >> std::noskipws >> new_char.key;
	while (!infile.eof())
	{
		tr->insert(new_char);
		infile >> std::noskipws >> new_char.key;
		
	}

	infile.close();
	return *tr;
}


Node* huffman(BSTree& tr)
{
	int i, size = tr.getNumOfObjects();
	int freqSum;
	TNode* temp;
	Heap Q(size);
	Node* node;

	//initializing forest of leaves in Q;
	for (i = 0; i < size; i++)
	{
		temp = tr.min();
		Q.insert(temp);
		tr.remove(temp->getKey());
	}

	//creating the huffman tree using huffman algorithem
	for (i = 0; i < size-1; i++)
	{
		node = new Node;
		node->setLeftChild(Q.deleteMin());
		node->setRightChild(Q.deleteMin());
		freqSum = node->getLeftChild()->getFrequency() + node->getRightChild()->getFrequency();
		node->setFrequency(freqSum);

		Q.insert(node);
	}

	return Q.deleteMin();
}

int printEncoded(Node* tr, int depth, int* code)
{
	if (tr != NULL)
	{
		if (tr->getLeftChild() == NULL && tr->getRightChild() == NULL) //is a leaf
		{
			if (tr->getData() == '\n') //special char \n printing
				cout << "'\\n' - ";
			else if (tr->getData() == '\t') //special char \t printing
				cout << "'\\t' - ";
			else
				cout << "'" << tr->getData() << "' - "; //'normal' char

			if (depth == 0) //tree has only root <=> root is also a leaf
			{
				cout << "1";
				return tr->getFrequency();
			}

			for (int i = 0; i < depth; i++)
			{
				cout << code[i]; 
			}
		
			cout << endl;

			//returning length of the code * char instances
			return (tr->getFrequency() * depth);
		}
		else
		{
			int freqSum;
			code[depth] = 0; //left subtree code starts with 0
			freqSum = printEncoded(tr->getLeftChild(), depth + 1, code);

			code[depth] = 1; //right subtree code starts with 1
			freqSum += printEncoded(tr->getRightChild(), depth + 1, code);
			return freqSum;
		}
	}
	else
		return 0;
}