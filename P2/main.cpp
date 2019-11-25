#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "node.h"
#include "testTree.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>


//global for line number
int linum = 0;
//global for filename
std::string inputf_name;
int fipos = 0;

int main(int argc, char *argv[]) {


	//initialize strings for input
	std::string stinput;
	//setup reading stream
	std::ifstream inputfile;

	//file is given
	if (argc == 2) {
		stinput = argv[1];
		inputf_name = stinput + ".sp19";

	}//No file given, keyboard option
	else if (argc == 1) {
		std::ofstream outputfile;
		inputf_name = ".inputfile.sp19";
		outputfile.open(".inputfile.sp19");
		std::string input;
		while (std::getline(std::cin, input)) {
			outputfile << input << std::endl;
		}
		outputfile.close();
	}
	else {//entered more than 2 args
		std::cout << "Too many arguments" << std::endl;
		return 1;
	}
	//testScanner opens the file, that main gets. Had issues with passing streams, this way works as well
	Node *parsetree = NULL;
	parsetree = parser();
	std::cout<< "Preorder" << std::endl;
	printPred(parsetree, 0);
	std::cout<< std::endl << std::endl;
	std::cout<< "Inorder" << std::endl;
	printIn(parsetree, 0);



	return 0;
}

