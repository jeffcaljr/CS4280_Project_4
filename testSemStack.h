/**
 * Author: Jeffery Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 04/22/17
 **/
#ifndef TESTSEMSTACK_H
#define TESTSEMSTACK_H

#include "node.h"
#include <fstream>

//perform semantic parsing of parse tree, and generate output file in asm language
void semParser(node*, ofstream &);

#endif