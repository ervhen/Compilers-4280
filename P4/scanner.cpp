#include "token.h"
#include "scanner.h"
#include <string>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>

//array of reserved words
static const std::string reserved[] = { "iter","void", "var", "return", "scan", "print", "program", "cond", "then", "let", "int" };
static int wordperline = 0;
static int eofcheck = 0;

std::string getdastring(){
	std::ifstream inputfile;
	inputfile.open(inputf_name.c_str());
	
	//basically same as P0, read from streams tokenizing
	if (inputfile.is_open()) {
		if (wordperline == 0){
			getlinum(inputfile);
			linum++;
		}
		std::string line;
		inputfile.seekg(fipos, inputfile.beg);
		inputfile >> line;
		if( (inputfile.rdstate() & std::ifstream::eofbit) != 0){
			inputfile.close();
			line = "HOI";
			return line;
		}
		wordperline--;
		fipos = inputfile.tellg();
			if (line == "&") { //checks for comments and skips it
				getline(inputfile, line);
				fipos = inputfile.tellg();
				linum--;
				return getdastring();
			}
		
		return line;
	}
	else {
		std::cout << "Input read Failed.";
		exit(-1);
	}
	inputfile.close();
}

void getlinum(std::ifstream & infile){
	std::string thing;
	std::string inbetween;
	getline(infile, thing);
	std::stringstream getit(thing);
        while (getline(getit, inbetween, ' ')) {
                if (inbetween == "&"){ //checks for comments and skips it
                	break;
                }
		wordperline++;
	}
}


//checks if token meets definition of identifier, has already been checked if it is a keyword
bool isIdent(const std::string &maybe) {

        if (inReserved(maybe) == -1){ //double check its not in reserved
                char hold = maybe.at(0); //get first char
                if (isalpha(hold) != 0){ //check its a letter
                        if(islower(hold) != 0){ //check its lowercase
                            if (maybe.length() > 1){
                                for (int i = 1; i < maybe.length(); i++){ //iterate through string one char at a time checking if alpha num 
                                        char otold = maybe.at(i);
                                        if ((isalnum(otold) != 0) && (i == maybe.length()-1)){
                                                return true;
                                        }
                                        if (isalnum(otold) !=0){
                                                continue;
                                        }
                                        else{
                                                return false;
                                        }
                                }
                            }
                            else{
                                return true;
                            }
                        }
                        else{
                                return false;
                        }
                }
                else{
                        return false;
                }
        }
        else{
                return false;
        }
}

//check if reserved word
int inReserved(const std::string &what) {
	for (int i = 0; i < reserved->length(); i++)
	{
		if (what.compare(reserved[i]) == 0){
			return i;
		}
	}
	return -1;
}
//check if string consists of numbers
bool isnumber(const std::string &checkit) {
	return checkit.find_first_not_of("0123456789") == std::string::npos; //the find_first_not_of function is rather usefull, reminds me of python functions
}

//checks to see if string consists of op/delims 
bool isop(const std::string &checkit) {
        return checkit.find_first_not_of("=<>:+-*/%.(),{};[]") == std::string::npos;
}

token scanner() {
	std::string line = getdastring();
	token inputok;
	if (line.compare("HOI") == 0) {
		inputok.tokenInstance = "EOF";
		inputok.tokenIdent = EOF_tk;
		inputok.linenum = linum;
		return inputok;
		}
			//check keyword
			if ((inReserved(line)) != -1) {
				inputok.tokenInstance = line;
				inputok.tokenIdent = KW_tk;
				inputok.linenum = linum;
				return inputok;
			}
			//check if number
			else if (isnumber(line) == true) {
				inputok.tokenInstance = line;
				inputok.tokenIdent = NUM_tk;
				inputok.linenum = linum;
				return inputok;
			}
			//check if identifier
			else if (isIdent(line) == true) {
				inputok.tokenInstance = line;
				inputok.tokenIdent = IDENT_tk;
				inputok.linenum = linum;
				return inputok;
			}
			//finds what op/delim it is and returns that
			else if (isop(line) == true) {
				inputok.tokenInstance = line;
				inputok.linenum = linum;
				if (line.compare("=") == 0) {
					inputok.tokenIdent = equal_tk;
				}
				else if (line.compare("<") == 0) {
					inputok.tokenIdent = less_than_tk;
				}
				else if (line.compare(">") == 0) {
					inputok.tokenIdent = great_th_tk;
				}
				else if (line.compare(":") == 0) {
					inputok.tokenIdent = col_tk;
				}
				else if (line.compare("+") == 0) {
					inputok.tokenIdent = plus_tk;
				}
				else if (line.compare("-") == 0) {
					inputok.tokenIdent = minus_tk;
				}
				else if (line.compare("*") == 0) {
					inputok.tokenIdent = mult_tk;
				}
				else if (line.compare("/") == 0) {
					inputok.tokenIdent = div_tk;
				}
				else if (line.compare("%") == 0) {
					inputok.tokenIdent = mod_tk;
				}
				else if (line.compare(",") == 0) {
					inputok.tokenIdent = comma_tk;
				}
				else if (line.compare("{") == 0) {
					inputok.tokenIdent = op_brace_tk;
				}
				else if (line.compare("}") == 0) {
					inputok.tokenIdent = clo_brace_tk;
				}
				else if (line.compare(";") == 0) {
					inputok.tokenIdent = semi_tk;
				}
				else if (line.compare("[") == 0) {
					inputok.tokenIdent = op_brack;
				}
				else if (line.compare("]") == 0) {
					inputok.tokenIdent = close_brak_tk;
				}
				else if (line.compare("=<") == 0){
					inputok.tokenIdent = less_equal;
				}
				else if (line.compare("=>") == 0){
					inputok.tokenIdent = great_equal;
				}
				else if(line.compare("<>") == 0){
					inputok.tokenIdent = less_great;
				}
				return inputok;
			}
			//else its an error
			else {
				inputok.tokenInstance = line;
				inputok.tokenIdent = ERR_tk;
				inputok.linenum = linum;
			}
		
		//inputfile.close();

}
