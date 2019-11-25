

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
#include <iterator>
#include <map>
#include <vector>

std::map<std::string, int> testofit;
std::map<std::string, std::string> mapsofvar;
std::vector<std::vector<token>> globalvect;
std::vector<std::string, std::string>::iterator it;
static int instertnum;

void staticsam(Node *treein){
  if ( treein != nullptr){
    if (treein->names.compare("vars") == 0){
      if(treein->keys.empty()){
      }
      else if(mapsofvar.find(treein->keys[0].tokenInstance) == mapsofvar.end()){
        mapsofvar.insert(std::make_pair(treein->keys[0].tokenInstance, treein->keys[1].tokenInstance));
      }
      else{
        std::cout << "Error: Variable already defined" << std::endl;
        exit(-1);
      }

      //globalvect.push_back(treein->keys);
    }
    else if (!treein->keys.empty()){
      for(auto i: treein->keys){
        if(isnumber(i.tokenInstance) == true){
          continue;
        }
        else{
          std::map<std::string, std::string>::iterator theoneof = mapsofvar.find(i.tokenInstance);
          if (theoneof == mapsofvar.end()){
            std::cout << "Error: Variable Undefined" << std::endl;
            exit(-1);
          }
        }
      }
    }

    
		staticsam(treein->left);
    staticsam(treein->right);
	}
}