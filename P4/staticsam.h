
#ifndef STATICSAM_H
#define STATICSAM_H

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
#include <map>
#include <vector>


extern std::map<std::string, std::string> mapsofvar;

void staticsam(Node *);

std::string vectcpyer(std::vector<token> ent);




#endif
#pragma once
