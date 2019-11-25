#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include <iostream>
#include <string.h>

extern int linum; //global defined in main
bool isIdent(const std::string &); //is Identifier
token scanner(std::string); //returns tokens
int inReserved(const std::string &); //check if keyword
bool isnumber(const std::string &); //checks if number
bool isop(const std::string &);

#endif // !TESTSCANNER_H
#pragma once
