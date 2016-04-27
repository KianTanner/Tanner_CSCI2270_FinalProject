#include "global.h"

#include <iostream>

//Formerly in MorseTree.cpp
std::string orderedMorse[36] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", //A - J
					/*K - T*/	"-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
					/*U - Z*/	"..-", "...-", ".--", "-..-", "-.--", "--..", 
					/*0 - 9*/	"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
char nonAlphaNumChar[13] = {'\?', '\"', '+', '.', '@', '\'', '-', 
							'=', '/', ';', '!', ',', ':'};
std::string nonAlphaNumMorse[13] = {"..--..", ".-..-.", ".-.-.", ".-.-.-", ".--.-.", ".----.", "-....-", 
									"-...-", "-..-.", "-.-.-.", "-.-.--", "--..--", "---..."};

//Formerly in main.cpp
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

void displayHelp() {
	std::cout << "======HELP TEXT=====\n";
	std::cout << "======END OF HELP TEXT======" << std::endl;
	return;
}

void displayDict() {
	std::cout << "======DICTIONARY======\nInternational Standard:";
	for (int i = 0; i < 26; i++) {
		if (i%6 == 0)
			std::cout << "\n";
		std::cout << (char)((int)('A') + i) << " : " << orderedMorse[i];
		for (int j = orderedMorse[i].length(); j < 7; j++) {
			std::cout << " ";
		}
		std::cout << "\t";
	}
	for (int i = 26; i < 36; i++) {
		if (i%6 == 0)
			std::cout << "\n";
		std::cout << i-26 << " : " << orderedMorse[i];
		for (int j = orderedMorse[i].length(); j < 7; j++) {
			std::cout << " ";
		}
		std::cout << "\t";
	}
	std::cout << "\n\nCommon, Non-Standard Prosigns:";
	for (int i = 0; i < 13; i++) {
		if ((i+36)%6 == 0)
			std::cout << "\n";
		std::cout << nonAlphaNumChar[i] << " : " << nonAlphaNumMorse[i];
		for (int j = nonAlphaNumMorse[i].length(); j < 7; j++) {
			std::cout << " ";
		}
		std::cout << "\t";		
	}
	std::cout << "\n======END OF DICTIONARY======" << std::endl;
	return;
}
