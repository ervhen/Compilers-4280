#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include <iostream>
#include <string.h>
#include <fstream>

extern int linum; //global defined in main
extern std::string inputf_name;
extern int fipos;
std::string getdastring();
void getlinum(std::ifstream&);
bool isIdent(const std::string &); //is Identifier
token scanner(); //returns tokens
int inReserved(const std::string &); //check if keyword
bool isnumber(const std::string &); //checks if number
bool isop(const std::string &);

#endif // !TESTSCANNER_H
#pragma once
