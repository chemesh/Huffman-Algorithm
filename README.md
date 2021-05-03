# Huffman-Algorithm
This one is an implimentation of the Huffman algorithm for file encoding and decoding

There ia also an implimentaion of a Binari Search Tree data structure, using a binari tree data structure as a base, and which the algorithm utilize.

This program recievs the full/relative path of a text file as input from stdin.
First, it will count the number of appearences of each character in the file, using a Binary Search Tree data structure (class BST) so that every tree node correspond to a character as key, and the number of appearences as satelite data.

Then, the program will call and perform the Huffman algorithm that will builed a Minimum Heap (using binary tree) data structure with each node represent a character and its  appearence frequency in the text file.
in the end the program will print out the encoded file size

NOTICE! - this program doesnt encode the file, but creating the optimal encode and decode map for the file!
