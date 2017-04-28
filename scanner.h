/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/
#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

#include <string>
#include <fstream>

using namespace std;


//attempts to read and return a token from a file
//successive calls returns the subsequent token in a file
token scanner(ifstream&);

#endif