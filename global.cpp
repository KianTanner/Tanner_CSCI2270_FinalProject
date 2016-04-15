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
	char a;
	std::cout << "=====HELP TEXT=====\n";
	std::cout << "Valid arguments are:\n";
	std::cout << "-h : display this help document\n" <<
				"\t\tThis argument overrides all others\n";
	std::cout << "-ti : input via text file\n" <<
				"\t\targument immediately after must be \"filename.txt\"\n" <<
				"\t\tThis argument conflicts with -ai, -mi, -menu, and -m2e (for now)\n";
	std::cout << "-ai : input via audio file (.wav only)\n" <<
				"\t\targument immediately after must be \"filename.wav\"\n" <<
				"\t\tThis argument conflicts with -ti, -mi, -menu, and -e2m (for now)\n";
	std::cout << "-mi : input manually via argument\n" <<
				"\t\targument immediately after must be input text\n" <<
				"\t\tMorse code must be entered in the format: .../---/... .../---/... (characters separated by / and words separated by a single space)\n" <<
				"\t\tEnglish may be entered normally\n" <<
				"\t\tThis argument conflicts with -ti, -ai, and -menu\n";
	std::cout << "-menu : input via menu\n" <<
				"\t\tIf neither -ti, -ai,-mi, nor -menu are passed, -menu will be selected\n" <<
				"\t\tIf the filename after either -ti, -ai, or -mi is invalid, -menu will be selected\n" <<
				"\t\tIf more than just one of -ti, -ai, or -mi are given as arguments, -menu will be selected\n" <<
				"\t\tThis argument overrides -ti, -ai, -mi, -m2e, -e2m, -to, -ao, and -do\n";
	std::cout << "-m2e : translate from morse code to english\n" <<
				"\t\tIf neither -m2e nor -e2m are given as arguments, -menu will be selected\n" <<
				"\t\tIf both -m2e and -e2m are given as arguments, -menu will be selected\n" <<
				"\t\tThis argument conflicts with -ti, -menu, and -ao\n";
	std::cout << "-e2m : translate from english to morse code\n" <<
				"\t\tThis argument conflicts with -ai and -menu\n";
	std::cout << "-to : outputs to a text file\n" << 
				"\t\targument immediately after must be \"filename.txt\"\n" <<
				"\t\tThis argument conflicts with -menu\n";
	std::cout << "-ao : outputs to an audio file (.wav only)\n" << 
				"\t\targument immediately after must be \"filename.wav\"\n" <<
				"\t\tThis argument conflicts with -m2e and -menu\n";
	std::cout << "-do : displays the output onscreen\n" <<
				"\t\tIf neither -to, -ao, nor -do are given as arguments, -do will be selected\n" <<
				"\t\tThis argument conflicts with -menu\n";
	std::cout << "-dict : displays the english to morse code dictionary used by this program\n";
	std::cout << "=====END OF HELP TEXT=====" << std::endl;
	std::cout << "\n\nPress any key to go to menu: ";
	std::cin >> a;
	std::cin.ignore();
	return;
}

void displayDict() {
	std::cout << "=====DICTIONARY=====\nInternational Standard:";
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
	std::cout << "\n=====END OF DICTIONARY=====\n";
	return;
}
