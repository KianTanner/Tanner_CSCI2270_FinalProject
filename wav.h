//WAV class header
//Copyright (C) 2016  Kian Tanner

//Licensed under GNU GPL v3. Full disclaimer may be found in main.cpp

#ifndef WAV_H
#define WAV_H

#include <string>
#include <cstdio>
#include <vector>

class WAV {
	public:
		WAV();	//Constructor
		~WAV();	//Destructor
		void writeFile(std::string fName, unsigned long int numSamples, short int * data);	//Write data to WAV file
		std::vector <short int> readFile(std::string fName);	//Read data from WAV file, output to timings
		void composeMessage(std::string fName, std::vector<short int> timings);	//Compose message from timings to data
	protected:
	private:
		void writeLittleEndian(unsigned int word, int numBytes, FILE * wavFile);	//Write little endian
		
		unsigned int sampleRate;	//in Hertz
		unsigned int numChannels;
		unsigned int bytesPerSample;
		unsigned int byteRate;
		unsigned short int dotPeriod;	//Length of one dot time period in samples
		
		float amplitude;	//Volume
		float freq;	//Frequency of sine wave
		float freqRadsPerSample;
};

#endif
