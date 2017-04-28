/**
 * Author: Jeffery Calhoun
 * Course: CS 4280 (5:30-6:45PM)
 * Date: 04/22/17
 **/

#include "fsa_table.h"
#include "scanner.h"
#include "token.h"
#include "node.h"
#include "parser.h"
#include "semstack.h"
#include "treePrint.h"
#include "testSemStack.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


//Global Variables
const string INPUT_FILE_EXTENSION = ".4280E01";
const string TEMPORARY_FILE_NAME = "keyboard" + INPUT_FILE_EXTENSION; //output file created for keyboard input
const string OUTPUT_FILE_EXTENSION = ".asm";


/**
* MAIN FUNCTION
**/

int main(int argc, char** argv){

	// printTable();

	//determine if input should come from keyboard or file

	string inputFilename;
	string inputFilenameNoExtension;

	if(argc == 1){
		//keyboard input

		ofstream tempfile;
		tempfile.open(TEMPORARY_FILE_NAME.c_str(), fstream::out);

		if( ! tempfile.good()){
			perror("Error creating temporary file for keyboard input");
			exit(1);
		}

		string word;
		char c;

		///read lines from keyboard until the user signals EOF

		while(getline(cin, word)){
			tempfile << word << "\n";
		}

		tempfile.close();

		inputFilename = TEMPORARY_FILE_NAME;
		inputFilenameNoExtension = "out";
	}
	else if(argc == 2){
		//file input
		inputFilenameNoExtension = string(argv[1]);
		inputFilename = string(argv[1]) + INPUT_FILE_EXTENSION;	
		
	}
	else{
		//invalid number of arguments
		perror("Invalid number of arguments...");
		exit(1);
	}

	ifstream inputfile;
	inputfile.open(inputFilename.c_str(), fstream::in);

	//verify that the input file is opened and readable, or exit with error

	if(! inputfile.good() || ! inputfile.is_open()){
		perror("Cannot read from input file");
		exit(1);
	}

	//create the generated output file 
	ofstream assemblyOutputFile;
	assemblyOutputFile.open(inputFilenameNoExtension + OUTPUT_FILE_EXTENSION, fstream::out);

	

	node* tree = parser(inputfile);

	// traversePreorder(tree);

	//perform semantic parsing of the statically-parsed tree
	semParser(tree, assemblyOutputFile);

	cout << "Parse successful." << endl;
	

	inputfile.close();
	assemblyOutputFile.close();

	return 0;
}


