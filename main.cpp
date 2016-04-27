#include "MorseTree.h"
#include "wav.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

const short int VERSION = 1, MAJOR_REVISION = 4, MINOR_REVISION = 2;

void displayHelp();

//Delete tag is //DELETE ME
//FUTURE EDIT: Allow user to not enter file extension

int main(int argc, char * argv[]) {
	short int inputLang = 0; //1:e2m, 2:m2e, 3:display help, 4:display dictionary
	short int inputType = 0; //1:text file, 2:keyboard, 3:audio file
	short int outputType[3] = {-1, -1, -1}; //text, onscreen, audio file
	std::string inFileName, textOutFileName, audioOutFileName;
	
	MorseTree mTree;
	mTree.buildTree();
	
	//Menu
	while (inputLang != 1 && inputLang != 2) {
		std::cout << "======MORSE TRANSLATOR v" << VERSION << "." << MAJOR_REVISION << "." << MINOR_REVISION << "======\n";
		std::cout << "Translate from:\n\t1. English to morse code\n\t2. Morse code to english\n\t3. Display help\n\t4. Display english to morse code dictionary\n\t5. Quit\n";
		std::cin >> inputLang;
		if (inputLang == 3) {
			displayHelp();
			inputLang = 0;
		} else if (inputLang == 4) {
			mTree.displayDictionary();
			inputLang = 0;
		} else if (inputLang == 5) {
			return 0;
		}
	}
	if (inputLang == 1) { //English to morse code
		while (inputType != 1 && inputType != 2) {
			std::cout << "Input from:\n\t1. Text file\n\t2. Keyboard\n\t3. Quit\n";
			std::cin >> inputType;
			if (inputType == 3)
				return 0;
		}
		while (outputType[0] != 1 && outputType[0] != 2) {
			std::cout << "Output to text file? (may select multiple output types)\n\t1. Yes\n\t2. No\n\t3. Quit\n";
			std::cin >> outputType[0];
			if (outputType[0] == 3)
				 return 0;
		}
		while (outputType[1] != 1 && outputType[1] != 2) {
			std::cout << "Output to screen? (may select multiple output types)\n\t1. Yes\n\t2. No\n\t3. Quit\n";
			std::cin >> outputType[1];
			if (outputType[1] == 3)
				 return 0;
		}
		while (outputType[2] != 1 && outputType[2] != 2) {
			std::cout << "Output to audio file? (may select multiple output types)\n\t1. Yes\n\t2. No\n\t3. Quit\n";
			std::cin >> outputType[2];
			if (outputType[2] == 3)
				 return 0;
		}
		for (int i = 0; i < 3; i++) { //Transform from 1 and 2 to 0 and 1
			outputType[i] -= 2;
			outputType[i] *= -1;
		}
	} else { //Morse code to english
		while (inputType != 1 && inputType != 2 && inputType != 3) {
			std::cout << "Input from:\n\t1. Text file (must be in correct format)\n\t2. Keyboard (must be in correct format)\n\t3. Audio file (must be .wav with correct timing)\n\t4. Quit\n";
			std::cin >> inputType;
			if (inputType == 4)
				return 0;
		}
		while (outputType[0] != 1 && outputType[0] != 2) {
			std::cout << "Output to text file? (may select multiple output types)\n\t1. Yes\n\t2. No\n\t3. Quit\n";
			std::cin >> outputType[0];
			if (outputType[0] == 3)
				 return 0;
		}
		while (outputType[1] != 1 && outputType[1] != 2) {
			std::cout << "Output to screen? (may select multiple output types)\n\t1. Yes\n\t2. No\n\t3. Quit\n";
			std::cin >> outputType[1];
			if (outputType[1] == 3)
				 return 0;
		}
		outputType[2] = 0;
		for (int i = 0; i < 2; i++) { //Transform from 1 and 2 to 0 and 1
			outputType[i] -= 2;
			outputType[i] *= -1;
		}
	}
	
	if (inputType == 1 || inputType == 3) { //Input via file
		FILE * testFile;
		do {
			std::cin.ignore(1000, '\n');
			std::cout << "Enter the name of the input file (including file extension):" << std::endl;
			std::getline(std::cin, inFileName);
			testFile = fopen(inFileName.c_str(), "r");
		} while (testFile == NULL);
		fclose(testFile);
	} else if (inputLang == 1) { //Onscreen input in english
		std::cin.ignore(1000, '\n');
		std::cout << "Enter the english string you wish to translate into morse code:" << std::endl;	//FUTURE EDIT: need to press enter twice if outputing to a file
		std::getline(std::cin, inFileName);
	} else { //Onscreen input in morse code
		std::cin.ignore(1000, '\n');
		std::cout << "Enter the morse code string you wish to translate into english (must use '/' to separate characters and ' ' to separate words):" << std::endl;
		std::getline(std::cin, inFileName);
	}
	if (outputType[0] == 1) {
		FILE * testFile;
		do {
			std::cin.ignore(1000, '\n');
			std::cout << "Enter the name of the text file to be output (including .txt file extension):" << std::endl;
			std::getline(std::cin, textOutFileName);
			testFile = fopen(textOutFileName.c_str(), "w");
		} while (testFile == NULL);
		fclose(testFile);
	}
	if (outputType[2] == 1) {
		FILE * testFile;
		do {
			std::cin.ignore(1000, '\n');
			std::cout << "Enter the name of the audio file to be output (including .wav file extension):" << std::endl;
			std::getline(std::cin, audioOutFileName);
			testFile = fopen(audioOutFileName.c_str(), "w");
		} while (testFile == NULL);
		fclose(testFile);
	}
	
	WAV mWav;

	std::string engText = "", morseText = "";
	if (inputLang == 1) { //English to morse code
		if (inputType == 1) { //Input via text file
			//FUTURE EDIT: Check to see if invalid chars
			std::ifstream myFile;
			std::string line;
			myFile.open(inFileName.c_str());
			if (myFile.is_open()) {
				while (getline(myFile, line)) {
					line += " ";
					engText += line;
				}
				myFile.close();
			}
		} else { //Input via keyboard
			engText = inFileName;
		}
		morseText = mTree.engToMorse(engText);
		if (outputType[0] == 1) { //Output to text file
			std::ofstream myFile;
			myFile.open(textOutFileName.c_str(), std::ios::trunc);
			if (myFile.is_open()) {
				myFile << morseText;
				myFile.close();
			}
		}
		if (outputType[1] == 1) //Output to screen
			std::cout << engText << " translated into morse code is:\n" << morseText << std::endl;
		if (outputType[2] == 1) { //Output to audio file
			std::vector<short int> timing = mTree.createTimings(morseText);
			mWav.composeMessage(audioOutFileName, timing);
		}
	} else { //Morse code to english
		if (inputType == 1) { //Input via text file
			std::ifstream myFile;
			std::string line;
			myFile.open(inFileName.c_str());
			if (myFile.is_open()) {
				while (getline(myFile, line)) {
					line += " ";
					morseText += line;
				}
				myFile.close();
			}
		} else if (inputType == 2) { //Input via keyboard
			morseText = inFileName;
		} else { //Input via audio file
			std::vector<short int> retTiming = mWav.readFile(inFileName);
			morseText = mTree.inverseTimings(retTiming);
		}
		engText = mTree.morseToEngMult(morseText);
		if (outputType[0] == 1) { //Output to text file
			std::ofstream myFile;
			myFile.open(textOutFileName.c_str(), std::ios::trunc);
			if (myFile.is_open()) {
				myFile << engText;
				myFile.close();
			}
		}
		if (outputType[1] == 1) //Output to screen
			std::cout << morseText << " translated into english is:\n" << engText << std::endl;
	}

	return 0;
}

void displayHelp() {
	std::cout << "======HELP TEXT=====\n";
	std::cout << "======END OF HELP TEXT======" << std::endl;
	return;
}


