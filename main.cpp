#include "MorseTree.h"
#include "wav.h"
#include "global.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

// Maybe add error handling so that if user inputs filename can add extension?
				

int main(int argc, char * argv[]) {
	
	bool tIn, aIn, mIn, menu, m2e, e2m, tOut, aOut, dOut, h, dict;
	tIn = aIn = mIn = menu = m2e = e2m = tOut = aOut = dOut = h = dict = false;
	std::string inFile = "", tOutFile, aOutFile, argum, exten;
	
	//Parse arguments
	for (int i = 1; i < argc; i++) {
		argum = argv[i];
		if (argum == "-h") {	//Display help (overrides others)
			h = true;
		} else if (argum == "-help") {
			h = true;
		} else if (argum == "-ti") {	//Input via text file (conflicts with -m2e (for now), -ai, -mi, -menu)
			tIn = true;
			inFile = argv[i+1];	//Next argument must be filename
			i++;
		} else if (argum == "-ai") {	//Input via audio file (conflicts with -e2m (for now), -ti, -mi, -menu)
			aIn = true;
			inFile = argv[i+1];
			i++;
		} else if (argum == "-mi") {	//Input via argument (conflicts with -ti, -ai, -menu), (if -m2e, must be in the form ---/.../--- .../---/... ---/.../--- ('/' to separate letters, ' ' to separate words))
			mIn = true;
			inFile = argv[i+1];
			i++;
		} else if (argum == "-menu") {	//Input via menu (conflicts with -ti, -ai, -mi, -m2e, -e2m, -to, -ao, -do, -dict) default if no other input method selected or if filenames don't open
			menu = true;
		} else if (argum == "-m2e") {	//Morse to english (conflicts with -ti (for now), -menu, -ao), (default if neither -m2e or -e2m is menu)
			m2e = true;
		} else if (argum == "-e2m") {	//English to morse (conflicts with -ai (for now), -menu)
			e2m = true;
		} else if (argum == "-to") {	//Output to text file (conflicts with -menu)
			tOut = true;
			tOutFile = argv[i+1];	//Next argument must be filename
			i++;
		} else if (argum == "-ao") {	//Output to audio file (.wav) (conflicts with -menu, -m2e (for now))
			aOut = true;
			aOutFile = argv[i+1];
			i++;
		} else if (argum == "-do") {	//Output to display (conflicts with -menu)
			dOut = true;
		} else if (argum == "-dict") {	//Display english to morse dictionary
			dict = true;
		} else {
			std::cout << argum << " is not a valid argument." << std::endl;
			h = true;
		}
	}
	
	//Check for conflicts in arguments
	if (h)
		menu = true;
	if (dict)
		menu = true;
	if (tIn && (aIn || mIn || menu || m2e))
		menu = true;
	if (aIn && (tIn || mIn || menu || e2m))
		menu = true;
	if (mIn && (tIn || aIn || menu))
		menu = true;
	if (!tIn && !aIn && !mIn)
		menu = true;
	if (!menu && !mIn) {
		exten = "";
		for (int i = 4; i >= 0; i--) {
			exten += inFile[inFile.length() - i];
		}
		if (tIn) {
			if (exten != ".txt")
				menu = true;
		}
		if (aIn) {
			if (exten != ".wav")
				menu = true;
		}
		FILE * testFile;
		testFile = fopen(inFile.c_str(), "r");
		if (testFile == NULL)
			menu = true;
		fclose (testFile);
	}
	if (!m2e && !e2m)
		menu = true;
	if (m2e && (e2m || aOut))
		menu = true;
	if (tOut && !menu) {
		exten = "";
		for (int i = 4; i >= 0; i--) {
			exten += tOutFile[tOutFile.length() - i];
		}
		std::string exten_c = exten.c_str();
		std::string tExten = ".txt";
		std::string tExten_c = tExten.c_str();
		if (exten_c.compare(tExten_c))
			menu = true;
	}
	if (aOut && !menu) {
		exten = "";
		for (int i = 4; i >= 0; i--) {
			exten += aOutFile[aOutFile.length() - i];
		}
		std::string exten_c = exten.c_str();
		std::string tExten = ".wav";
		std::string tExten_c = tExten.c_str();
		if (exten_c.compare(tExten_c))
			menu = true;
	}
	if (!menu && !tOut && !aOut)
		dOut = true;
	if (menu)
		tIn = aIn = mIn = m2e = e2m = tOut = aOut = dOut = false;
	
	/*
	std::cout << "Arguments:\n------------------------------------------\n";
	std::cout << "Input:\nText:\tAudio:\tManual:\tMenu:\n" << tIn << "\t" << aIn << "\t" << mIn << "\t" << menu << "\n\n";
	std::cout << "Output:\nText:\tAudio:\tDisplay:\n" << tOut << "\t" << aOut << "\t" << dOut << "\n\n";
	std::cout << "Others:\nM2E:\tE2M:\tHelp:\tDict:\n" << m2e << "\t" << e2m << "\t" << h << "\t" << dict << "\n\n";
	*/
	
	if (h)
		displayHelp();
	
	if (dict)
		displayDict();
	
	int inputInt;
	if (menu) {
		inFile = "";
		std::cout << "=====MORSE TRANSLATOR v1.0=====\n";
		inputInt = 0;
		while (!(inputInt == 1 || inputInt == 2)) {
			std::cout << "Translate from: \n\t1. English to morse code\n\t2. Morse code to english\n";
			std::cin >> inputInt;
			std::cin.ignore(1000, '\n');
			std::cout << std::endl;
		}
		if (inputInt == 1)
			e2m = true;
		else
			m2e = true;
		inputInt = 0;
		while (!(inputInt == 1 || inputInt == 2 || inputInt == 3)) {
			if (e2m) {
				std::cout << "Input from: \n\t1. Text file (.txt only)\n\t2. Enter on keyboard\n";
				std::cin >> inputInt;
				std::cin.ignore(1000, '\n');
				std::cout << std::endl;
				if (inputInt == 3)
					inputInt = 4;
			} else {
				std::cout << "Input from: \n\t1. Text file (.txt only)\nt2. Audio file (.wav only)\n\t3. Enter on keyboard\n";
				std::cin >> inputInt;
				std::cin.ignore(1000, '\n');
				std::cout << std::endl;
			}
		}
		if (e2m) {
			if (inputInt == 1)
				tIn = true;
			else
				mIn = true;
		} else {
			if (inputInt == 1)
				tIn = true;
			else if (inputInt == 2)
				aIn =true;
			else
				mIn = true;
		}
		inputInt = 0;
		if (!mIn) {
			FILE * tFile;
			do {
				std::cout << "Enter the name of the input file (including file extension): ";
				std::getline(std::cin, inFile);
				std::cin.ignore(1000, '\n');
				tFile = fopen(inFile.c_str(), "r");
			} while (tFile == NULL);
			fclose(tFile);
		} else {
			if (m2e) {
				std::cout << "Enter a morse code sequence (\'/\' between letters, \' \' between words): ";
				std::getline(std::cin, inFile);
				std::cin.ignore(1000, '\n');
			} else {
				std::cout << "Enter a message in english: ";
				std::getline(std::cin, inFile);
				std::cin.ignore(1000, '\n');
			}
		}
		while (!(inputInt == 1 || inputInt == 2)) {
			std::cout << "Output as a text file? (may select multiple outputs)\n\t1. Yes\n\t2. No\n";
			std::cin >> inputInt;
			std::cin.ignore(1000, '\n');
			std::cout << std::endl;
		}
		if (inputInt == 1) {
			FILE * tFile;
			tOutFile = "";
			tOut = true;
			do {
				std::cout << "Enter the name of the text file to be output (including file extension): ";
				std::getline(std::cin, tOutFile);
				std::cin.ignore(1000, '\n');
				tFile = fopen(tOutFile.c_str(), "w");
			} while (tFile == NULL);
			fclose(tFile);
		}
		inputInt = 0;
		while (!(inputInt == 1 || inputInt == 2)) {
			std::cout << "Output as an audio file? (.wav only) (may select multiple outputs)\n\t1. Yes\n\t2. No\n";
			std::cin >> inputInt;
			std::cin.ignore(1000, '\n');
			std::cout << std::endl;
		}
		if (inputInt == 1) {
			FILE * tFile;
			aOutFile = "";
			aOut = true;
			do {
				std::cout << "Enter the name of the audio file to be output (including file extension): ";
				std::getline(std::cin, aOutFile);
				std::cin.ignore(1000, '\n');
				tFile = fopen(aOutFile.c_str(), "w");
			} while (tFile == NULL);
			fclose(tFile);
		}
		inputInt = 0;
		while (!(inputInt == 1 || inputInt == 2)) {
			std::cout << "Output onto the display?\n\t1. Yes\n\t2. No\n";
			std::cin >> inputInt;
			std::cin.ignore(1000, '\n');
			std::cout << std::endl;
		}
		if (inputInt == 1) {
			dOut = true;
		}
	}
	
	MorseTree mTree;
	for (int i = 0; i < 58; i++) {
		mTree.addNode(cArray[i], sArray[i]);
	}
	WAV mWav;
	
	std::string morseText, engText;
	if (m2e) {
		if (tIn) {
			//Get morseText
		} else if (aIn) {
			//Get morse audio
		} else if (mIn) {
			morseText = inFile;
		}
		engText = mTree.morseToEngMult(morseText);
		if (tOut) {
			//Write to text file
		}
		if (dOut)
			std::cout << "The message translated into english is: \n" << engText << std::endl;
	} else if (e2m) {
		if (tIn) {
			//Get engText
		} else if (mIn) {
			engText = inFile;
		}
		morseText = mTree.engToMorse(engText);
		if (tOut) {
			//Write shit to text file
		}
		if (aOut) {
			std::vector<short int> timing = mTree.createTimings(morseText);
			mWav.composeMessage(aOutFile, timing);
		}
		if (dOut)
			std::cout << "The message translated into morse code is: \n" << morseText << std::endl;
	}
	
	
	
	return 0;
}
