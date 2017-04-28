/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 04/14/2017
 **/
#include "treePrint.h"
#include "token.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


//FUNCTION PROTOTYPES
string formatNodeData(node* nodePtr, int depth);
void traversePreorderHelper(node* nodePtr, int depth);
string tokenToString(token tkn);

//FUNCTION DEFINITIONS
void traversePreorder(node* root){


	traversePreorderHelper(root, 0);

}

//Prints a node and it's children, indented by depth
void traversePreorderHelper(node* nodePtr, int depth){
	if(nodePtr == NULL){
		//do nothing
	}
	else{
		cout << formatNodeData(nodePtr, depth) << endl;
		traversePreorderHelper(nodePtr->child1, depth + 1);
		traversePreorderHelper(nodePtr->child2, depth + 1);
		traversePreorderHelper(nodePtr->child3, depth + 1);
		traversePreorderHelper(nodePtr->child4, depth + 1);
	}
}

//Adds indentation to node based on depth
string formatNodeData(node* nodePtr, int depth){
	ostringstream oss;

	for(int i = 0; i < depth; i++){
		oss << "  ";
	}

	oss << nodePtr->label;

	for(vector<token>::iterator i = (nodePtr->tkns).begin(); i != (nodePtr->tkns).end(); ++i){
		oss << " ";
		oss << tokenToString(*i);
	}
	
		
	return oss.str();

}

//Converts token to a readable string format
string tokenToString(token tkn){
	ostringstream oss;
	if(tkn.instanceWord != ""){
		oss << "TOKEN:: " << tkn.name << ", ";
		oss << "INSTANCE:: " << tkn.instanceWord << ", ";
		// oss << "ID:: ";
		// oss << tkn.id;
		// oss << " ; ";
		oss << "LINE #:: " << tkn.line;
	}

	return oss.str();
}