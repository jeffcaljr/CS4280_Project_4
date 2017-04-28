/**
 * Author: Jeffer Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 04/22/17
 **/

#include "semstack.h"
#include <iostream>

using namespace std;



//********************
//	Constructor
//  Creates a stack of specified size; if size > 100; ends with stackoverflow error
//*********************
SVT::SVT(int size){
	if(size > 100){
		cout << "Error: Stack overflow. Stack size cannot be greater than 100!" << endl;
		exit(0);
	}
	stackArr = new string[size];
	stackSize = size;
	top = -1;
}

//********************
//	Destructor
//  Frees memory allocated to the stack
//*********************
SVT::~SVT(){
	delete [] stackArr;
}

//********************
// Pushes a string onto the stack, if the stack is not full
//*********************
void SVT::push(string tkn){

	if( ! isFull()){
		top++;
		stackArr[top] = tkn;
		// cout << "pushing " << tkn << " at position " << top << endl;
	}
}

//********************
// Pops the top string off of the stack, if the stack is not empty
//*********************
void SVT::pop(){

	if(! isEmpty()){
		top--;
		// cout << "popping stack, top is now " << top << endl;
	}

}

//********************
// Returns the position of the first occurence of the specified string from the top of the stack; -1 if the string is not found in the stack
//*********************
int SVT::find(string tkn){

	int position = -1;

	for(int i = 0, j = top; i <= j; i++){
		if(stackArr[j - i] == tkn){
			position = i;
			// cout << "found " << tkn << " in stack at position " << i <<  endl;
			break;
		}
	}

	if(position == -1){
		// cout << tkn << " not in stack" << endl;
	}

	return position;
}

//********************
// Returns true if the speficied string is contained in the stack; false otherwise
//*********************
bool SVT::verify(string tkn){
	bool isInStack = false;

	if(isEmpty()){
		return false;
	}
	for(int i = top; i > -1; i--){
		if(stackArr[i] == tkn){
			isInStack = true;
			break;
		}
	}

	return isInStack;
}

//********************
// Returns true if the stack is full; false otherwise
//*********************
bool SVT::isFull(){
	return (top == stackSize - 1);
}

//********************
// Returns true if the stack is empty; false otherwise
//*********************
bool SVT::isEmpty(){
	return (top == -1);
}