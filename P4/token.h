#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include <iostream>

//enum for tokens, non scoped made it easier to use, may want to change later or not
enum tokenID { IDENT_tk, NUM_tk, KW_tk, equal_tk, less_than_tk, great_th_tk, less_equal, great_equal,less_great, col_tk, plus_tk, minus_tk, mult_tk, div_tk, mod_tk, comma_tk, op_brace_tk, clo_brace_tk, semi_tk, op_brack, close_brak_tk, quot_tk, ERR_tk, EOF_tk };

struct token{
	//non-scoped enum, may need to change, may help with scoping later
	tokenID tokenIdent;
	std::string tokenInstance;
	int linenum; //the linenumber it was found on
};


#endif // !TOKEN_H

