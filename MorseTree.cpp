#include "MorseTree.h"
#include <iostream>

MorseTree::MorseTree() {
	MorseNode *r;
	r = new MorseNode;
	r->engChar = '&';
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
	std::cout << temp->morse << " equals " << inMorse << std::endl;
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
	std::cout << node->engChar << " is " << node->morse << " in morse code.\n";
	MorseTree::printTree(node->right);
}
	
	
	
