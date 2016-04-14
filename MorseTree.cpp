#include "MorseTree.h"
#include <iostream>
#include <cctype>

std::string orderedMorse[36] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", //A - J
					/*K - T*/	"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
					/*U - Z*/	"..-", "...-", ".--", "-..-", "-.--", "--..", 
					/*0 - 9*/	"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
char nonAlphaNumChar[13] = {'\?', '\"', '+', '.', '@', '\'', '-', 
							'=', '/', ';', '!', ',', ':'};
std::string nonAlphaNumMorse[13] = {"..--..", ".-..-.", ".-.-.", ".-.-.-", ".--.-.", ".----.", "-....-", 
									"-...-", "-..-.", "-.-.-.", "-.-.--", "--..--", "---..."};

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
	std::cout << "Added " << inEngChar << " as " << inMorse << " as a child of " << toAdd->parent->engChar << std::endl; //del later
	return;
}

std::string MorseTree::engToMorse(std::string inString) {
	std::string outString = "", indivChar;
	for (int i = 0; i < inString.length(); i++) {
		indivChar = engToMorse(inString[i]);
		if (indivChar != "error")
			outString += indivChar;
		if (engToMorse(inString[i+1]) != "  ")
			outString += "/";
	}
	return outString;
}

std::string MorseTree::engToMorse(char inChar) {
	short int index;
	std::string outString;
	if (isalpha(inChar)) {
		inChar = toupper(inChar);
		index = int (inChar) - int ('A');
		outString = orderedMorse[index];
	} else if (isdigit(inChar)) {
		index = int (inChar) - int ('0') + 26;
		outString = orderedMorse[index];
	} else if (inChar == ' ') {
		outString = "  ";
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

char MorseTree::morseToEng(std::string inMorse) {
	MorseNode *temp;
	temp = root;
	for (int i = 0; i < inMorse.length(); i++) {
		if (inMorse[i] == '.')
			temp = temp->left;
		else if (inMorse[i] == '-')
			temp = temp->right;
		else
			return '!';
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
	
	
	
