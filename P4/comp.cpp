#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "node.h"
#include "testTree.h"
#include "comp.h"
#include "staticsam.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>
#include <iterator>
#include <map>
#include <vector>
#include <stack>
#include <deque>

std::ofstream asmout;
int ACC;
std::vector<std::string> othervars; //have to be isolated from temp
std::vector<std::string> temp;
std::vector<std::string> looper;
std::deque<std::string> iterstuff;
int varCt = 0;
std::deque <std::string> vals;
std::deque <std::string> commands;
std::deque <std::string> mathit;
int nums = 0;
int mult = 0;
int diver = 0;
int add = 0;
int sub = 0;
int printflag = 0;
int inflag = 0;
int assignflag = 0;
int loopflag = 0;
int iterprintflag = 0;
int iterinflag = 0;
int iterassignflag = 0;
int iterloopflag = 0;

void writetotarget(std::string com, std::string va, std::string output){
    std::ofstream target;
    target.open(output, std::ios_base::app);
    target << com << " " << va << std::endl;
    target.close();

}
void comp(Node *treein, std::string output){
    if(treein != nullptr){
        if(treein->names.compare("out") == 0){
            out(treein->left, output);
            if(printflag == 1){
                while(loopflag > 0){
                    writetotarget(looper.back() + ":", "NOOP", output);
                    looper.pop_back();
                    loopflag--;
                }
            }
            else if(iterprintflag == 1){
                while(loopflag > 0){
                    writetotarget(looper.back() + ":", "NOOP", output);
                    looper.pop_back();
                    loopflag--;
                }
            }

        }
        if(treein->names.compare("in") == 0){
            compin(treein, output);
            if(inflag == 1){
                while(loopflag > 0){
                    writetotarget(looper.back() + ":", "NOOP", output);
                    looper.pop_back();
                    loopflag--;
                }
            }
        }
        if(treein->names.compare("if") == 0){
            compiffer(treein, output);
        }
        if(treein->names.compare("assign") == 0){
            compassign(treein, output);
            if(assignflag == 1){
                while(loopflag > 0){
                    writetotarget(looper.back() + ":", "NOOP", output);
                    looper.pop_back();
                    loopflag--;
                }
            }
            else if(iterassignflag == 1){
                    writetotarget(iterstuff.front(), iterstuff.at(1), output);
                    iterstuff.pop_front();
                    iterstuff.pop_front();
                    writetotarget(iterstuff.front(), iterstuff.at(1), output);
                    iterstuff.pop_front();
                    iterstuff.pop_front();
                    writetotarget(iterstuff.front(), iterstuff.at(1), output);
                    iterstuff.pop_front();
                    iterstuff.pop_front();
                    iterassignflag = 0;
            }
        }
        if(treein->names.compare("loop") == 0){
            comploop(treein, output);
        }
        comp(treein->left, output);
        comp(treein->right, output);
    }
}

void compin(Node *treein, std::string output){
    writetotarget("READ", treein->keys[0].tokenInstance, output);
}

void out(Node *treein, std::string output){    
    //asmout.open(output);
    if(treein != nullptr){
        Node * newnode = new Node;
        Node * otnode = new Node;
        otnode = treein->left; 
        if (treein->right->right != nullptr){ //check x, there is some add/sub
            compexpr(treein, output);
        }
        else if(treein->left->right->right != nullptr){ //there is division
            compexpr(treein, output);
        }
        else if(treein->left->left->right->left != nullptr){
            compexpr(treein, output);
        }
        else{
            int count = 0;
            newnode = treein;
            while (newnode->left != nullptr){
                if(newnode->names.compare("m") ==0){
                    count++;
                }
                newnode = newnode->left;
            }
            if(count >= 1){
                if(count % 2 == 1){
                    writetotarget("MULT", "-1", output);
                    writetotarget("STORE",newnode->right->keys[0].tokenInstance, output);
                }
            }
            writetotarget("WRITE", newnode->right->keys[0].tokenInstance, output);
        }
    }
}

std::string newTemper(){
    std::ostringstream ostringstreamit;
    ostringstreamit << "T" << varCt++;
    //std::string tempit = "T" + varCt++;
    temp.push_back(ostringstreamit.str());
    return ostringstreamit.str();
}

std::string newT(){ //have to be isolated from newTemper
    std::ostringstream ostringstreamit;
    ostringstreamit << "T" << varCt++;
    othervars.push_back(ostringstreamit.str());
    return ostringstreamit.str();
}

std::string labelMaker(){
    std::ostringstream ostringstreamit;
    ostringstreamit << "Loop" << varCt++;
    looper.push_back(ostringstreamit.str());
    return ostringstreamit.str();
}

void comploop(Node *treein, std::string output){
    std::deque<std::string>::iterator p;
    if(treein != nullptr){
        //check stat to see what flag it goes to
        Node *checker = new Node;
        checker = treein->right->left;
        Node *hold = new Node;
        hold = checker;
        if(checker->names.compare("out") == 0){
            iterprintflag++;
        }
        else if(checker->names.compare("assign") == 0){
            iterassignflag++;
        }
        else if(checker->names.compare("block") == 0){
            while(checker->right!= nullptr){
                hold= checker->right;
                if(hold->left != nullptr){
                    checker = checker->right;
                }
                else{
                    break;
                }
            }
            if(checker->left->left->names.compare("out")==0){
                iterprintflag++;
            }
            else if(checker->left->left->names.compare("assign")==0){
                iterassignflag++;
            }
            else if(checker->left->left->names.compare("in")==0){
                iterinflag++;
            }
        }
        else if(checker->names.compare("in") == 0){
            iterinflag++;
        }
        iterassignflag = 1;
        Node * newnode = new Node;
        newnode = treein;
        while (newnode->left != nullptr){
            newnode = newnode->left; //gets node before r, which is on the right (gets first expression on left)
            //std::cout << newnode->names;
        }
        writetotarget(labelMaker() + ":", "NOOP", output);
        writetotarget("LOAD", newnode->right->keys[0].tokenInstance, output);
        writetotarget("STORE", newT(), output);
        mapsofvar.insert(std::make_pair(othervars.back(), "0"));
        Node *tempnode = new Node;
        tempnode = treein->left->right->right; //other expr node
        if ((tempnode->left->right->left != nullptr) || (tempnode->left->left->right->left != nullptr) || (tempnode->left->left->left->right->left != nullptr)){
            compexpr(tempnode, output); //send in expr node
            exprevaler(output);
            //mathit.clear();
        }
        else{ //no math on right
            while(tempnode->left != nullptr){
                tempnode = tempnode->left; //ends right before r (which has value)
            }
            writetotarget("LOAD", tempnode->right->keys[0].tokenInstance, output);
            writetotarget("STORE", newT(), output);
            mapsofvar.insert(std::make_pair(othervars.back(), "0"));
        }
        Node *otnode = new Node;
        otnode = treein->left->right->left; //ro node
        if (otnode->keys[0].tokenInstance.compare("=") == 0){
            if(otnode->left->keys.empty()){
                    writetotarget("LOAD", mathit.back(), output);
                    writetotarget("SUB", othervars.back(), output);
                    writetotarget("BRNEG", labelMaker(), output);
                    writetotarget("BRPOS", looper.back(), output);
                    loopflag++;
            }
            else{
                if(otnode->left->keys[0].tokenInstance.compare("<") == 0){
                    writetotarget("LOAD", othervars.rbegin()[1], output);
                    writetotarget("SUB", othervars.back(), output);
                    writetotarget("BRPOS", labelMaker(), output);
                    loopflag++;
                }
                else{
                    iterstuff.push_back("LOAD");
                    iterstuff.push_back(othervars.rbegin()[1]);
                    iterstuff.push_back("SUB");
                    iterstuff.push_back(othervars.back());
                    iterstuff.push_back("BRPOS");
                    iterstuff.push_back(looper.back());
                }
            }
        }
        else if(otnode->keys[0].tokenInstance.compare(">")){
            iterstuff.push_back("LOAD");
            iterstuff.push_back(othervars.rbegin()[1]);
            iterstuff.push_back("SUB");
            iterstuff.push_back(othervars.back());
            iterstuff.push_back("BRZPOS");
            iterstuff.push_back(looper.back());
        }
    }
}

void compassign(Node *treein, std::string output){
    std::deque<std::string>::iterator p;
    if(treein != nullptr){
        if ((treein->left->right->right != nullptr) || (treein->left->left->right->right != nullptr) || (treein->left->left->left->right->left != nullptr)){ //check x, there is some add/sub
            compexpr(treein->left, output); //send in expr node
            exprevaler(output);
            writetotarget("COPY", treein->keys[0].tokenInstance + " " + temp.back(), output);
            mathit.clear();
        }
        else{
            Node * newnode = new Node;
            newnode = treein;
            while (newnode->left != nullptr){
                newnode = newnode->left;
            }
            writetotarget("LOAD", newnode->right->keys[0].tokenInstance, output);
            writetotarget("STORE", treein->keys[0].tokenInstance, output);
        }
    }
}

void exprevaler(std::string output){   
    std::deque<std::string>::iterator p;
    int total = mult+sub+diver+add;
    for(total; total>=0; total--){
        for(int x = 0; x<mathit.size(); x++){
            if(mathit[x].compare("MULT") == 0){
                writetotarget("LOAD", mathit[x+1], output);
                writetotarget("MULT", mathit[x+2], output);
                writetotarget("STORE", newTemper(), output);
                p = mathit.begin();
                advance(p, x);
                mathit.insert(p, temp.back());
                mapsofvar.insert(std::make_pair(temp.back(), "0"));
                mathit.erase(p+1, p+4);
                mult--;
                total--;
            }
            if((mult == 0) && (diver > 0)){
                if(mathit[x].compare("DIV") == 0){
                    writetotarget("LOAD", mathit[x+2], output);
                    writetotarget("DIV", mathit[x+1], output);
                    writetotarget("STORE", newTemper(), output);
                    p = mathit.begin();
                    advance(p, x); 
                    mathit.insert(p, temp.back());        
                    mapsofvar.insert(std::make_pair(temp.back(), "0"));
                    diver--;
                    total--;
                    mathit.erase(mathit.begin()+x+1, mathit.begin()+x+4);
                }
            }
        }
        for(int x = mathit.size(); x>=0; x--){
            if(diver == 0){ 
                if((mathit[x].compare("ADD") == 0) || (mathit[x].compare("SUB") == 0)){
                    writetotarget("LOAD", mathit[x+2], output);
                    writetotarget(mathit[x], mathit[x+1], output);
                    writetotarget("STORE", newTemper(), output);
                    p=mathit.begin();
                    mathit.insert(mathit.end(), temp.back());
                    advance(p, x);
                    mapsofvar.insert(std::make_pair(temp.back(), "0"));
                    mathit.erase(p, p+3);
                    add--;
                    sub--;
                    total--;
                    x = mathit.size();
                }
            }
        }
    }
}


void compiffer(Node *treein, std::string output){
    std::deque<std::string>::iterator p;
    if(treein != nullptr){
        //check stat to see what flag it goes to
        Node *checker = new Node;
        checker = treein->right->left;
        if(checker->names.compare("out") == 0){
            printflag++;
        }
        else if(checker->names.compare("assign") == 0){
            assignflag++;
        }
        else if(checker->names.compare("block") == 0){
            while(checker->right!= nullptr){
                checker = checker->right;
            }
            if(checker->left->left->names.compare("out")==0){
                printflag++;
            }
            else if(checker->left->left->names.compare("assign")==0){
                assignflag++;
            }
            else if(checker->left->left->names.compare("in")==0){
                inflag++;
            }
        }
        else if(checker->names.compare("in") == 0){
            inflag++;
        }



        Node * newnode = new Node;
        newnode = treein;
        while (newnode->left != nullptr){
            newnode = newnode->left; //gets me node before r, which is on the right (gets first expression on left)
        }
        writetotarget("LOAD", newnode->right->keys[0].tokenInstance, output);
        writetotarget("STORE", newT(), output);
        mapsofvar.insert(std::make_pair(othervars.back(), "0"));
        Node *tempnode = new Node;
        tempnode = treein->left->right->right; //other expr node
        if ((tempnode->left->right->left != nullptr) || (tempnode->left->left->right->left != nullptr) || (tempnode->left->left->left->right->left != nullptr)){
            compexpr(tempnode, output); //send in expr node
            exprevaler(output);
            //mathit.clear();
        }
        else{ //no math on right
            while(tempnode->left != nullptr){
                tempnode = tempnode->left; //ends right before r (which has value)
            }
            writetotarget("LOAD", tempnode->right->keys[0].tokenInstance, output);
            writetotarget("STORE", newT(), output);
            mapsofvar.insert(std::make_pair(othervars.back(), "0"));
        }
        Node *otnode = new Node;
        otnode = treein->left->right->left; //ro node
        if (otnode->keys[0].tokenInstance.compare("=") == 0){
            if(otnode->left->keys.empty()){
                    writetotarget("LOAD", mathit.back(), output);
                    writetotarget("SUB", othervars.back(), output);
                    writetotarget("BRNEG", labelMaker(), output);
                    writetotarget("BRPOS", looper.back(), output);
                    loopflag++;
            }
            else{
                if(otnode->left->keys[0].tokenInstance.compare("<") == 0){
                    writetotarget("LOAD", othervars.rbegin()[1], output);
                    writetotarget("SUB", othervars.back(), output);
                    writetotarget("BRPOS", labelMaker(), output);
                    loopflag++;
                }
                else{
                    writetotarget("LOAD", othervars.rbegin()[1], output);
                    writetotarget("SUB", othervars.back(), output);
                    writetotarget("BRNEG", labelMaker(), output);
                    loopflag++;
                }
            }
        }
    }
}
//count number of mult tokens, then for loop outside compexpr, with mult store load   same for others
void compexpr(Node *treein, std::string output){
    if(treein != nullptr){
        if(treein->names.compare("z") == 0){
            if(!treein->keys.empty()){
                mult++;
                mathit.push_back("MULT");
            }

        }
        if(treein->names.compare("y") == 0){
            if(!treein->keys.empty()){
                diver++;
                mathit.push_back("DIV");
            }
        }
        if(treein->names.compare("x") == 0){
            if(!treein->keys.empty()){
                if(treein->keys[0].tokenInstance.compare("+") == 0){
                    add++;
                    mathit.push_back("ADD");
                }
                else{
                    sub++;
                    mathit.push_back("SUB");
                }
            }
        }
        if(treein->names.compare("r") == 0){
            if(!treein->keys.empty()){
                mathit.push_back(treein->keys[0].tokenInstance);
                nums++;
            }
        }
        
        compexpr(treein->right, output);
        compexpr(treein->left, output);
    }
}
