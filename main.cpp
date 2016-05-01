//Morse translator
//Copyright (C) 2016  Kian Tanner
    
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MorseTree.h"
#include "wav.h"

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

const short int VERSION = 1, MAJOR_REVISION = 6, MINOR_REVISION = 2;

void displayHelp();

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
		std::cout << "Copyright(C) 2016 Kian Tanner - See help for details\n";
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
	char input = 'a';
	std::cout << "======HELP TEXT=====\n";
	std::cout << "Copyright (C) 2016 Kian Tanner\n";
	
	while (input != ('i' || 'c' || 'm' || 'h' || 'l' || 'e')) {	
		//Menu
		std::cout << "For information on input/output options, enter 'i'\n";
		std::cout << "For how to contact the developer for bug reporting/suggestions, enter 'c'\n";
		std::cout << "For how to format morse text, enter 'm'\n";
		std::cout << "For information on entities whose help made this program possible, enter 'h'\n";
		std::cout << "For licensing information, enter 'l'\n";
		std::cout << "To exit this help text, enter 'e'" << std::endl;
		
		std::cin >> input;
		switch (input) {
			case 'i':
				std::cout << "===Input/Output Options===\n";
				std::cout << "English to Morse Code\n" << 
							 "    Input via:     |     Output to:\n" << 
							 "-------------------|-------------------\n" << 
							 "    Text file      |     Text file\n" << 
							 "  Onscreen input   |   Onscreen output\n" << 
							 "                   |  Audio file (.wav)\n";
				std::cout << "Morse Code to English\n" << 
							 "    Input via:     |     Output to:\n" << 
							 "-------------------|-------------------\n" << 
							 "    Text file      |     Text file\n" << 
							 "  Onscreen input   |   Onscreen output\n" << 
							 " Audio file (.wav) |\n";
				std::cout << "==========================" << std::endl;
				break;
			case 'c':
				std::cout << "===Developer Contact Information===\n";
				std::cout << "Please report any issues or bugs on the GitHub page for this program\n" << 
							 "<https://github.com/KianTanner/Tanner_CSCI2270_FinalProject>, or email to " <<
							 "\n<kian.tanner@colorado.edu>\n";
				std::cout << "Please email any other suggestions to <kian.tanner@colorado.edu>\n";
				std::cout << "===================================" << std::endl;
				break;
			case 'm':
				std::cout << "===Morse Code Format===\n";
				std::cout << "This program uses standard morse code with some extended prosigns.\n" << 
							 "To view a full list of available characters, choose option 4 at the main menu.\n"; 
				std::cout << "Morse code is represented in the standard format, with '.' and '-'. ' ' is \n" << 
							 "used to separate words, and '/' is used to separate individual characters.\n" <<
							 "For example, the phrase 'This is a test' is represented as \n" << 
							 "'-/..../../... ../... .- -/./.../-' in morse code.\n";
				std::cout << "=======================" << std::endl;
				break;
			case 'h':
				std::cout << "===Many Thanks To===\n";
				std::cout << "Reddit user AdamDe27, whose thread inspired this program\n" <<
							 "Stanford University, for much-needed information on the WAVE format\n" <<
							 "Wayback Machine, for archiving the Stanford University webpage\n" <<
							 "Cplusplus.com, for its reference pages on the C++ standard library\n" << 
							 "Dillinger.io, for an in-browser, WYSIWYG markdown editor\n";
				std::cout << "====================" << std::endl;
				break;
			case 'l':
				std::cout << "===License Information===\n";
				std::cout << "Copyright (C) 2016 Kian Tanner\n";
				std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details, see GNU General \n" << 
							 "Public License v3 Section 15.\n";
				std::cout << "This is free software, and you are welcome to redistribute it under certain \n" << 
							 "conditions; for details, see GNU General Public License v3, Sections 4 - 7\n";
				std::cout << "You should have received a copy of the GNU General Public License along with \n" << 
							 "this program.  If not, see <http://www.gnu.org/licenses/>.\n";
				std::cout << "=========================" << std::endl;
				break;
			case 'e':
				std::cout << "======END OF HELP TEXT======" << std::endl;
				return;
				break;
			default:
				std::cout << input << " is not a valid input." << std::endl;
				break;
		}
		input = 'a';
	}
	
	return;
}


