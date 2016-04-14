#include "MorseTree.cpp"

int main(int argc, char* argv[]) {
	char cArray[30] = {'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', //[43] total
						'D', 'K', 'G', 'O', 'H', 'V', 'F', '!', 'L', '!', 
						'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '!', '!'};
	std::string sArray[30] = {".", "-", "..", ".-", "-.", "--", "...", "..-", ".-.", ".--", 
								"-..", "-.-", "--.", "---", "....", "...-", "..-.", "..--", ".-..", ".-.-", 
								".--.", ".---", "-...", "-..-", "-.-.", "-.--", "--..", "--.-", "---.", "----"};
	
	MorseTree mTree;
	
	for (int i = 0; i < 30; i++) {
		mTree.addNode(cArray[i], sArray[i]);
	}
	
	mTree.printTree();
	char a  = mTree.morseToEng("..");
	std::cout << a << std::endl;
	
	return 0;
}
