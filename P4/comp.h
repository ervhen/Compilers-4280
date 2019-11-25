

#ifndef COMP_H
#define COMP_H

#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "node.h"
#include "testTree.h"
#include "staticsam.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>

void comp(Node *, std::string);
void out(Node *, std::string);
void compin(Node *, std::string);
void compexpr(Node *, std::string);
void compiffer(Node *, std::string);
void compr(Node *, std::string);
void compassign(Node *, std::string);
void writetotarget(std::string, std::string, std::string);
void exprevaler(std::string);
void comploop(Node *, std::string);

#endif