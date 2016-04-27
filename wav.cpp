//WAV class implementation
//Copyright (C) 2016  Kian Tanner

//Licensed under GNU GPL v3. Full disclaimer may be found in main.cpp

#include "wav.h"

#include <iostream>
#include <cstring>
#include <cmath>

const double PI = 3.14159265358979323846264338327950288419716939937510582; //Duh

WAV::WAV() {	//Constructor
	sampleRate = 44100;
	numChannels = 1;
	bytesPerSample = 2;
	byteRate = sampleRate * numChannels * bytesPerSample;
	dotPeriod = 5292;
	amplitude = 32000;
	freq = 440;
	freqRadsPerSample = freq*2*PI/sampleRate;
}

WAV::~WAV() {	//Destructor
}

void WAV::writeLittleEndian(unsigned int word, int numBytes, FILE * wavFile) {	//Write little endian
	unsigned int buf;	//Buffer of data to write
	
	while (numBytes > 0) {	//While have bytes to write
		buf = word & 0xff;	//& is bitwise and - goes bit by bit. 0xff = 0b11111111, so if word[i] == 0, buf[i] = 0; if word[i] == 1, buf[i] = 1. Only does first byte of word
		fwrite(&buf, 1, 1, wavFile);	//Write buf, 1 byte, 1 element, to wavFile
		numBytes--;
		//word >>= 8;	//FUTURE EDIT: Delete
		word = word >> 8;	//Word = word shifted 8 bits right (esentially discard first 8 bits of word)
	}
	
	return;
}

void WAV::writeFile(std::string fName, unsigned long int numSamples, short int * data) {	//Write data to WAV file
	FILE * wavFile;
	wavFile = fopen(fName.c_str(), "w");	//Open file in write mode
	if (!wavFile) {		//Check if file opened successfully
		std::cerr << "File didn't open" << std::endl;
		return;
	}
	
	//Write RIFF header
	fwrite("RIFF", 1, 4, wavFile);	//ChunkID
	writeLittleEndian(36 + bytesPerSample * numSamples * numChannels, 4, wavFile);	//ChunkSize	(size of file in bytes - ChunkID and ChunkSize ; ChunkID and ChunkSize = 8 bytes)
	fwrite("WAVE", 1, 4, wavFile);	//Format (WAVE format has two subchunks, fmt and data
	
	//Write fmt subchunk
	fwrite("fmt ", 1, 4, wavFile);	//Subchunk1ID
	writeLittleEndian(16, 4, wavFile);	//Subchunk1Size (16 for PCM)
	writeLittleEndian(1, 2, wavFile);	//AudioFormat (PCM is 1)
	writeLittleEndian(numChannels, 2, wavFile);	//NumChannels
	writeLittleEndian(sampleRate, 4, wavFile);	//SampleRate
	writeLittleEndian(byteRate, 4, wavFile);	//ByteRate
	writeLittleEndian(numChannels * bytesPerSample, 2, wavFile);	//BlockAlign (Num of bytes for one sample including all channels)
	writeLittleEndian(8 * bytesPerSample, 2, wavFile);	//BitsPerSample
	
	//Write data subchunk
	fwrite("data", 1, 4, wavFile);	//Subchunk2ID
	writeLittleEndian(bytesPerSample * numSamples * numChannels, 4, wavFile);	//Subchunk2Size
	for (unsigned long int i = 0; i < numSamples; i++) {	//Write data
		writeLittleEndian((unsigned int)(data[i]), bytesPerSample, wavFile);
	}
	
	fclose(wavFile);	//Close file
	
	return;
}

std::vector <short int> WAV::readFile(std::string fName) {	//Read data from WAV file, output to timings
	FILE * wavFile;
	wavFile = fopen(fName.c_str(), "r");	//Open file in read mode
	if (!wavFile) {	//Check if file opened successfully
		std::cerr << "File didn't open" << std::endl;
	}
	
	fseek(wavFile, 0, SEEK_END);	//Move position indicator to end of file
	unsigned long int numSamples = ftell(wavFile) - 44;	//numSamples = number of bytes in file - 44
	fseek(wavFile, 44, SEEK_SET);	//Move position indicator to 44 bytes from front
	unsigned long int numElements = numSamples / dotPeriod;
	float phase = 0;
	short int * inBuffer;
	short int * outBuffer;
	inBuffer = new short int [numSamples];
	
	std::vector <short int> times;
	std::vector <short int> outTimes;
	
	fread(inBuffer, 1, numSamples, wavFile);	//Read numSamples number of bytes from current position from wavFile into inBuffer
	
	for (unsigned long int i = 0; i < numSamples; i++) {	//For each byte read
		phase += freqRadsPerSample;
		inBuffer[i] = round((inBuffer[i]/sin(phase)) / amplitude);	//Convert to 0 if silence, 1 if sound
	}
	
	for (unsigned long int i = 0; i < (numSamples/2)/dotPeriod; i++) {	//Because 2 bytes per sample
		times.push_back(inBuffer[dotPeriod*i]);	//Push back 0 or 1 for each dot time period
	}
	
	delete [] inBuffer;
	
	int sum = 0;
	for (unsigned long int i = 0; i < times.size(); i++) {	//Sum up periods of sound into (1 or 3)
		if (times[i] == 1) {	//For each dot time period of sound add 1 to sum
			sum++;
		}
		if (times[i] == 0) {	//When encounter silence
			outTimes.push_back(sum);	//Push back sum of sound
			sum = 0;
			outTimes.push_back(0);	//Push back silence
		} else if (i == times.size() - 1) {	//If at end of times, push back sound
			outTimes.push_back(sum);
		}
	}
	
	times.clear();	//Empty times
	times.resize(0);	//Ensure that size is 0
	
	sum = 0;
	for (unsigned long int i = 0; i < outTimes.size(); i++) {	//Sum up silences into (-1, -3, or -7)
		if (outTimes[i] == 0) {	//For each dot time period of silence, subtract 1 from sum
			sum--;
		}
		if (outTimes[i] != 0) {	//When encounter sound
			if (sum < 0) {	//If past was silent
				times.push_back(sum);	//Push back number of dot time periods of silence
			}
			sum = 0;
			times.push_back(outTimes[i]);	//Push back sound
		} else if (i == outTimes.size() - 1) {	//If at end of outTimes, push back silence
			times.push_back(sum);
		}
	}
	
	fclose(wavFile);	//Close file
	
	return times;
}	

void WAV::composeMessage(std::string fName, std::vector<short int> timings) {	//Compose message from timings to data
	long int numElements = 0;	//Sum of abs value of each element in timings (total length of audio in dot time periods
	
	for (int i = 0; i < timings.size(); i++) {	//Sum up numElements
		numElements += abs(timings[i]);
	}
	
	unsigned long int numSamples = numElements * dotPeriod;
	unsigned long int sampleCount = 0;
	float phase = 0;
	short int buffer[numSamples];	//Data to write
	
	for (int i = 0; i < timings.size(); i++) {
		if (timings[i] > 0) {	//If sound
			for (unsigned long int j = 0; j < timings[i] * dotPeriod; j++) {
				phase += freqRadsPerSample;	//Update phase
				buffer[sampleCount] = (int)(amplitude * sin(phase));	//Calculate sine wave
				sampleCount++;
			}
		} else {	//If silent
			for (unsigned long int j = 0; j < timings[i] * dotPeriod * -1; j++) {
				phase += freqRadsPerSample;	//Update phase
				buffer[sampleCount] = 0;	//Silence
				sampleCount++;
			}
		}
	}
	
	writeFile(fName, numSamples, buffer);	//Write data
	
	return;
}
