//Ervin Hennrich
//cs 4280
//Feb 9, 2019
//Project 0, implementing a BST


#ifndef node_h
#define node_h
#include <iostream>
#include <string>
#include <stdlib.h>

//The Binary Search Tree wrapper structure. 
		struct Node{
			int key;
			std::string names;
			Node *right;
			Node *left;
		
			//Node contructor.
			Node(){
				key = 0;
				right = nullptr;
				left = nullptr;
			}
	};


#endif


