


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
#include "staticsam.h"
#include "comp.h"
#include <map>
#include <vector>

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
	std::string finout;

	//file is given
	if (argc == 2) {
		stinput = argv[1];
		inputf_name = stinput + ".sp19";
		finout = stinput + ".asm";
	}//No file given, keyboard option
	else if (argc == 1) {
		std::ofstream outputfile;
		inputf_name = ".inputfile.sp19";
		finout = "out.asm";
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
	std::ifstream test;
	if(test.good()){
		remove(finout.c_str());
	}
	
	//testScanner opens the file, that main gets. Had issues with passing streams, this way works as well
	Node *parsetree = NULL;
	parsetree = parser();
	staticsam(parsetree);
	comp(parsetree, finout);
	//std::cout << "STOP\n";
	writetotarget("STOP", " ", finout);
	for(auto elem : mapsofvar){
		writetotarget(elem.first, elem.second, finout);
    //std::cout << elem.first << " " << elem.second << " " << "\n";
	}




	return 0;
}

