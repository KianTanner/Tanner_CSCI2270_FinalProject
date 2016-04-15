#include "MorseTree.cpp"
#include "wav.cpp"

int main(int argc, char* argv[]) {
	char cArray[58] = {'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', 
						'D', 'K', 'G', 'O', 'H', 'V', 'F', '\0', 'L', '\0', 
						'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '\0', '\0', 
						'5', '4', '3', '2', '1', '6', '7', '8', '9', '0',
						'\0', '\?', '\0', '\"', '+', '.', '\0', '@', '\'', 
						'-', '=', '/', '\0', ';', '!', '\0', ',', ':'};
	std::string sArray[58] = {".", "-", "..", ".-", "-.", "--", "...", "..-", ".-.", ".--", 
								"-..", "-.-", "--.", "---", "....", "...-", "..-.", "..--", ".-..", ".-.-", 
								".--.", ".---", "-...", "-..-", "-.-.", "-.--", "--..", "--.-", "---.", "----", 
								".....", "....-", "...--", "..---", ".----", "-....", "--...", "---..", "----.", "-----",
								"..--.", "..--..", ".-..-", ".-..-.", ".-.-.", ".-.-.-", ".--.-", ".--.-.", ".----.", 
								"-....-", "-...-", "-..-.", "-.-.-", "-.-.-.", "-.-.--", "--..-", "--..--", "---..."};
	
	MorseTree mTree;
	
	for (int i = 0; i < 58; i++) {
		mTree.addNode(cArray[i], sArray[i]);
	}
	
	//mTree.printTree();
	std::string a = "The quick brown fox jumps over the yellow dog.";
	std::string b = mTree.engToMorse(a);
	std::string c = mTree.morseToEngMult(b);
	std::cout << a << "\n" << b << "\n" << c << std::endl;
	
	std::vector<short int> d = mTree.createTimings("SOS", false);
	
	WAV mWav;
	
	mWav.composeMessage("completeSOS.wav", d);
	return 0;
}
