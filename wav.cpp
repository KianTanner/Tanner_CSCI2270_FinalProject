#include "wav.h"

#include <iostream>
#include <cstring>
#include <cmath>

const double pi = 3.14159265358979323846264338327950288419716939937510582;

WAV::WAV() {
	sampleRate = 44100;
	numChannels = 1;
	bytesPerSample = 2;
	byteRate = sampleRate * numChannels * bytesPerSample;
	dotPeriod = 5292;
	amplitude = 32000;
	freq = 440;
	freqRadsPerSample = freq*2*pi/sampleRate;
}

WAV::~WAV() {
}

void WAV::writeLittleEndian(unsigned int word, int numBytes, FILE *wavFile) {
	unsigned buf;
	while (numBytes > 0) {
		buf = word & 0xff;
		fwrite(&buf, 1, 1, wavFile);
		numBytes--;
		word >>= 8;
	}
}

void WAV::writeFile(std::string fName, unsigned long int numSamples, short int * data) {
	FILE * wavFile;
	wavFile = fopen(fName.c_str(), "w");
	if (!wavFile) {
		std::cout << "File didn't open" << std::endl;
		return;
	}
	fwrite("RIFF", 1, 4, wavFile);
	writeLittleEndian(36 + bytesPerSample * numSamples * numChannels, 4, wavFile);
	fwrite("WAVE", 1, 4, wavFile);
	
	//Write fmt subchunk
	fwrite("fmt ", 1, 4, wavFile);
	writeLittleEndian(16, 4, wavFile);	//First subchunk size is 16
	writeLittleEndian(1, 2, wavFile);	//PCM is format 1
	writeLittleEndian(numChannels, 2, wavFile);
	writeLittleEndian(sampleRate, 4, wavFile);
	writeLittleEndian(byteRate, 4, wavFile);
	writeLittleEndian(numChannels * bytesPerSample, 2, wavFile);	//Align blocks
	writeLittleEndian(8 * bytesPerSample, 2, wavFile);	//Bits per sample
	
	//Write data subchunk
	fwrite("data", 1, 4, wavFile);
	writeLittleEndian(bytesPerSample * numSamples * numChannels, 4, wavFile);
	for (unsigned long int i; i < numSamples; i++) {
		writeLittleEndian((unsigned int)(data[i]), bytesPerSample, wavFile);
	}
	fclose(wavFile);
	return;
}

void WAV::composeMessage(std::string fName, std::vector<short int> timings) {
	long int numElements = 0;
	for (int i = 0; i < timings.size(); i++) {
		numElements += abs(timings[i]);
	}
	unsigned long int numSamples = numElements * dotPeriod;
	unsigned long int sampleCount = 0;
	float phase = 0;
	short int buffer[numSamples];
	for (int i = 0; i < timings.size(); i++) {
		if (timings[i] > 0) {
			for (unsigned long int j = 0; j < timings[i] * dotPeriod; j++) {
				phase += freqRadsPerSample;
				buffer[sampleCount] = (int)(amplitude * sin(phase));
				sampleCount++;
			}
		} else {
			for (unsigned long int j = 0; j < timings[i] * dotPeriod * -1; j++) {
				phase += freqRadsPerSample;
				buffer[sampleCount] = 0;
				sampleCount++;
			}
		}
	}
	writeFile(fName, numSamples, buffer);
	return;
}
	
	

