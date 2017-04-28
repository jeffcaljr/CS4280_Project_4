/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum tokenID {
	IDENT_tk,
	NUM_tk,
	EOF_tk,
	//Keyword Tokens
	START_tk,
	STOP_tk,
	DEC_tk,
	WHILE_tk,
	VOID_tk,
	INT_tk,
	RETURN_tk,
	READ_tk,
	PRINT_tk,
	PROGRAM_tk,
	//operator delimiter tokens
	EQUALS_tk,
	LEFT_BITSHIFT_tk,
	RIGHT_BITSHIFT_tk,
	INEQUALITY_tk,
	EQUALITY_tk,
	COLON_tk,
	PLUS_tk,
	MINUS_tk,
	MULTIPLICATION_tk,
	DIVISION_tk,
	AMPERSAND_tk,
	MODULO_tk,
	DOT_tk,
	LEFT_PARENTHESIS_tk,
	RIGHT_PARENTHESIS_tk,
	COMMA_tk,
	LEFT_CURLY_BRACE_tk,
	RIGHT_CURLY_BRACE_tk,
	SEMICOLON_tk,
	LEFT_SQUARE_BRACKET_tk,
	RIGHT_SQUARE_BRACKET_tk
};

const string tokenNames[] = {
	"Identifier",
	"Number",
	"End of file",
	"Start-Keyword",
	"Stop-Keyword",
	"Decision-Keyword",
	"While-Keyword",
	"Void-Keyword",
	"Int-Keyword",
	"Return-Keyword",
	"Read-Keyword",
	"Print-Keyword",
	"Program-Keyword",
	"Assignment-operator",
	"Left-shift-operator",
	"Right-shift-operator",
	"Inequality-operator",
	"Equality-operator",
	"Colon-operator",
	"Addition-operator",
	"Subtraction-operator",
	"Multiplication-operator",
	"Division-operator",
	"Address-of-operator",
	"Modulo-operator",
	"Dot-operator",
	"Left-parenthesis-operator",
	"Right-parenthesis-operator",
	"Comma-operator",
	"Left-curly-brace-operator",
	"Right-curly-brace-operator",
	"Semicolon-operator",
	"Left-square-bracket-operator",
	"Right-square-bracket-operator"
};

typedef struct token{
	tokenID id;
	string name;
	int line;
	string instanceWord;
} token;

#endif