//implementation of Scanner 

#include "token.h"
#include "testScanner.h"
#include "scanner.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>



//array of reserved words
static const std::string reserved[] = { "iter","void", "var", "return", "scan", "print", "program", "cond", "then", "let", "int" };


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

token scanner(std::string tokenized) {
	token inputok;
	//check keyword
	if ((inReserved(tokenized)) != -1) {
		inputok.tokenInstance = tokenized;
		inputok.tokenIdent = KW_tk;
		inputok.linenum = linum;
		return inputok;
	}
	//check if number
	else if (isnumber(tokenized) == true){
		inputok.tokenInstance = tokenized;
		inputok.tokenIdent = NUM_tk;
		inputok.linenum = linum;
		return inputok;
	}
	//check if identifier
	else if (isIdent(tokenized) == true){
		inputok.tokenInstance = tokenized;
		inputok.tokenIdent = IDENT_tk;
		inputok.linenum = linum;
		return inputok;
	}
	//finds what op/delim it is and returns that
	else if (isop(tokenized) == true){
		inputok.tokenInstance = tokenized;
		inputok.linenum = linum;
		if (tokenized.compare("=") == 0){
                        inputok.tokenIdent = equal_tk;
                }
                else if (tokenized.compare("<") == 0){
                        inputok.tokenIdent = less_than_tk;
                }
                else if (tokenized.compare(">") == 0){
                        inputok.tokenIdent = great_th_tk;
                }
                else if (tokenized.compare(":") == 0){
                        inputok.tokenIdent = col_tk;
                }
                else if (tokenized.compare("+") == 0){
                        inputok.tokenIdent = plus_tk;
                }
                else if (tokenized.compare("-") == 0){
                        inputok.tokenIdent = minus_tk;
                }
                else if (tokenized.compare("*") == 0){
                        inputok.tokenIdent = mult_tk;
                }
                else if (tokenized.compare("/") == 0){
                        inputok.tokenIdent = div_tk;
                }
                else if (tokenized.compare("%") == 0){
                        inputok.tokenIdent = mod_tk;
                }
                else if (tokenized.compare(",") == 0){
                        inputok.tokenIdent = comma_tk;
                }
                else if (tokenized.compare("{") == 0){
                        inputok.tokenIdent = op_brace_tk;
                }
                else if (tokenized.compare("}") == 0){
                        inputok.tokenIdent = clo_brace_tk;
                }
                else if (tokenized.compare(";") == 0){
                        inputok.tokenIdent = semi_tk;
                }
                else if (tokenized.compare("[") == 0){
                        inputok.tokenIdent = op_brack;
                }
                else if (tokenized.compare("]") == 0){
                        inputok.tokenIdent = close_brak_tk;
                }
		return inputok;
	}		
	//else its an error
	else{
		inputok.tokenInstance = tokenized;
		inputok.tokenIdent = ERR_tk;
		inputok.linenum = linum;
	}

}
