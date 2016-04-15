#include "MorseTree.h"
#include "global.h"
#include <iostream>
#include <cctype>

MorseTree::MorseTree() {
	MorseNode *r;
	r = new MorseNode;
	r->engChar = '\0';
	r->morse = "";
	r->parent = NULL;
	r->left = NULL;
	r->right = NULL;
	root = r;
}

MorseTree::~MorseTree() {
	//add code
}

void MorseTree::addNode(char inEngChar, std::string inMorse) {
	int level = -1;
	std::string a = ".";
	MorseNode *temp;
	MorseNode *parent;
	MorseNode *toAdd;
	temp = root;
	parent = NULL;
	toAdd = new MorseNode;
	toAdd->engChar = inEngChar;
	toAdd->morse = inMorse;
	toAdd->parent = NULL;
	toAdd->left = NULL;
	toAdd->right = NULL;
	
	while (temp != NULL) {
		level++;
		parent = temp;
		if (toAdd->morse[level] == '.') {
			temp = temp->left;
		} else if (toAdd->morse[level] == '-') {
			temp = temp->right;
		} else {
			std::cout << "inMorse must be composed solely of dots and/or dashes" << std::endl;
			return; //Ya done fucked up, just give up now
		}
	}
	if (parent == NULL) {
		return;
	} else if (toAdd->morse[level] == '.') {
		parent->left = toAdd;
		toAdd->parent = parent;
	} else {
		parent->right = toAdd;
		toAdd->parent = parent;
	}
	return;
}

std::vector<short int> MorseTree::createTimings(std::string input, bool inMorse) {
	std::vector<short int> outVec;
	if (!inMorse)
		input = engToMorse(input);
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '.') {
			outVec.push_back(1);	//One dot period of sound
			if (input[i+1] == '/' || input[i+1] == ' ' || i == input.length()-1) {
			} else {
				outVec.push_back(-1);	//One dot period of silence	
			}
		} else if (input[i] == '-') {
			outVec.push_back(3);	//Three dot periods of sound
			if (input[i+1] == '/' || input[i+1] == ' ' || i == input.length()-1) {
			} else {
				outVec.push_back(-1);	//One dot period of silence	
			}
		} else if (input[i] == '/') {
			outVec.push_back(-3);
		} else if (input[i] == ' ') {
			outVec.push_back(-7);
		}
	}
	return outVec;
}

std::string MorseTree::engToMorse(std::string inString) {
	std::string outString = "", indivChar;
	for (int i = 0; i < inString.length(); i++) {
		indivChar = engToMorse(inString[i]);
		if (indivChar != "error")
			outString += indivChar;
		if (inString[i+1] != ' ' && inString[i] != ' ' && inString[i+1] != '\0')
			outString += "/";
	}
	return outString;
}

std::string MorseTree::engToMorse(char inChar) {
	short int index;
	std::string outString;
	if (isalpha(inChar)) {
		inChar = toupper(inChar);
		index = (int)(inChar) - (int)('A');
		outString = orderedMorse[index];
	} else if (isdigit(inChar)) {
		index = (int)(inChar) - (int)('0') + 26;
		outString = orderedMorse[index];
	} else if (inChar == ' ') {
		outString = " ";
	} else {
		outString = "error";
		for (int i = 0; i < 13; i++) {
			if (inChar == nonAlphaNumChar[i])
				index = i;
		}
		outString = nonAlphaNumMorse[index];
	}
	return outString;
}

std::string MorseTree::morseToEngMult(std::string inMorse) {
	std::string outString;
	inMorse += "/";
	char a;
	int sIndex = 0;
	while (sIndex != inMorse.length()) {
		for (int i = sIndex; i < inMorse.length(); i++) {
			if (inMorse[i] == '/' || inMorse[i] == ' ' || i == inMorse.length() - 1) {
				if (i == inMorse.length())
					a = morseToEng(inMorse.substr(sIndex));
				else
					a = morseToEng(inMorse.substr(sIndex, (i-sIndex)));
				outString += a;
				if (int (inMorse[i]) == 32)
					outString += " ";
				sIndex = ++i;				
				break;
			}
		}
	}
	return outString;
}

char MorseTree::morseToEng(std::string inMorse) {
	MorseNode *temp;
	temp = root;
	for (int i = 0; i < inMorse.length(); i++) {
		if (inMorse[i] == '.')
			temp = temp->left;
		else if (inMorse[i] == '-')
			temp = temp->right;
		else
			return '\0'; //was '&'
	}
	return temp->engChar;
}	

void MorseTree::printTree() {
	MorseTree::printTree(root);
	return;
}

void MorseTree::printTree(MorseNode *node) {
	if (node == NULL)
		return;
	MorseTree::printTree(node->left);
	if (node->engChar != '\0')
		std::cout << node->engChar << " is " << node->morse << " in morse code.\n";
	MorseTree::printTree(node->right);
}
