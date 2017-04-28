/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/

#include "parser.h"
#include "scanner.h"
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

static token tkn;


//FUNCTION PROTOTYPES
node* program(ifstream&);
node* block(ifstream&);
node* vars(ifstream&);
node* mvars(ifstream&);
node* expr(ifstream&);
node* m(ifstream&);
node* t(ifstream&);
node* f(ifstream&);
node* r(ifstream&);
node* stats(ifstream&);
node* mStat(ifstream&);
node* stat(ifstream&);
node* in(ifstream&);
node* out(ifstream&);
node* If(ifstream&);
node* loop(ifstream&);
node* assign(ifstream&);
node* ro(ifstream&);
void error(string errorMessage);
node* generateNode(string label);



//FUNCTION DEFINITIONS
node* parser(ifstream& file){
	node* tree;

	tkn = scanner(file);
	tree = program(file);
	if(tkn.id != EOF_tk){
		error("Program was not parsed successfully");
	}
	
	return tree;
}


//CFG PARSING FUNCTIONS
node* program(ifstream& file){

	node* newNode = generateNode("program");

	if(tkn.id != PROGRAM_tk){
		error("Expected 'program'");
	}
	tkn = scanner(file);
	newNode->child1 = vars(file);
	newNode->child2 = block(file);
	return newNode;
}

node* vars(ifstream& file){

	node* newNode = generateNode("vars");


	if(tkn.id != INT_tk){
		return newNode; //Should i return null?
	}
	else{
		tkn = scanner(file);
		if(tkn.id == IDENT_tk){
			(newNode->tkns).push_back(tkn);
			tkn = scanner(file);
			newNode->child1 = mvars(file);
			return newNode;
		}
		else{
			error("Expected idenfifier");
		}
	}
}

node* block(ifstream& file){

	node* newNode = generateNode("block");

	if(tkn.id == START_tk){
		tkn = scanner(file);
		newNode->child1 = vars(file);
		newNode->child2 = stats(file);
		if(tkn.id == STOP_tk){
			tkn = scanner(file);
			return newNode;
		}
		else{
			error("Expected 'stop'");
		}
	}
	else{
		error("Expected 'start'");
	}
}

node* mvars(ifstream& file){

	node* newNode = generateNode("mvars");

	if(tkn.id == COLON_tk){
		tkn = scanner(file);
		if(tkn.id == IDENT_tk){

			(newNode->tkns).push_back(tkn);

			tkn = scanner(file);
			newNode->child1 = mvars(file);
			return newNode;
		}
		else{
			error("Expected identifier");
		}
	}
	else{
		return newNode; //should I return null?
	}

}

node* expr(ifstream& file){

	node* newNode = generateNode("expr");

	newNode->child1 = m(file);

	if(tkn.id == MULTIPLICATION_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		newNode->child2 = expr(file);
	}
	return newNode;
}

node* m(ifstream& file){

	node* newNode = generateNode("m");

	newNode->child1 = t(file);

	if(tkn.id == DIVISION_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		newNode->child2 = m(file);
	}

	return newNode;
}

node* t(ifstream& file){

	node* newNode = generateNode("t");

	newNode->child1 = f(file);

	if(tkn.id == PLUS_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		newNode->child2 =  t(file);
	}
	else if(tkn.id == MINUS_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		newNode->child2 = t(file);
	}
	return newNode;
}

node* f(ifstream& file){

	node* newNode = generateNode("f");

	if(tkn.id == AMPERSAND_tk){
		tkn = scanner(file);
		newNode->child1 = f(file);
	}
	else{
		newNode->child1 = r(file);
	}

	return newNode;
}

node* r(ifstream& file){

	node* newNode = generateNode("r");

	if(tkn.id == LEFT_PARENTHESIS_tk){
		tkn = scanner(file);
		newNode->child1 = expr(file);
		if(tkn.id == RIGHT_PARENTHESIS_tk){
			tkn = scanner(file);
			return newNode;
		}
		else{
			error("Expected ')'");
		}
	}
	else if(tkn.id == IDENT_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		return newNode;
	}
	else if(tkn.id == NUM_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		return newNode;
	}
	else{
		error("Expected '(', identifier, or number");
	}
}

node* stats(ifstream& file){
	node* newNode = generateNode("stats");
	newNode->child1 = stat(file);
	newNode->child2 = mStat(file);
	return newNode;
}

node* mStat(ifstream& file){

	node* newNode = generateNode("mStat");
	
	if(tkn.id != READ_tk
		&& tkn.id != PRINT_tk
		&& tkn.id != START_tk
		&& tkn.id != DEC_tk
		&& tkn.id != WHILE_tk
		&& tkn.id != IDENT_tk){
		
		return newNode; //Should i return null?
	}
	else{
		newNode->child1 = stat(file);
		newNode->child2 = mStat(file);
		return newNode;
	}
}

node* stat(ifstream& file){

	node* newNode = generateNode("stat");

	if(tkn.id == READ_tk){
		newNode->child1 = in(file);
		return newNode;
	}
	else if(tkn.id == PRINT_tk){
		newNode->child1 = out(file);
		return newNode;
	}
	else if(tkn.id == START_tk){
		newNode->child1 = block(file);
		return newNode;
	}
	else if(tkn.id == DEC_tk){
		newNode->child1 = If(file);
		return newNode;
	}
	else if(tkn.id == WHILE_tk){
		newNode->child1 = loop(file);
		return newNode;
	}
	else if(tkn.id == IDENT_tk){
		newNode->child1 = assign(file);
		return newNode;
	}
	else{
		error("Expected statement");
	}
}

node* in(ifstream& file){

	node* newNode = generateNode("in");

	if(tkn.id == READ_tk){
		tkn = scanner(file);
		if(tkn.id == RIGHT_BITSHIFT_tk){
			tkn = scanner(file);
			if(tkn.id == IDENT_tk){
				(newNode->tkns).push_back(tkn);
				tkn = scanner(file);
				if(tkn.id == SEMICOLON_tk){
					tkn = scanner(file);
					return newNode;
				}
				else{
					error("Expected ';'");
				}
			}
			else{
				error("Expected identifier");
			}
		}
		else{
			error("Expected '>>'");
		}
	}
	else{
		error("Expected 'read'");
	}
}

node* out(ifstream& file){

	node* newNode = generateNode("out");

	if(tkn.id == PRINT_tk){
		tkn = scanner(file);
		if(tkn.id == LEFT_BITSHIFT_tk){
			tkn = scanner(file);
			newNode->child1 = expr(file);
			return newNode;
		}
		else{
			error("Expected '<<");
		}
	}
	else{
		error("Expected 'print");
	}
}

node* If(ifstream& file){

	node* newNode = generateNode("If");

	if(tkn.id == DEC_tk){
		tkn = scanner(file);
		if(tkn.id == LEFT_PARENTHESIS_tk){
			tkn = scanner(file);
			newNode->child1 = expr(file);
			newNode->child2 = ro(file);
			newNode->child3 = expr(file);
			if(tkn.id == RIGHT_PARENTHESIS_tk){
				tkn = scanner(file);
				newNode->child4 = block(file);
				return newNode;
			}
			else{
				error("Expected ')'");
			}
		}
		else{
			error("Expected '('");
		}
	}
	else{
		error("Expected 'decision'");
	}
}

node* loop(ifstream& file){

	node* newNode = generateNode("loop");

	if(tkn.id == WHILE_tk){
		tkn = scanner(file);
		if(tkn.id == LEFT_PARENTHESIS_tk){
			tkn = scanner(file);
			newNode->child1 = expr(file);
			newNode->child2 = ro(file);
			newNode->child3 = expr(file);
			if(tkn.id == RIGHT_PARENTHESIS_tk){
				tkn = scanner(file);
				newNode->child4 = block(file);
				return newNode;
			}
			else{
				error("Expected ')'");
			}
		}
		else{
			error("Expected '('");
		}
	}
	else{
		error("Expected 'while'");
	}
}

node* assign(ifstream& file){

	node* newNode = generateNode("assign");

	if(tkn.id == IDENT_tk){

		(newNode->tkns).push_back(tkn);

		tkn = scanner(file);
		if(tkn.id == EQUALS_tk){
			tkn = scanner(file);
			newNode->child1 = expr(file);
			if(tkn.id == SEMICOLON_tk){
				tkn = scanner(file);
				return newNode;
			}
			else{
				error("Expected ';'");
			}
		}
		else{
			error("Expected '='");
		}
	}
	else{
		error("Expected identifier");
	}
}

node* ro(ifstream& file){


	node* newNode = generateNode("ro");

	if(tkn.id == LEFT_BITSHIFT_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		if(tkn.id == EQUALS_tk){
			(newNode->tkns).push_back(tkn);
			tkn = scanner(file);
		}
		return newNode; //FIXME: need to determine if << or <<= was relational operator 
	}
	else if(tkn.id == RIGHT_BITSHIFT_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		if(tkn.id == EQUALS_tk){
			(newNode->tkns).push_back(tkn);
			tkn = scanner(file);
		}
		return newNode; //FIXME: need to determine if >> or >>= was relational operator 
	}
	else if(tkn.id == EQUALITY_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		return newNode;
	}
	else if(tkn.id == INEQUALITY_tk){
		(newNode->tkns).push_back(tkn);
		tkn = scanner(file);
		return newNode;
	}
	else{
		error("Expected relational operator");
	}
}

//Prints error message and token info
void error(string errorMessage){
	ostringstream oss;
	oss << "Error at line " << tkn.line << ": " << errorMessage << " Found " << tkn.name; 
	perror(oss.str().c_str());
	exit(1);
}

//generates a new, initialized node
node* generateNode(string label){
	node * newNode = new node();

	newNode->label = label;
	newNode->child1 = NULL;
	newNode->child2 = NULL;
	newNode->child3 = NULL;
	newNode->child4 = NULL;

	return newNode;
}
