/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/
#include "scanner.h"
#include "fsa_table.h"
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm> //used for find method

using namespace std;

//FUNCTION PROTOTYPES
bool commentCheck(const char c);
token tokenBuilder(int state, string tokenText, int line);


//GLOBALS
const char COMMENT_START_DELIMITER = '#';
const int num_keywords = 10; //number of keywords specified for this language
//Array of keywords used to build vector of keywords
const string keywordsArray[] = {"start", "stop", "decision", "while", "void", "int", "return", "read", "print", "program"};
const vector<string> keyWords(keywordsArray, keywordsArray + num_keywords); //vector used instead of array for 'find()' method for searching keywords


//METHOD IMPLEMENTATIONS

//Reads an open file for a word, and parses it into a token
token scanner(ifstream& file){


	static int line = 1;

	//read first character from file and determine it's type/label
	static char c = file.get();
	label l = getLabelForChar(c);


	static char lastChar = -1; //keeps track of the previous character read, checking for '\n'

	string word;

	int currentState;
	int nextState;

	currentState = INITIAL;

	while(currentState != EOF_STATE){

		//increment line number if most recently read character was newline

		if(lastChar == '\n'){
			++line;
		}

		//check if current char is the start of a comment
			//if yes
				// 1.skip the rest of the line, 
				// 2. signal that last character read was a newline (for line incrementing)
				// 3.read the next character in the file and get it's appropriate symbol in the FSA table 
				// 4. reset the FSA state (to INITIAL) to start new graph traversal
				// 5. rerun the loop

		if(commentCheck(c)){
			string comment;
			getline(file, comment);
			lastChar = '\n';
			c = file.get();
			l = getLabelForChar(c);
			word = "";
			currentState = INITIAL;
			continue;
		}

		//if no comment was detected, determine the next transition in the FSA table
		
		nextState = Table[currentState][l];

		//if next transition is error due to reading character outside FSA alphabet,
		//print appropriate message to console and exit the program

		if(nextState == ERROR_INVALID_ALPHABET_CHAR){
			ostringstream oss;
			oss << "Scanner error at line " << line << ": ";
			oss <<  c << " is not valid at this state.";
			// string errorString =  "Scanner Error at line " + line + ": ";
			// errorString += c;
			// errorString += " is not valid at this state.";
			perror(oss.str().c_str());
			exit(1);
		}
		//if next transition is error due to reading FSA alphabet character not valid in current "scope"
		//print appropriate message to console and exit the program
		else if(nextState == ERROR_UNRECOGNIZED_CHAR){
			ostringstream oss;
			oss << "Scanner error at line " << line << ": ";
			oss <<  c << " is not in the FSA alphabet!";
			// string errorString = "Scanner Error at line " + line + ": ";
			// errorString += c;
			// errorString += " is not in the FSA alphabet!";
			perror(oss.str().c_str());
			exit(1);
		}
		//if next transition is a FINAL state due to token id being detected,
		//generate the appropriate 
		else if(nextState == FINAL){
			return tokenBuilder(currentState, word, line);
			word = "";
		}
		else if(nextState == EOF_STATE){

			//if there is a word that has yet to be tokenized, and the loop sees file about to end, tokenize the word
			//either way, loop will reach exit condition and stop on the next condition check
			if(word != ""){
				return tokenBuilder(currentState, word, line);
				word = "";
			}
		}
		else{
			if(getLabelForChar(c) != WS){
				word += c;
			}
		}

		currentState = nextState;
		lastChar = c;
		c = file.get();
		l = getLabelForChar(c);
	}

	//loop has detected EOF state and exited
	//finally, return EOF token
	return tokenBuilder(currentState, "", line);

}


/**
*	Checks if given string is a keyword, and returns the appropriate tokenID if so.
*	Otherwise, returns tokenID to denote that given string is recognized as a non-reserved identifier
*/
tokenID checkIsKeyword(string word){

	//search for word in list(vector) of keywords
	vector<string>::const_iterator itr = find(keyWords.begin(), keyWords.end(), word);

	if(itr == keyWords.end()){//not a keyword;
		return IDENT_tk;

	}
	else{
		int keywordIndex = itr - keyWords.begin();

		switch(keywordIndex){
			case 0:
				return START_tk;
			break;
			case 1:
				return STOP_tk;
			break;
			case 2:
				return DEC_tk;
			break;
			case 3:
				return WHILE_tk;
			break;
			case 4:
				return VOID_tk;
			break;
			case 5:
				return INT_tk;
			break;
			case 6:
				return RETURN_tk;
			break;
			case 7:
				return READ_tk;
			break;
			case 8:
				return PRINT_tk;
			break;
			case 9:
				return PROGRAM_tk;
			break;
			default:
				string errorStr = "scanner.cpp: error determining tokenID of " + word;
				perror(errorStr.c_str());
				exit(1);
		}
	}
}


//HELPER FUNCTIONS

/**
*	Helper to construct token objects for scanner
*/

/**
 * Checks if char c is start of comment (Comments start with '#' character)
 */
bool commentCheck(const char c){
	return (c == COMMENT_START_DELIMITER);

}

token tokenBuilder(int state, string tokenText, int line){
	token t;
	bool instanceWordSetFlag = false;

	switch(state){
		case POSSIBLE_IDENTIFIER:
			t.id = checkIsKeyword(tokenText);
			if(t.id == IDENT_tk){
				t.instanceWord = tokenText;
				instanceWordSetFlag = true;
			}
		break;
		case POSSIBLE_INTEGER:
			t.id = NUM_tk;
			t.instanceWord = tokenText;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_EQUALS:
			t.id = EQUALS_tk;
			t.instanceWord = tokenText;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_SHIFT:
			if(tokenText == "<<"){
				t.id = LEFT_BITSHIFT_tk;
				t.instanceWord = tokenText;
				instanceWordSetFlag = true;
			}
			else if(tokenText == ">>"){
				t.id = RIGHT_BITSHIFT_tk;
				t.instanceWord = tokenText;
				instanceWordSetFlag = true;
			}
			else{
				string errorString = "Error parsing token - attempted to process bitshift";
				perror(errorString.c_str());
				exit(1);
			}
		break;
		case POSSIBLE_INEQUALITY:
			t.id = INEQUALITY_tk;
			t.instanceWord = tokenText;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_EQUALITY:
			t.instanceWord = tokenText;
			t.id = EQUALITY_tk; 
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_COLON:
			t.id = COLON_tk;
		break;
		case POSSIBLE_ADDITION:
			t.instanceWord = tokenText;
			t.id = PLUS_tk;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_SUBTRACTION:
			t.instanceWord = tokenText;
			t.id = MINUS_tk;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_MULTIPLICATION:
			t.instanceWord = tokenText;
			t.id = MULTIPLICATION_tk;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_DIVISION:
			t.instanceWord = tokenText;
			t.id = DIVISION_tk;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_AMPERSAND:
			t.id = AMPERSAND_tk;
		break;
		case POSSIBLE_MODULO:
			t.instanceWord = tokenText;
			t.id = MODULO_tk;
			instanceWordSetFlag = true;
		break;
		case POSSIBLE_DOT:
			t.id = DOT_tk;
		break;
		case POSSIBLE_LEFT_PARENTHESIS:
			t.id = LEFT_PARENTHESIS_tk;
		break;
		case POSSIBLE_RIGHT_PARENTHESIS:
			t.id = RIGHT_PARENTHESIS_tk;
		break;
		case POSSIBLE_COMMA:
			t.id = COMMA_tk;
		break;
		case POSSIBLE_LEFT_CURLY_BRACE:
			t.id = LEFT_CURLY_BRACE_tk;
		break;
		case POSSIBLE_RIGHT_CURLY_BRACE:
			t.id = RIGHT_CURLY_BRACE_tk;
		break;
		case POSSIBLE_SEMICOLON:
			t.id = SEMICOLON_tk;
		break;
		case POSSIBLE_LEFT_SQUARE_BRACKET:
			t.id = LEFT_SQUARE_BRACKET_tk;
		break;
		case POSSIBLE_RIGHT_SQUARE_BRACKET:
			t.id = RIGHT_SQUARE_BRACKET_tk;
		break;
		case EOF_STATE:
			t.id = EOF_tk;
		break;
		default:
			string errorString = "Error building token - unrecognized state";
			perror(errorString.c_str());
			exit(1);
	}

	t.name = tokenNames[t.id];
	t.line = line;
	if(!instanceWordSetFlag){
		t.instanceWord = "";
	}
	return t;
}