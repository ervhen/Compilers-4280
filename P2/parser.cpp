/*
Ervin Hennrich


My BNF, I changed a few things, to make it LL(1) and to make it fit a BST.
<program>  ->       <vars> <block>
<block>   	->      void <vars> <stats> return
<vars>     	->  	empty | var Identifier : Integer <vars> 
<expr>    	->  	<A> <x>
<x>		    ->	    + <expr> | - <expr> | E
<A>         ->    	<N> <Y>
<Y>		    ->	    / <A> |  E
<N>         ->   	<M> <Z>
<Z>		    ->	    * <N> | E 
<M>    	    ->      <M> |  <R>
<R>         ->       <expr> ) | Identifier | Integer
<stats>     ->  	<stat> ; <mStat>
<mStat>   	->  	E |  <stat>  ;  <mStat>
<stat>     	->  	<in> | <out> | <block> | <if> | <loop> | <assign>
<in>        ->      scan  Identifier 
<out>      	->      print <expr>
<if>       	->      cond [ <inner> ] <stat>
<loop>      ->      iter [ <inner> ] <stat>
<inner>	    ->	    <expr> <mid>
<mid>		->	    <RO> <expr>
<assign>   	->      Identifier  = <expr>  
<RO>        ->      < <less> | = <eq> | >
<less>		->       > | E
<eq>		->	    < | > | E           
*/




#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "node.h"
#include <string>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>

token tk;

Node *errorfunky(std::string from){ //line numbers broke when I "fixed" scanner, so I just left them out
    std::cout << "ERROR: " << from << " " << tk.tokenInstance;
    exit(-1);
}

Node *parser(){
    tk = scanner();
    Node *root;
    root = program();
    if(tk.tokenIdent == EOF_tk) { return root;}
    else{
        errorfunky("EOF expected, found");
    }

}
Node *program(){
    Node *newnode = new Node;
    newnode->names = "program";
    newnode->left = vars();
    newnode ->right = block();
    return newnode;

}
Node *vars(){
    Node *newnode = new Node;
    newnode->names = "vars";
    if(tk.tokenInstance.compare("var") == 0){ //var Identifier : Integer <vars>
        tk = scanner();
        if(tk.tokenIdent == IDENT_tk){
            newnode->keys.push_back(tk);
            tk = scanner();
            if (tk.tokenInstance.compare(":") == 0){
                tk = scanner();
                if(tk.tokenIdent == NUM_tk){
                    newnode->keys.push_back(tk);
                    tk = scanner();
                    newnode->left = vars();
                    return newnode;
                }
                else{
                    errorfunky("Number expected, found");
                }
            }
            else
            {
                errorfunky("Syntax : expected, found");
            }
            
        }
        else{
            errorfunky("Identifier expected, found");
        }
    }
    else{
        return newnode; //empty
    }

}

Node *block(){
    Node *newnode = new Node;
    newnode->names = "block";
    if (tk.tokenInstance.compare("void") == 0){
        tk = scanner();
        newnode->left = vars();
        newnode->right = stats();
        if (tk.tokenInstance.compare("return") == 0)
        {
            tk = scanner();
            return newnode;
        }
        else
        {
            errorfunky("return expected, found ");
        }        
    }
    else
    {
        errorfunky("void epected, found");
    }
}

Node *stats(){
    Node *newnode = new Node;
    newnode->names = "stats";
    newnode->left = stat();
    if (tk.tokenInstance.compare(";") == 0){
        tk = scanner();
        newnode->right = mstat();
        return newnode;
    }
    else
    {
        errorfunky("; expected, found");
    }
}

Node *stat(){ //in | out | block | if | loop | assign
    Node *newnode = new Node;
    newnode->names = "stat";
    if(tk.tokenInstance.compare("scan") == 0){ //in
        tk=scanner(); //consume scan; verified before entry
        newnode->left = in();
        return newnode;
    }
    else if(tk.tokenInstance.compare("print") == 0){ //out
        tk = scanner();
        newnode->left = out();
        return newnode;
    }
    else if(tk.tokenInstance.compare("cond") == 0) { //if
        tk=scanner();
        newnode->left = iffer();
        return newnode;
    }
    else if(tk.tokenInstance.compare("iter") == 0){ //loop
        tk = scanner();
        newnode->left = loop();
        return newnode;
    }
    else if (tk.tokenIdent == IDENT_tk){ //assign dont consume tk here leave it for assign
        newnode->left = assign();
        return newnode;
    }
    else if (tk.tokenInstance.compare("void") == 0){
        newnode->left = block(); //block checks for Node,* so dont want to eat it
        return newnode;
    }
    else{
        errorfunky("Unexpected token");
    }
    
}

Node *mstat(){
    Node *newnode = new Node;
    newnode->names = "mstat";
    if ( (tk.tokenInstance.compare("scan") == 0) || (tk.tokenInstance.compare("print") == 0) || (tk.tokenInstance.compare("cond") == 0) || (tk.tokenInstance.compare("iter") == 0) || tk.tokenIdent == IDENT_tk){
        newnode->left = stat();
        if (tk.tokenInstance.compare(";") == 0){
            tk = scanner();
            newnode->right = mstat();
            return newnode;
        }
        else{
            errorfunky("; expected, found");
        }
    }
    else{
        return newnode; //empty
    }

}

Node *in(){ //scan already consumed
    Node *newnode = new Node;
    newnode->names = "in";
    if (tk.tokenIdent == IDENT_tk){
        newnode->keys.push_back(tk);
        tk = scanner();
        return newnode;
    }
    else{
        errorfunky("Identifier expected, found");
    }
}

Node *out(){
    Node *newnode = new Node;
    newnode->names = "out";
    newnode->left = expr();
    return newnode;
}

Node *iffer(){
    Node *newnode = new Node;
    newnode->names = "if";
    if(tk.tokenInstance.compare("[") == 0){
        tk = scanner();
        newnode->left = inner();
        if(tk.tokenInstance.compare("]") == 0){
            tk = scanner();
            newnode->right = stat();
            return newnode;
        }
        else{
            errorfunky("] expected, found");
        }
    }
    else{
        errorfunky("[ expected, found");
    }
}

Node *inner(){
    Node *newnode = new Node;
    newnode->names = "inner";
    newnode ->left = expr();
    newnode->right = mid();
    return newnode;
}

Node *mid(){
    Node *newnode = new Node;
    newnode->names = "inner";
    newnode->left = ro();
    newnode->right = expr();
    return newnode;
}

Node *assign(){
    Node *newnode = new Node;
    newnode->names = "assign";
    if (tk.tokenIdent == IDENT_tk){
        newnode->keys.push_back(tk);
        tk = scanner();
        if(tk.tokenInstance.compare("=") == 0){
            tk = scanner();
            newnode->left = expr();
            return newnode;
        }
        else{
            errorfunky("= expected, found");
        }
    }
    else{
        errorfunky("Identifier expected, found");
    }
}

Node *loop(){
    Node *newnode = new Node;
    newnode->names = "loop";
    if(tk.tokenInstance.compare("[") == 0){
        tk = scanner();
        newnode->left = inner();
        if(tk.tokenInstance.compare("]") == 0){
            tk = scanner();
            newnode->right = stat();
            return newnode;
        }
        else{
            errorfunky("] expected, found");
        }
    }
    else{
        errorfunky("[ expected, found");
    }
}

Node *expr(){
    Node *newnode = new Node;
    newnode->names = "expr";
    newnode->left = a();
    newnode->right = x();
    return newnode;
}

Node *x(){
    Node *newnode = new Node;
    newnode->names = "x";
    if(tk.tokenIdent == plus_tk){
        tk = scanner();
        newnode->left = expr();
        return newnode;
    }
    else if(tk.tokenIdent == minus_tk){
        tk = scanner();
        newnode->right = expr();
        return newnode;
    }
    else{
        return newnode; //empty
    }
}

Node *a(){
    Node *newnode = new Node;
    newnode->names = "a";
    newnode->left = n();
    newnode->right = y();
    return newnode;
}

Node *y(){
    Node *newnode = new Node;
    newnode->names = "y";
    if(tk.tokenIdent == div_tk){
        tk = scanner();
        newnode->left = a();
        return newnode;
    }
    else{
        return newnode;
    }
}

Node *n(){
    Node *newnode = new Node;
    newnode->names = "n";
    newnode->left = m();
    newnode->right = z();
    return newnode;
}

Node *m(){
    Node *newnode = new Node;
    newnode->names = "m";
    if(tk.tokenInstance.compare("%") == 0){
        tk = scanner();
        newnode->left = m();
        return newnode;
    }
    else{
        newnode->right = r();
        return newnode;
    }
}

Node *r(){
    Node *newnode = new Node;
    newnode->names = "r";
    if(tk.tokenInstance.compare("(") == 0){
        tk = scanner();
        newnode->left = expr();
        if(tk.tokenInstance.compare(")") == 0){
            return newnode;
        }
        else{
            errorfunky(") expected, found");
        }
    }
    else if(tk.tokenIdent == IDENT_tk){
        newnode->keys.push_back(tk);
        tk = scanner();
        return newnode;
    }
    else if(tk.tokenIdent == NUM_tk){
        newnode->keys.push_back(tk);
        tk = scanner();
        return newnode;
    }
    else{
        errorfunky("(, Identifier or Number expected, found");
    }
}

Node *z(){
    Node *newnode = new Node;
    newnode->names = "z";
    if (tk.tokenIdent == mult_tk){
        tk = scanner();
        newnode->left = n();
        return newnode;
    }
    else{
        return newnode;
    }
}

Node *ro(){
    Node *newnode = new Node;
    newnode->names = "ro";
    if (tk.tokenIdent == less_than_tk){
        tk = scanner();
        newnode->left = less();
        return newnode;
    }
    else if (tk.tokenIdent == great_th_tk){
        tk = scanner();
        return newnode;
    }
    else if (tk.tokenIdent == equal_tk){
        tk = scanner();
        newnode->left = eq();
        return newnode;
    }
    else {
        errorfunky("< > or = expected, found");
    }
}

Node *less(){
    Node *newnode = new Node;
    newnode->names = "less";
    if (tk.tokenIdent == great_th_tk){
        tk = scanner();
        return newnode;
    }
    else{
        return newnode;
    }
}

Node *eq(){
    Node *newnode = new Node;
    newnode->names = "eq";
    if(tk.tokenIdent == great_th_tk){
        tk = scanner();
        return newnode;
    }
    else if(tk.tokenIdent == less_than_tk){
        tk = scanner();
        return newnode;
    }
    else {
        return newnode;
    }
}

