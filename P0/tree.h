//Ervin Hennrich
//cs 4280
//Feb 9, 2019
//Project 0, implementing a BST


#ifndef TREE_H
#define TREE_H
#include "node.h" 
#include <iostream>
#include <fstream>
#include <string>
	void buildTree(Node *, Node *&);
	void printInorder(Node *, int, std::ostream&);
	void printPreorder(Node *, int, std::ostream&);
	void printPostorder(Node *, int, std::ostream&);
#endif
