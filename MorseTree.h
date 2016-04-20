#ifndef MORSETREE_H
#define MORSETREE_H

#include <string>
#include <vector>

struct MorseNode {
	char engChar;
	std::string morse;
	
	MorseNode *parent;
	MorseNode *left;
	MorseNode *right;
	
	MorseNode() {}
	MorseNode(char inEngChar, std::string inMorse) {
		engChar = inEngChar;
		morse = inMorse;
	}
};

class MorseTree {
	public:
		MorseTree();
		~MorseTree();
		void addNode(char inEngChar, std::string inMorse);
		std::vector<short int> createTimings(std::string input, bool inMorse = true);
		std::string inverseTimings(std::vector <short int> inTiming);
		std::string engToMorse(std::string inString);
		std::string morseToEngMult(std::string inMorse);
		void printTree();
	
	protected:
	private:
		MorseNode *root;
		std::string engToMorse(char inChar);
		char morseToEng(std::string inMorse);
		void printTree(MorseNode *node);
};

#endif
