#ifndef MORSETREE_H
#define MORSETREE_H

#include <string>
#include <vector>

//Struct for node
struct MorseNode {
	char engChar;	//English character represented by morse (if null character '\0', node is empty)
	std::string morse;	//Morse string composed solely with '.' or '-'
	
	MorseNode *parent;	//Duh
	MorseNode *left;
	MorseNode *right;
	
	MorseNode() {}
	MorseNode(char inEngChar, std::string inMorse) {
		engChar = inEngChar;
		morse = inMorse;
	}
};

//Tree class
class MorseTree {
	public:
		MorseTree();	//Constructor
		~MorseTree();	//Destructor
		void buildTree();	//Build tree
		void addNode(char inEngChar, std::string inMorse);	//Add node
		std::vector<short int> createTimings(std::string input, bool inMorse = true);	//Create timings to give to WAV class
		std::string inverseTimings(std::vector <short int> inTiming);	//Convert timings returned from WAV to standard morse code
		std::string engToMorse(std::string inString);	//Translate english string to morse code
		std::string morseToEngMult(std::string inMorse);	//Translate morse phrase to english
		void printTree();	//Print entire tree
		std::string engToMorse(char inChar);	//Translate english character to morse code
		char morseToEng(std::string inMorse);	//Translate single morse sequence (letter, number, etc) to english character
	protected:
	private:
		MorseNode *root;	//Root of tree
		void printTree(MorseNode * node);	//Print tree given root
};

#endif
