/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 04/14/2017
 **/
#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <string>
#include <vector>

typedef struct Node{
	string label;
	vector<token> tkns;
	Node* child1;
	Node* child2;
	Node* child3;
	Node* child4;
} node;


#endif