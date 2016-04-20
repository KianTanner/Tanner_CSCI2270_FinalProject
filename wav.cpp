#include "wav.h"
#include "global.h"
#include <iostream>
#include <cstring>
#include <cmath>

/*Thanks to Stanford University for the webpage http://ccrma.stanford.edu/courses/422/projects/WaveFormat/ 
 * which had very useful information on how .wav files are formated.
 * In addition the Wayback Machine was neccessary to access the above page
 */

const double PI = 3.14159265358979323846264338327950288419716939937510582;

WAV::WAV() {
	sampleRate = 44100;
	numChannels = 1;
	bytesPerSample = 2;
	byteRate = sampleRate * numChannels * bytesPerSample;
	dotPeriod = 5292;
	dotPeriod = 3;
	amplitude = 32000;
	freq = 440;
	freqRadsPerSample = freq*2*PI/sampleRate;
	bytesWriten = 0;
}

WAV::~WAV() {
}

void WAV::writeLittleEndian(unsigned int word, int numBytes, FILE *wavFile) {
	unsigned int buf;
	while (numBytes > 0) {
		buf = word & 0xff;
		fwrite(&buf, 1, 1, wavFile);
		bytesWriten++;
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
	fwrite("RIFF", 1, 4, wavFile); //4 bytes
	bytesWriten += 4;
	writeLittleEndian(36 + bytesPerSample * numSamples * numChannels, 4, wavFile); //
	fwrite("WAVE", 1, 4, wavFile);
	bytesWriten += 4;
	
	//Write fmt subchunk
	fwrite("fmt ", 1, 4, wavFile);
	bytesWriten += 4;
	writeLittleEndian(16, 4, wavFile);	//First subchunk size is 16
	writeLittleEndian(1, 2, wavFile);	//PCM is format 1
	writeLittleEndian(numChannels, 2, wavFile);
	writeLittleEndian(sampleRate, 4, wavFile);
	writeLittleEndian(byteRate, 4, wavFile);
	writeLittleEndian(numChannels * bytesPerSample, 2, wavFile);	//Align blocks
	writeLittleEndian(8 * bytesPerSample, 2, wavFile);	//Bits per sample
	
	//Write data subchunk
	fwrite("data", 1, 4, wavFile);
	bytesWriten += 4;
	writeLittleEndian(bytesPerSample * numSamples * numChannels, 4, wavFile);
	//std::cout << bytesWriten << std::endl;
	for (unsigned long int i = 0; i < numSamples; i++) {
		writeLittleEndian((unsigned int)(data[i]), bytesPerSample, wavFile);
	}
	//std::cout << "Num samples: " << numSamples << std::endl;
	fclose(wavFile);
	return;
}

std::vector <short int> WAV::readFile(std::string fName) {
	FILE * wavFile;
	wavFile = fopen(fName.c_str(), "r");
	if (!wavFile) {
		std::cout << "File didn't open" << std::endl;
	}
	fseek(wavFile, 0, SEEK_END);
	unsigned long int numSamples = ftell(wavFile) - 44;
	fseek(wavFile, 44, SEEK_SET);
	unsigned long int numElements = numSamples / dotPeriod;
	//std::cout << numSamples << "  " << numElements << std::endl;
	float phase = 0;
	short int * inBuffer;
	short int * outBuffer;
	inBuffer = new short int [numSamples];
	outBuffer = new short int [numSamples];
	
	unsigned long int numRead = fread(inBuffer, 1, numSamples, wavFile);
	for (unsigned long int i = 0; i < numSamples; i++) {
		phase += freqRadsPerSample;
		outBuffer[i] = round((inBuffer[i]/sin(phase)) / amplitude);
	}
	delete [] inBuffer;
	std::vector <short int> times;
	std::vector <short int> outTimes;
	std::vector <short int> trueOutTimes;
	for (unsigned long int i = 0; i < (numSamples/2)/dotPeriod; i++) {
		times.push_back(outBuffer[dotPeriod*i]);
	}
	delete [] outBuffer;
	
	int sum = 0;
	for (unsigned long int i = 0; i < times.size(); i++) {
		if (times[i] == 1) {
			sum++;
		}
		if (times[i] == 0) {
			outTimes.push_back(sum);
			sum = 0;
			outTimes.push_back(0);
		} else if (i == times.size() - 1) {
			outTimes.push_back(sum);
		}
	}
	
	sum = 0;
	for (unsigned long int i = 0; i < outTimes.size(); i++) {
		if (outTimes[i] == 0) {
			sum--;
		}
		if (outTimes[i] != 0) {
			if (sum < 0) {
				trueOutTimes.push_back(sum);
			}
			sum = 0;
			trueOutTimes.push_back(outTimes[i]);
		} else if (i == outTimes.size() - 1) {
			trueOutTimes.push_back(sum);
		}
	}
	
	fclose(wavFile);
	return trueOutTimes;
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
