//Ervin Hennrich
//cs 4280
//Feb 9, 2019
//Project 0, implementing a BST


#ifndef node_h
#define node_h
#include "token.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

//The Node struct. 
		struct Node{
			std::vector<token> keys;
			std::string names;
			Node *right;
			Node *left;
		
			//Node contructor.
			Node(){
				right = nullptr;
				left = nullptr;
			}
	};


#endif


