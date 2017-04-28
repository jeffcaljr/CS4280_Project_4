/**
 * Author: Jeffery Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 04/22/17
 **/
#include "testSemStack.h"
#include "parser.h"
#include "token.h"
#include "semstack.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//GLOBAL VARIABLES

static int tempVars = -1; //Temporary vars will all be labeled T# (T0, T1, ... Tn)
static int labelSuffix = 0; //Used to generate unique labels ('LABEL0', 'LABEL1', ... 'LABELn')

static int varCount = 0;	//used to keep track of the number of variables declared in a block; reset when block is exited

SVT svt(100);	//stack for monitoring scopes; can't be more than size 100

//Function Prototypes
void pushIdentifiers(node*, ofstream& output); // pushes a node's identifiers onto the stack (usually just 1 identifier)
int getStackPosition(node*); //finds the position of a label in the stack; throws error if not found
string createTempVar(); //generates a temporary variable name upon being called (ex: 'T1')
string createLabel(); //generates a label name upon being called (ex: 'LABEL1')

//FUNCTION DEFINITIONS

//***************************
//	Auxillary function to perform semantic parsing on a statically-parsed tree
//	attempt to push identifiers for a given node onto the stack, or check if they are already defined before being used
//***************************
void semParser(node* ptr, ofstream& output){	
	if(ptr == NULL){
		return;
	}

	if(ptr->label == "program"){

		semParser(ptr->child1, output);
		semParser(ptr->child2, output);

		//signal end of program; before variable declarations

		output << "STOP" << endl;

		//initialize all temporary variables
		for(int i = tempVars; i >= 0; i--){
			svt.pop();
			output << "T" << i << " 0" << endl;
		}

	}
	else if(ptr->label == "block"){

		//perform local scoping of variable definitions
	
		int tempVarCount = varCount;
		varCount = 0;

		semParser(ptr->child1, output);


		//what to parse next?
		semParser(ptr->child2, output);

		for(int i = 0; i < varCount; i++){
			svt.pop();
			output << "POP" << endl;
		}

		varCount = tempVarCount;

	}
	else if(ptr->label == "vars"){
		pushIdentifiers(ptr, output);

		semParser(ptr->child1, output);

	}
	else if(ptr->label == "mvars"){
		pushIdentifiers(ptr, output);
		semParser(ptr->child1, output);

	}
	else if(ptr->label == "expr"){

		if(ptr->child2 == NULL){
			semParser(ptr->child1, output);
		}
		else{
			semParser(ptr->child2, output);
			string temp = createTempVar();
			output << "STORE " << temp << endl;
			semParser(ptr->child1, output);
			output << "MULT " << temp << endl;
		}
	}
	else if(ptr->label == "m"){

		if(ptr->child2 == NULL){
			semParser(ptr->child1, output);
		}
		else{
			semParser(ptr->child2, output);
			string temp = createTempVar();
			output << "STORE " << temp << endl;
			semParser(ptr->child1, output);
			output << "DIV " << temp << endl;
		}

	}
	else if(ptr->label == "t"){


		if(ptr->child2 == NULL){
			semParser(ptr->child1, output);
		}
		else{
			semParser(ptr->child2, output);
			string temp = createTempVar();
			output << "STORE " << temp << endl;
			semParser(ptr->child1, output);

			if(((ptr->tkns).at(0)).id == PLUS_tk ){
				output << "ADD " << temp << endl;
			}
			else{
				output << "SUB " << temp << endl;
			}

		}

	}
	else if(ptr->label == "f"){

		if((ptr->child1)->label == "f"){

			semParser(ptr->child1, output);

			output << "MULT -1" << endl;
		}
		else{
			semParser(ptr->child1, output);
		}

	}
	else if(ptr->label == "r"){

		if(ptr->child1 != NULL){
			semParser(ptr->child1, output);
		}
		else{

			if((ptr->tkns).at(0).id == NUM_tk){
				output << "LOAD " << ((ptr->tkns).at(0)).instanceWord << endl;
			}
			else{
				int position = getStackPosition(ptr);
				output << "STACKR " << position << endl;
			}
		}


	}

	//The following are possible nodes, but are handled in the "else" case
	//Left in code for possible future changes

	// else if(ptr->label == "stats"){

	// 	semParser(ptr->child1, output);
	// 	semParser(ptr->child2, output);

	// }
	// else if(ptr->label == "mStat"){

	// 	semParser(ptr->child1, output);
	// 	semParser(ptr->child2, output);

	// }
	// else if(ptr->label == "stat"){

	// 	semParser(ptr->child1, output);

	// }
	else if(ptr->label == "in"){

		int position = getStackPosition(ptr);

		string temp = createTempVar();

		output << "READ " << temp << endl;
		output << "LOAD " << temp << endl;
		output << "STACKW " << position << endl;
		
	}
	else if(ptr->label == "out"){

		semParser(ptr->child1, output);

		string temp = createTempVar();
		output << "STORE " << temp << endl;
		output << "WRITE " << temp << endl;

	}
	else if(ptr->label == "If"){

		semParser(ptr->child3, output);

		string temp = createTempVar();
		output << "STORE " << temp << endl;

		semParser(ptr->child1, output);

		output << "SUB " << temp << endl;

		string label = createLabel();

		if((ptr->child2)->tkns.at(0).id == LEFT_BITSHIFT_tk) {
			if((ptr->child2)->tkns.size() > 1 && (ptr->child2)->tkns.at(1).id == EQUALS_tk){
				// << =
				output << "BRPOS " << label << endl;
			}
			else{
				// <<
				output << "BRZPOS " << label << endl;
			}
        }
        else if((ptr->child2)->tkns.at(0).id == RIGHT_BITSHIFT_tk) {
        	if((ptr->child2)->tkns.size() > 1 && (ptr->child2)->tkns.at(1).id == EQUALS_tk){
				// >> =
				output << "BRNEG " << label << endl;
			}
			else{
				// >>
				output << "BRZNEG " << label << endl;
			}     
        }
        else if((ptr->child2)->tkns.at(0).id == EQUALITY_tk) {
            output << "BRPOS " << label << endl;
            output << "BRNEG " << label << endl;
        }
        else if((ptr->child2)->tkns.at(0).id == INEQUALITY_tk) {
            output << "BRZERO " << label << endl;
        }
		else{
			cout << "ERROR: didn't handle this RO in If node???" << endl;
			exit(1);
		}

		semParser(ptr->child4, output);
		output << label << ": NOOP" << endl;

	}
	else if(ptr->label == "loop"){

		string labelStart = createLabel();

		string labelEnd = createLabel();

		output << labelStart << ": NOOP" << endl; //start of loop

		semParser(ptr->child3, output);

		string temp = createTempVar();
		output << "STORE " << temp << endl;

		semParser(ptr->child1, output);

		output << "SUB " << temp << endl;

		//handle relational operator

		if((ptr->child2)->tkns.at(0).id == LEFT_BITSHIFT_tk) {
			if((ptr->child2)->tkns.size() > 1 && (ptr->child2)->tkns.at(1).id == EQUALS_tk){
				// << =
				output << "BRPOS " << labelEnd << endl;
			}
			else{
				// <<
				output << "BRZPOS " << labelEnd << endl;
			}
        }
        else if((ptr->child2)->tkns.at(0).id == RIGHT_BITSHIFT_tk) {
        	if((ptr->child2)->tkns.size() > 1 && (ptr->child2)->tkns.at(1).id == EQUALS_tk){
				// >> =
				output << "BRNEG " << labelEnd << endl;

			}
			else{
				// >>
				output << "BRZNEG " << labelEnd << endl;
			}     
        }
        else if((ptr->child2)->tkns.at(0).id == EQUALITY_tk) {
            output << "BRPOS " << labelEnd << endl;
            output << "BRNEG " << labelEnd << endl;
        }
        else if((ptr->child2)->tkns.at(0).id == INEQUALITY_tk) {
            output << "BRZERO " << labelEnd << endl;
        }
        else{
			cout << "ERROR: didn't handle this RO in loop node???" << endl;
			exit(1);
		}


		semParser(ptr->child4, output);

		output << "BR " << labelStart << endl;

		output << labelEnd << ": NOOP" << endl; //end of loop


	}
	else if(ptr->label == "assign"){

		semParser(ptr->child1, output);

		int position = getStackPosition(ptr);

		output << "STACKW " << position << endl;

	}
	//Relational operators handled inside 'If' and 'loop'
	// else if(ptr->label == "ro"){

	// }
	else{
		semParser(ptr->child1, output);
		semParser(ptr->child2, output);
		semParser(ptr->child3, output);
		semParser(ptr->child4, output);
	}
}


//***************************
//	Push a node's variable declarations onto the stack; throwing an error if they were already defined
//***************************
void pushIdentifiers(node* ptr, ofstream& output){
	for(vector<token>::iterator i = (ptr->tkns).begin(); i != (ptr->tkns).end(); ++i){
			string instance = (*i).instanceWord;
			//if the variable is not yet defined

			if(varCount > 0){ //there are variables defined in this block
				int position = svt.find(instance); //find possible position of this variable in the stack
				if(position >= 0 && position < varCount){ //if this variable is defined in the current scope, throw an error
					cout << "Error: " << instance << " already defined in this scope!" << endl;
					exit(1);
				}
			}
			svt.push(instance);
			output << "PUSH" << endl;

			varCount++;
			
		}
}


//***************************
//	Check if a node's variables were already defined; exiting with an error if they were not
//***************************
int getStackPosition(node* ptr){
	int position = -1; //should never be returned

	for(vector<token>::iterator i = (ptr->tkns).begin(); i != (ptr->tkns).end(); ++i){
		//if the token is a number, no need to be defined

		string instance = (*i).instanceWord;

		position = svt.find(instance);

		if(position == -1){
			if( ! svt.verify(instance) ){
				cout << "Error: " << instance << " was used without being defined!" << endl;
				exit(1);
			}
		}
		return position;
	}

	return position; //control should never reach this point
}

//***************************
//	Generate a temporary variable name of the form 'T#'
//***************************
string createTempVar(){
	ostringstream oss;
	tempVars++;
	oss << "T" << tempVars;
	return oss.str();
}

//***************************
//	Generate a label name of the form 'LABEL#'
//***************************
string createLabel(){
	ostringstream oss;
	oss << "LABEL" << labelSuffix;
	labelSuffix++;
	return oss.str();
}

