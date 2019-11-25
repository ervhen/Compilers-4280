//Ervin Hennrich
//cs 4280
//Feb 9, 2019
//Project 0, implementing a BST



#include "node.h"
#include "tree.h"
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]){
	//create the root node for the tree
	Node *root = NULL;
	//initialize strings for input
	std::string stinput;
	std::string inputf_name;
	//setup reading stream
	std::ifstream inputfile;
	
	//file is given
	if (argc == 2){
		stinput = argv[1];
		inputf_name = stinput + ".sp19";

	}//No file given, keyboard option
	else if (argc == 1){
		std::ofstream outputfile;
		inputf_name = ".inputfile.sp19";
		outputfile.open(".inputfile.sp19");
		std::string input;
		while (std::getline(std::cin, input)){
			outputfile << input << std::endl;
    		}
		outputfile.close();
	}
	else {//entered more than 2 args
		std::cout << "Too many arguments" << std::endl;
		return 1;
	}
	
	//open inputfile from above	
	inputfile.open(inputf_name.c_str());
	

	std::string line; 
	//check to make sure its open then read from it into the tree
	if (inputfile.is_open()){
		while(getline(inputfile, line)){
			std::istringstream iss(line);
			while (getline(iss, line, '\t')){
				std::istringstream ss(line);
				while (getline(ss, line, ' ')){
//				line.erase(std::remove(line.begin(),line.end(), '\t'), line.end());   *this line will completely remove tabs, could be good but depends on whether tabs should be treated as spaces or removed (may want) 
					Node *newnode = new Node;
					newnode->key = static_cast<int>(line.length());
					if (newnode->key == 0){
						continue;
					}
					newnode->names = line;
					buildTree(newnode, *&root);
				}
			}
		}
		inputfile.close();
	}
	else {
		std::cout<< "Error: File not open/found (make sure you dont type .sp19)";
		return -1;
	}
	


//creating ofstreams for each file
	std::ofstream out_in;
	std::ofstream out_pre;
	std::ofstream out_post;
	
	std::string out_name_in;
	std::string out_name_pre;
	std::string out_name_post;
	if (argc == 2){
		//creating names for each file
		std::string infile_name = argv[1];	
		std::string inord = ".inorder";
		out_name_in = infile_name + inord;
		std::string pre = ".preorder";
		out_name_pre = infile_name + pre;
		std::string post = ".postorder";
		out_name_post = infile_name + post;
		

	}
	else { //names for each file if input from keyboard
		out_name_in = "out.inorder";
		out_name_pre = "out.preorder";
		out_name_post = "out.postorder";
	}
	
	//opening the streams
	out_in.open(out_name_in.c_str());
	out_pre.open(out_name_pre.c_str());
	out_post.open(out_name_post.c_str());

	//work with the Inorder 
	out_in << std::endl << "Inorder" << std::endl;
	printInorder(root, 0, out_in);
	out_in.close();


	//work with the Preorder
	out_pre << std::endl << "Preorder" << std::endl;
	printPreorder(root, 0, out_pre);
	out_pre.close();

	//work with the Postorder
	out_post << std::endl << "Postorder" << std::endl;
	printPostorder(root, 0, out_post);
	out_post.close();	


return 0;
	
}



