#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "testTree.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>


void vectprint(std::vector<token> ent){
	for(auto i: ent){
		std::cout << i.tokenInstance << ' ';
	}
}

void printPred(Node *inner,int count){ // std::ostream& out
	if (inner != nullptr){
		count++;
		for (int n = count - 2; n>=0; n--){
			std::cout << "--";
		}
    		std::cout << inner->names << " " ;
			vectprint(inner->keys);
			std::cout << std::endl;
    		printPred(inner->left, count);
        	printPred(inner->right, count);
	}
}

void printIn(Node *inner,int count){
	if (inner != nullptr){
		count++;
	    	printIn(inner->left, count);
		for (int n = count - 2; n>=0; n--){
			std::cout << "--";
		}
    	std::cout << inner->names << " " ;
		vectprint(inner->keys);
		std::cout << std::endl;
		printIn(inner->right, count);
	}
}