#include "MorseTree.h"
#include "global.h"

#include <iostream>
#include <cctype>

MorseTree::MorseTree() {	//Constructor
	MorseNode *r;
	r = new MorseNode;
	r->engChar = '\0';	//Root is null character
	r->morse = "";	//Root has no morse representation
	r->parent = NULL;
	r->left = NULL;
	r->right = NULL;
	root = r;
}

MorseTree::~MorseTree() {
}

void MorseTree::buildTree() {	//Add each node
	for (int i = 0; i < 58; i++) {
		addNode(cArray[i], sArray[i]);
	}
	return;
}

void MorseTree::addNode(char inEngChar, std::string inMorse) {	//Add a node
	short int level = -1;	//Level of tree on (0 is root, 1 is children of root, etc)
	
	MorseNode *temp;
	temp = root;
	
	MorseNode *parent;
	parent = NULL;
	
	MorseNode *toAdd;
	toAdd = new MorseNode;
	toAdd->engChar = inEngChar;
	toAdd->morse = inMorse;
	toAdd->parent = NULL;
	toAdd->left = NULL;
	toAdd->right = NULL;
	
	while (temp != NULL) {	//Find parent node
		level++;
		parent = temp;
		if (toAdd->morse[level] == '.')	//Dots to left
			temp = temp->left;
		else if (toAdd->morse[level] == '-')	//Dashes to right
			temp = temp->right;
		else
			return; //Ya done messed up, just give up now
	}
	
	if (toAdd->morse[level] == '.')	//Add to left
		parent->left = toAdd;
	else	//Add to right
		parent->right = toAdd;
	
	toAdd->parent = parent;
	
	return;
}

std::vector<short int> MorseTree::createTimings(std::string input, bool inMorse) {	//Create timings for sine wave of WAV file
	std::vector<short int> outVec;
	
	if (!inMorse)	//If not in morse code, translate it to morse code
		input = engToMorse(input);
	
	for (int i = 0; i < input.length(); i++) {	//For each element of input ('.', '-', ' ', or '/')
		if (input[i] == '.') {	//Dot
			outVec.push_back(1);	//One dot period of sound
			if (input[i+1] == '/' || input[i+1] == ' ' || i == input.length()-1) {	//FUTURE EDIT: change to if (!(input[i+1] == '/' || .....)) {outVec.push_back(-1)}
			} else {
				outVec.push_back(-1);	//One dot period of silence	
			}
		} else if (input[i] == '-') {	//Dash
			outVec.push_back(3);	//Three dot periods of sound
			if (input[i+1] == '/' || input[i+1] == ' ' || i == input.length()-1) {
			} else {
				outVec.push_back(-1);	//One dot period of silence	
			}
		} else if (input[i] == '/') {	//Space between letters
			outVec.push_back(-3);
		} else if (input[i] == ' ') {	//Space between words
			outVec.push_back(-7);
		}
	}
	return outVec;
}

std::string MorseTree::inverseTimings(std::vector <short int> inTiming) {	//Convert timings from sine wave to morse code;
	std::string outString = "";
	
	for (int i = 0; i < inTiming.size(); i++) {
		if (inTiming[i] == 1)	//One period of sound is a dot
			outString += '.';
		else if (inTiming[i] == 3)	//Three periods of sound is a dash
			outString += '-';
		else if (inTiming[i] == -3)	//Three periods of silence is a '/'
			outString += '/';
		else if (inTiming[i] == -5)	//Don't know why but required to function properly //FUTURE EDIT: Fix this sh*t (maybe look into why it is 2x+1?)
			outString += '/';
		else if (inTiming[i] == -7)	//Seven periods of silence is a ' '
			outString += ' ';
		else if (inTiming[i] == -13)	//Don't know why but required to function properly //FUTURE EDIT: Fix this sh*t (maybe look into why it is 2x+1?)
			outString += ' ';
	}
	
	return outString;
}

std::string MorseTree::engToMorse(std::string inString) {	//Translate english phrase to morse code
	std::string outString = "", indivChar;
	
	for (int i = 0; i < inString.length(); i++) {	//For each character in inString
		indivChar = engToMorse(inString[i]);
		
		if (indivChar != "error")	//If translated correctly, add translate character to outString
			outString += indivChar;
		
		if (inString[i+1] != ' ' && inString[i] != ' ' && inString[i+1] != '\0')	//Add letter/number delim if required
			outString += "/";
	}
	
	return outString;
}

std::string MorseTree::engToMorse(char inChar) {	//Translate english character to morse code
	short int index;
	std::string outString;
	
	if (isalpha(inChar)) {	//If inChar is alphabetic
		inChar = toupper(inChar);
		index = (int)(inChar) - (int)('A');	//A is 0, B is 1, etc
		outString = orderedMorse[index];	//Find morse code translation
	} else if (isdigit(inChar)) {	//If inChar is a number
		index = (int)(inChar) - (int)('0') + 26;	//0 is 26, 1 is 27, etc
		outString = orderedMorse[index];	//Find morse code translation
	} else if (inChar == ' ') {	//Space is just space :)
		outString = " ";
	} else {	//inChar not alphanumeric or space
		outString = "error";
		for (int i = 0; i < 13; i++) {	//Search for char in listing, if found, translate
			if (inChar == nonAlphaNumChar[i]) {
				outString = nonAlphaNumMorse[i];
				break;
			}
		}
	}
	
	return outString;
}

std::string MorseTree::morseToEngMult(std::string inMorse) {	//Translate multiple morse sequences (i.e. an entire multiletter word or phrase) into an english phrase
	std::string outString;
	inMorse += "/";
	
	char indivChar;
	int sIndex = 0;	//String index
	
	while (sIndex != inMorse.length()) {	//While not at end of input
		for (int i = sIndex; i < inMorse.length(); i++) {	//Search for next delim (' ' or '/')
			if (inMorse[i] == '/' || inMorse[i] == ' ' || i == inMorse.length() - 1) {
				if (i == inMorse.length())	//If at end of string, convert rest to morse
					indivChar = morseToEng(inMorse.substr(sIndex));
				else
					indivChar = morseToEng(inMorse.substr(sIndex, (i-sIndex)));
				
				outString += indivChar;
				
				if (inMorse[i] == ' ')	//If space, add space
					outString += " ";
				
				sIndex = ++i; //Increment index
								
				break;
			}
		}
	}
	
	return outString;
}

char MorseTree::morseToEng(std::string inMorse) {	//Translate single morse sequence (one english character) into english character
	MorseNode *temp;
	temp = root;
	
	for (int i = 0; i < inMorse.length(); i++) {	//Search for char
		if (inMorse[i] == '.')	//Dots go left
			temp = temp->left;
		else if (inMorse[i] == '-')	//Dashes go right
			temp = temp->right;
		else
			return '\0';
	}
	
	return temp->engChar;
}	

void MorseTree::printTree() {	//Print entire tree
	MorseTree::printTree(root);	//Start at root
	return;
}

void MorseTree::printTree(MorseNode * node) {	//Print tree starting at node
	if (node == NULL)
		return;
	
	MorseTree::printTree(node->left);	//Print left child
	
	if (node->engChar != '\0')	//If english char is null character, node is an empty node, so do not print
		std::cout << node->engChar << " is " << node->morse << " in morse code.\n";
	
	MorseTree::printTree(node->right);	//Print right child
}
