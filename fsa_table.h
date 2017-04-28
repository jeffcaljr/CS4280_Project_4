/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 03/22/17
 **/
#ifndef FSATABLE_H
#define FSATABLE_H

const int ERROR_INVALID_ALPHABET_CHAR = -2;
const int ERROR_UNRECOGNIZED_CHAR = -1;

enum state{
	INITIAL,
	POSSIBLE_IDENTIFIER,
	POSSIBLE_INTEGER,
	POSSIBLE_EQUALS,
	POSSIBLE_LEFT_BIT_SHIFT,
	POSSIBLE_RIGHT_BIT_SHIFT,
	POSSIBLE_SHIFT,
	POSSIBLE_INEQUALITY,
	POSSIBLE_EQUALITY,
	POSSIBLE_COLON, //TODO: Find a better name
	POSSIBLE_ADDITION,
	POSSIBLE_SUBTRACTION,
	POSSIBLE_MULTIPLICATION,
	POSSIBLE_DIVISION,
	POSSIBLE_AMPERSAND,
	POSSIBLE_MODULO,
	POSSIBLE_DOT,
	POSSIBLE_LEFT_PARENTHESIS,
	POSSIBLE_RIGHT_PARENTHESIS,
	POSSIBLE_COMMA,
	POSSIBLE_LEFT_CURLY_BRACE,
	POSSIBLE_RIGHT_CURLY_BRACE,
	POSSIBLE_SEMICOLON,
	POSSIBLE_LEFT_SQUARE_BRACKET,
	POSSIBLE_RIGHT_SQUARE_BRACKET, 
	EOF_STATE,
	FINAL
};

enum label{
	WS,// \t ' ' \n
	LETTER, //A-Z a-z
	DIGIT, //0-9
	EQUALS,//=
	LEFT_ANGLE_BRACKET,// <
	RIGHT_ANGLE_BRACKET,// >
	NEGATION, // !
	COLON,// :
	PLUS,// +
	MINUS, // -
	MULTIPLICATION,// *
	DIVISION,// /
	AMPERSAND, // &
	MODULO, // %
	DOT, // .
	LEFT_PARENTHESIS, // (
	RIGHT_PARENTHESIS, // )
	COMMA, // ,
	LEFT_CURLY_BRACE, // {
	RIGHT_CURLY_BRACE, // }
	SEMICOLON, // ;
	LEFT_SQUARE_BRACKET, // [
	RIGHT_SQUARE_BRACKET, // ]
	//Comment?
	EOF_LABEL,//
	INVALID
};

//NOTE: It is assumed that FINAL and INVALID are always at the end of
//their respective enums. If so, the following line can 
//determine the number of possible values of their respective enum based on the integer
//value of the last element in them

extern int ** Table;

void printTable();

label getLabelForChar(char c);


#endif