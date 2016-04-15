#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

//Ordered arrays for searching backwards
extern std::string orderedMorse[];
extern char nonAlphaNumChar[];
extern std::string nonAlphaNumMorse[];

//Arrays with data to create tree
extern char cArray[];
extern std::string sArray[];


void displayHelp();
void displayDict();

#endif

