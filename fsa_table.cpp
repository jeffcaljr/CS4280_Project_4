/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/
#include "fsa_table.h"
#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std; //only used for debugging in printTable; delete later

//FUNCTION PROTOTYPES
int** initializeTable();


//GLOBALS
int ** Table = initializeTable();

//METHOD IMPLEMENTATIONS

int** initializeTable(){

	//create a new table in memory

	int ** Table = 0;
	Table = new int*[FINAL + 1];

	for(int i = 0; i < FINAL + 1; i++){
		Table[i] = new int[INVALID + 1];
	}

	//For most labels (usually operational delimiters with 1 character), there is a standard way to determine transitions:
	//if they are followed by a whitespace or eof, the token can be parsed successfully
	//if they are followed by a character not in the FSA alphabet, there is an error
	//otherwise, if they are followed by any other character in the FSA alphabet, there is an error also 
	for(int state = 0; state < FINAL; state++){
		for(int label = 0; label < INVALID + 1; label++){

			if(state < EOF_STATE && state > POSSIBLE_INTEGER){
				if(label == WS){
					Table[state][label] = FINAL;
				}
				else if(label == EOF_LABEL){
					Table[state][label] = EOF_STATE;
				}
				else if(label == INVALID){
					Table[state][label] = ERROR_UNRECOGNIZED_CHAR;
				}
				else{
					Table[state][label] = ERROR_INVALID_ALPHABET_CHAR;
				}
			}
		}
	}


	//Handle the more unique cases, which are:
	// (Initial state, scanning digit, scanning identifier, scanning token beginning with =, bitshifts, and EOF)


	Table[INITIAL][WS] = INITIAL;
	Table[INITIAL][LETTER] =  POSSIBLE_IDENTIFIER;
	Table[INITIAL][DIGIT] = POSSIBLE_INTEGER;
	Table[INITIAL][EQUALS] = POSSIBLE_EQUALS;
	Table[INITIAL][LEFT_ANGLE_BRACKET] = POSSIBLE_LEFT_BIT_SHIFT;
	Table[INITIAL][RIGHT_ANGLE_BRACKET] = POSSIBLE_RIGHT_BIT_SHIFT;
	Table[INITIAL][NEGATION] = ERROR_INVALID_ALPHABET_CHAR;
	Table[INITIAL][COLON] = POSSIBLE_COLON;
	Table[INITIAL][PLUS] = POSSIBLE_ADDITION;
	Table[INITIAL][MINUS] = POSSIBLE_SUBTRACTION;
	Table[INITIAL][MULTIPLICATION] = POSSIBLE_MULTIPLICATION;
	Table[INITIAL][DIVISION] = POSSIBLE_DIVISION;
	Table[INITIAL][AMPERSAND] = POSSIBLE_AMPERSAND;
	Table[INITIAL][MODULO] = POSSIBLE_MODULO;
	Table[INITIAL][DOT] = POSSIBLE_DOT;
	Table[INITIAL][LEFT_PARENTHESIS] = POSSIBLE_LEFT_PARENTHESIS;
	Table[INITIAL][RIGHT_PARENTHESIS] = POSSIBLE_RIGHT_PARENTHESIS;
	Table[INITIAL][COMMA] = POSSIBLE_COMMA;
	Table[INITIAL][LEFT_CURLY_BRACE] = POSSIBLE_LEFT_CURLY_BRACE;
	Table[INITIAL][RIGHT_CURLY_BRACE] = POSSIBLE_RIGHT_CURLY_BRACE;
	Table[INITIAL][SEMICOLON] = POSSIBLE_SEMICOLON;
	Table[INITIAL][LEFT_SQUARE_BRACKET] = POSSIBLE_LEFT_SQUARE_BRACKET;
	Table[INITIAL][RIGHT_SQUARE_BRACKET] = POSSIBLE_RIGHT_SQUARE_BRACKET;
	Table[INITIAL][EOF_LABEL] = EOF_STATE;
	Table[INITIAL][INVALID] = ERROR_UNRECOGNIZED_CHAR;

	Table[POSSIBLE_IDENTIFIER][WS] = FINAL;
	Table[POSSIBLE_IDENTIFIER][LETTER] =  POSSIBLE_IDENTIFIER;
	Table[POSSIBLE_IDENTIFIER][DIGIT] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][EQUALS] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][LEFT_ANGLE_BRACKET] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][RIGHT_ANGLE_BRACKET] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][NEGATION] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][COLON] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][PLUS] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][MINUS] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][MULTIPLICATION] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][DIVISION] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][AMPERSAND] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][MODULO] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][DOT] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][LEFT_PARENTHESIS] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][RIGHT_PARENTHESIS] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][COMMA] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][LEFT_CURLY_BRACE] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][RIGHT_CURLY_BRACE] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][SEMICOLON] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][LEFT_SQUARE_BRACKET] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][RIGHT_SQUARE_BRACKET] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_IDENTIFIER][EOF_LABEL] = EOF_STATE;
	Table[POSSIBLE_IDENTIFIER][INVALID] = ERROR_UNRECOGNIZED_CHAR;

	Table[POSSIBLE_INTEGER][WS] = FINAL;
	Table[POSSIBLE_INTEGER][LETTER] = ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][DIGIT] = POSSIBLE_INTEGER;
	Table[POSSIBLE_INTEGER][EQUALS] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][LEFT_ANGLE_BRACKET] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][RIGHT_ANGLE_BRACKET] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][NEGATION] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][COLON] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][PLUS] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][MINUS] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][MULTIPLICATION] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][DIVISION] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][AMPERSAND] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][MODULO] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][DOT] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][LEFT_PARENTHESIS] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][RIGHT_PARENTHESIS] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][COMMA] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][LEFT_CURLY_BRACE] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][RIGHT_CURLY_BRACE] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][SEMICOLON] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][LEFT_SQUARE_BRACKET] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][RIGHT_SQUARE_BRACKET] =  ERROR_INVALID_ALPHABET_CHAR;
	Table[POSSIBLE_INTEGER][EOF_LABEL] = EOF_STATE;
	Table[POSSIBLE_INTEGER][INVALID] = ERROR_UNRECOGNIZED_CHAR;

	Table[POSSIBLE_EQUALS][EQUALS] = POSSIBLE_EQUALITY;
	Table[POSSIBLE_EQUALS][NEGATION] = POSSIBLE_INEQUALITY;


	
	Table[POSSIBLE_LEFT_BIT_SHIFT][LEFT_ANGLE_BRACKET] = POSSIBLE_SHIFT;
	Table[POSSIBLE_LEFT_BIT_SHIFT][WS] = ERROR_INVALID_ALPHABET_CHAR;

	Table[POSSIBLE_RIGHT_BIT_SHIFT][RIGHT_ANGLE_BRACKET] = POSSIBLE_SHIFT;
	Table[POSSIBLE_RIGHT_BIT_SHIFT][WS] = ERROR_INVALID_ALPHABET_CHAR;

	Table[EOF_STATE][WS] = FINAL;
	Table[EOF_STATE][LETTER] = FINAL;
	Table[EOF_STATE][DIGIT] = FINAL;
	Table[EOF_STATE][EQUALS] = FINAL;
	Table[EOF_STATE][LEFT_ANGLE_BRACKET] = FINAL;
	Table[EOF_STATE][RIGHT_ANGLE_BRACKET] = FINAL;
	Table[EOF_STATE][NEGATION] = FINAL;
	Table[EOF_STATE][COLON] = FINAL;
	Table[EOF_STATE][PLUS] = FINAL;
	Table[EOF_STATE][MINUS] = FINAL;
	Table[EOF_STATE][MULTIPLICATION] = FINAL;
	Table[EOF_STATE][DIVISION] = FINAL;
	Table[EOF_STATE][AMPERSAND] = FINAL;
	Table[EOF_STATE][MODULO] = FINAL;
	Table[EOF_STATE][DOT] = FINAL;
	Table[EOF_STATE][LEFT_PARENTHESIS] = FINAL;
	Table[EOF_STATE][RIGHT_PARENTHESIS] = FINAL;
	Table[EOF_STATE][COMMA] = FINAL;
	Table[EOF_STATE][LEFT_CURLY_BRACE] = FINAL;
	Table[EOF_STATE][RIGHT_CURLY_BRACE] = FINAL;
	Table[EOF_STATE][SEMICOLON] = FINAL;
	Table[EOF_STATE][LEFT_SQUARE_BRACKET] = FINAL;
	Table[EOF_STATE][RIGHT_SQUARE_BRACKET] = FINAL;
	Table[EOF_STATE][EOF_LABEL] = FINAL;
	Table[EOF_STATE][INVALID] = FINAL;

	Table[FINAL][WS] = INITIAL;
	Table[FINAL][LETTER] =  POSSIBLE_IDENTIFIER;
	Table[FINAL][DIGIT] = POSSIBLE_INTEGER;
	Table[FINAL][EQUALS] = POSSIBLE_EQUALS;
	Table[FINAL][LEFT_ANGLE_BRACKET] = POSSIBLE_LEFT_BIT_SHIFT;
	Table[FINAL][RIGHT_ANGLE_BRACKET] = POSSIBLE_RIGHT_BIT_SHIFT;
	Table[FINAL][NEGATION] = ERROR_INVALID_ALPHABET_CHAR;
	Table[FINAL][COLON] = POSSIBLE_COLON;
	Table[FINAL][PLUS] = POSSIBLE_ADDITION;
	Table[FINAL][MINUS] = POSSIBLE_SUBTRACTION;
	Table[FINAL][MULTIPLICATION] = POSSIBLE_MULTIPLICATION;
	Table[FINAL][DIVISION] = POSSIBLE_DIVISION;
	Table[FINAL][AMPERSAND] = POSSIBLE_AMPERSAND;
	Table[FINAL][MODULO] = POSSIBLE_MODULO;
	Table[FINAL][DOT] = POSSIBLE_DOT;
	Table[FINAL][LEFT_PARENTHESIS] = POSSIBLE_LEFT_PARENTHESIS;
	Table[FINAL][RIGHT_PARENTHESIS] = POSSIBLE_RIGHT_PARENTHESIS;
	Table[FINAL][COMMA] = POSSIBLE_COMMA;
	Table[FINAL][LEFT_CURLY_BRACE] = POSSIBLE_LEFT_CURLY_BRACE;
	Table[FINAL][RIGHT_CURLY_BRACE] = POSSIBLE_RIGHT_CURLY_BRACE;
	Table[FINAL][SEMICOLON] = POSSIBLE_SEMICOLON;
	Table[FINAL][LEFT_SQUARE_BRACKET] = POSSIBLE_LEFT_SQUARE_BRACKET;
	Table[FINAL][RIGHT_SQUARE_BRACKET] = POSSIBLE_RIGHT_SQUARE_BRACKET;
	Table[FINAL][EOF_LABEL] = EOF_STATE;
	Table[FINAL][INVALID] = ERROR_UNRECOGNIZED_CHAR;

	return Table;
}

//Accepts a character c and returns the appropriate FSA label for it

label getLabelForChar(char c){
	if(isspace(c)){ //WS
		return WS;
	}
	else if(isalpha(c)){ //letter
		return LETTER;
	}
	else if(isdigit(c)){ //digit
		return DIGIT;
	}
	else if(c == '='){ // =
		return EQUALS;
	}
	else if(c == '<'){ // <
		return LEFT_ANGLE_BRACKET;
	}
	else if(c == '>'){ // >
		return RIGHT_ANGLE_BRACKET;
	}
	else if(c == '!'){ // !
		return NEGATION;
	}
	else if(c == ':'){ // :
		return COLON;
	}
	else if(c == '+'){ // +
		return PLUS;
	}
	else if(c == '-'){ // -
		return MINUS;
	}
	else if(c == '*'){ // *
		return MULTIPLICATION;
	}
	else if(c == '/'){ // /
		return DIVISION;
	}
	else if(c == '&'){ // &
		return AMPERSAND;
	}
	else if(c == '%'){ // %
		return MODULO;
	}
	else if(c == '.'){ // .
		return DOT;
	}
	else if(c == '('){ // (
		return LEFT_PARENTHESIS;
	}
	else if(c == ')'){ // )
		return RIGHT_PARENTHESIS;
	}
	else if(c == ','){ // ,
		return COMMA;
	}
	else if(c == '{'){ // {
		return LEFT_CURLY_BRACE;
	}
	else if(c == '}'){ // }
		return RIGHT_CURLY_BRACE;
	}
	else if(c == ';'){ // ;
		return SEMICOLON;
	}
	else if(c == '['){ // [
		return LEFT_SQUARE_BRACKET;
	}
	else if(c == ']'){ // ]
		return RIGHT_SQUARE_BRACKET;
	}
	else if(c == char_traits<char>::eof()){ // EOF
		return EOF_LABEL;
	}
	else{
		return INVALID;
	}
}


//For debugging; prints FSA transition table 
void printTable(){
	cout << setw(6) << " " 
		 << setw(6) << "WS" 
		 << setw(6) << "L" 
		 << setw(6) << "D" 
		 << setw(6) << "=" 
		 << setw(6) << "<" 
		 << setw(6) << ">"
		 << setw(6) << "!" 
		 << setw(6) << ":" 
		 << setw(6) << "+" 
		 << setw(6) << "-" 
		 << setw(6) << "*" 
		 << setw(6) << "/" 
		 << setw(6) << "&" 
		 << setw(6) << '%' 
		 << setw(6) << "."
		 << setw(6) << "(" 
		 << setw(6) << ")" 
		 << setw(6) << "," 
		 << setw(6) << "{" 
		 << setw(6) << "}" 
		 << setw(6) << ";" 
		 << setw(6) << "[" 
		 << setw(6) << "]" 
		 << setw(6) << "EOF" 
		 <<setw(6) << "?"
		 << endl;

		 for(int i = 0; i < FINAL + 1; i++){
		 	cout << setw(6) << i;
		 	for(int j = 0; j < INVALID + 1; j++){
		 		int state = Table[i][j];

		 		if(state == FINAL){
		 			cout << setw(6) << 'F';
		 		}
		 		else if(state == -2){
		 			cout << setw(6) << "ERR1";
		 		}
		 		else if(state == -1){
		 			cout << setw(6) << "ERR2";
		 		}
		 		else{
		 			cout << setw(6) << state;
		 		}
		 		// cout << setw(6) << (Table[i][j] == FINAL ? 'F' : Table[i][j]);
		 	} 
		 	cout << endl;
		 }

		 cout << endl;
		 cout << "ERR1 = Character in FSA alphabet, but not acceptable in current state" << endl;
		 cout << "ERR2 = Character not in FSA alphabet; considered 'other'" << endl;
		 cout << "F = Final state; should have derived a token of some sort" << endl;
		 cout << endl << endl;
}
