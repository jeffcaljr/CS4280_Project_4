/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "token.h"
#include "node.h"

using namespace std;


node* parser(ifstream& file);

#endif