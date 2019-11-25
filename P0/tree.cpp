//Ervin Hennrich
//cs 4280
//Feb 9, 2019
//Project 0, implementing a BST



#include <iostream>
#include "node.h"
#include <fstream>
#include <string>



//Adds nodes to a tree, using recursion. 
void buildTree(Node *newnode, Node *&anode){
	//the tree is empty
	if (anode == nullptr){
                anode = newnode;
		return;
        }
		//otherwise go left or right depending on value looking for a nullptr
                if (newnode->key < anode->key){ 
			if(anode->left == nullptr){
                        	anode->left = newnode;
				return;
                	}
			else
				buildTree(newnode, *&anode->left);
		}
		else {
			if(anode->key == newnode->key){
				if (anode->names.find(newnode->names) != std::string::npos){   //checks to see if the string is already there
					return;
				}
				else{
					anode->names.append(" " + newnode->names);
					return;
				}
			}

			else if (anode->right == nullptr){
                        	anode->right = newnode;
				return;
                	}
			else
				buildTree(newnode, *&anode->right);
		}
}


//The inorder tree printing function. Uses recurssion to go through the tree and print accordingly
void printInorder(Node *inner,int count, std::ostream& out){
	if (inner != nullptr){
		count++;
	    	printInorder(inner->left, count, out);
		for (int n = count - 2; n>=0; n--){
			out << "--";
		}
		out << inner->key << " " << inner->names << std::endl;
		printInorder(inner->right, count, out);
	}
}
//Preorder printing funtion
void printPreorder(Node *inner,int count, std::ostream& out){
	if (inner != nullptr){
		count++;
		for (int n = count - 2; n>=0; n--){
			out << "--";
		}
    		out << inner->key << " " << inner->names << std::endl;
    		printPreorder(inner->left, count, out);
        	printPreorder(inner->right, count, out);
	}
}
//Postorder function
void printPostorder(Node *inner, int count, std::ostream& out){
	if (inner != nullptr){
		count++;
    		printPostorder(inner->left, count, out);
        	printPostorder(inner->right, count, out);
		for (int n = count - 2; n>=0; n--){
			out << "--";
		}
    		out << inner->key << " " << inner->names << std::endl;

	}
}


