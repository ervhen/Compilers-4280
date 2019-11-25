#include "token.h"
#include "scanner.h"
#include "testScanner.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

//gets input file name
int testScanner(std::string inputf_name){ 
	//for prints what tokens are (array is in same order as enum list)	
	std::string tokenNames[] = {"Identifier", "Number", "Keyword", "Equal token", "Less Than", "Greater than", "Colon", "Addition", "Subtraction", "Multiplication", "Division", "Mod", "Comma", "Open Brace", "Closed Brace", "Semi colon", "Open Bracket", "Closed Bracket", "Scanner ERROR"}; 

	std::ifstream inputfile;
	inputfile.open(inputf_name.c_str());
	
	//basically same as P0, read from streams tokenizing
	if (inputfile.is_open()){
		
		std::string line;
		std::string inbetween;

		while (std::getline(inputfile, line)) {

			linum++;		

			std::stringstream getit(line);

			while (getline(getit, inbetween, ' ')) {
				if (inbetween == "&"){ //checks for comments and skips it
					break;
				}
				token hold = scanner(inbetween); 
				std::cout << tokenNames[hold.tokenIdent] << "  \"" << hold.tokenInstance << "\" " << hold.linenum << std::endl;
			}
		}
		if (inputfile.eof()){ //checks if EOF bit is set (which always should be once it gets here)
			std::cout << "EOF token " << linum << std::endl;
			inputfile.close();
			return 0;
		}

	}
	else {
		std::cout << "File not found";
		exit(-1);
	}
}
