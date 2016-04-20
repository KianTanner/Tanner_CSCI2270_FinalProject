#ifndef WAV_H
#define WAV_H

#include <string>
#include <cstdio>
#include <vector>

class WAV {
	public:
		WAV();
		~WAV();
		void writeFile(std::string fName, unsigned long int numSamples, short int * data);
		std::vector <short int> readFile(std::string fName);
		void composeMessage(std::string fName, std::vector<short int> timings);
	protected:
	private:
		void writeLittleEndian(unsigned int word, int numBytes, FILE *wavFile);
		unsigned int sampleRate;
		unsigned int numChannels;
		unsigned int bytesPerSample;
		unsigned int byteRate;
		unsigned short int dotPeriod;
		float amplitude;
		float freq;
		float freqRadsPerSample;
		int bytesWriten;
};

#endif
