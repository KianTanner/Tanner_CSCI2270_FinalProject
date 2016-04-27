# Tanner_CSCI2270_FinalProject

## Table of Contents
1. [Project Summary](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#project-summary)
2. [Input/Output Options](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#inputoutput-options)
    * [English to Morse Code](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#english-to-morse-code)
    * [Morse Code to English](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#morse-code-to-english)
3. [How to Run](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#how-to-run)
    * [Dependencies](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#dependencies)
    * [System Requirements](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#system-requirements)
    * [Running](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#running)
    * [Examples](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#examples)
        * [Ex. 1 English to Morse Code](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#ex-1-english-to-morse-code)
        * [Ex. 2 Morse Code to English](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#ex-2-morse-code-to-english)
4. [Development](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#development)
    * [Group Members](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#group-members)
    * [Contributors](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#contributors)
    * [Open Issues/Bugs](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#open-issuesbugs)
    * [Future Enhancements](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#future-enhancements)
5. [Morse Code Standard](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#morse-code-standard)
6. [Many Thanks To](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#many-thanks-to)
7. [License](https://github.com/KianTanner/Tanner_CSCI2270_FinalProject/blob/master/README.md#license)

## Project Summary
This program is a morse code translator. It can translate an english string into morse code and vice-versa. It can get input from and output to several different formats. The user merely needs to follow onscreen instructions to use this program.
A binary search tree is used to translate morse code into an english character, with the idea coming from [this image](http://apfelmus.nfshost.com/articles/fun-with-morse-code/morse-tree.png).
A class is used to handle the .wav files.

## Input/Output options
##### English to Morse Code
Input via: | Output to:
---------- | ----------
Text file | Text file
Onscreen input | Onscreen display
 | Audio file (.wav)

##### Morse Code to English
Input via: | Output to:
---------- | ----------
Text file | Text file
Onscreen input | Onscreen display
Audio file (.wav) | 

## How to Run
##### Dependencies
Included header files and C++ standard library

##### System Requirements
Compiled on linux with g++, should work on any system. __Compiled using C++ 11__
```sh
g++ main.cpp MorseTree.cpp wav.cpp -std=c++11
```

##### Running
Using this program is fairly easy, one merely needs to:

1. Compile as above
2. Run ouput
3. Follow onscreen menus

##### Examples

###### Ex 1. English to Morse Code
```sh
=====MORSE TRANSLATOR v1.4.1======
Translate from:
    1. English to morse code
    2. Morse code to english
    3. Display help
    4. Display english to morse code dictionary
    5. Quit
1
Input from:
    1. Text file
    2. Keyboard
    3. Quit
2
Output to text file? (may select multiple output types)
    1. Yes
    2. No
    3. Quit
2
Output to screen? (may select multiple output types)
    1. Yes
    2. No
    3. Quit
1
Output to audio file? (may select multiple output types)
    1. Yes
    2. No
    3. Quit
1
Enter the english string you wish to translate into morse code:
SOS
Enter the name of the audio file to be output (including .wav file extension):
SOS.wav
SOS translated into morse code is:
.../---/...
```

###### Ex. 2 Morse Code to English
```sh
=====MORSE TRANSLATOR v1.4.1======
Translate from:
    1. English to morse code
    2. Morse code to english
    3. Display help
    4. Display english to morse code dictionary
    5. Quit
2
Input from:
    1. Text file (must be in correct format)
    2. Keyboard (must be in correct format)
    3. Audio file (must be .wav with correct timing)
    4. Quit
3
Output to text file? (may select multiple output types)
    1. Yes
    2. No
    3. Quit
2
Output to screen? (may select multiple output types)
    1. Yes
    2. No
    3. Quit
1
Enter the name of the input file (including file extension):
SOS.wav
.../---/... translated into english is:
SOS
```

## Development
##### Group Members
- Kian Tanner

##### Contributors
- N/A

##### Open Issues/Bugs
* User has to press enter twice after typing input file name or input text (only occurs when output to a file is selected)
* Please report any issues or bugs on the GitHub page, or email to kian.tanner@colorado.edu

##### Future Enhancements 
* [ ] Check input text file to see if any characters don't have morse code equivalents and remove them
* [ ] Allow user to not type file extension when entering input or output file names
* [ ] Allow user to speed up audio output to make files that could be transmitted faster
* [ ] Use an external library (or make your own if you're that good) to read an audio file with a person speaking and translate that to morse code
* [ ] Use an external text-to-speech library to output english as an audio file
* Please email any other suggestions to kian.tanner@colorado.edu

## Morse Code Standard
This program uses standard morse code with some extended prosigns. A full list of available characters that may be used can be viewed by running the program and selecting
```sh
4. Display english to morse code dictionary
```
in the main menu.
Morse code is represented in the standard format, with '.' and '-'. ' ' is used to separate words, and '/' is used to separate individual characters. For example,
>This is a test

is represented as
>-/..../../... ../... .- -/./.../-

in morse code.

## Many Thanks To
- Reddit user [AdamDe27](https://www.reddit.com/r/LearnUselessTalents/comments/2cuwur/morse_code_translator_tree_when_you_hear_a_move/) for the idea for this project
- [Stanford University](https://web.archive.org/web/20090827003349/http://ccrma.stanford.edu/courses/422/projects/WaveFormat), for much-needed information on the WAVE format
- [Wayback Machine](https://archive.org/web/), which was required to access above webpage
- [Cplusplus.com](cplusplus.com), for its reference pages on the C++ standard library
- [Dillinger](dillinger.io), for an in-browser, WYSIWYG markdown editor

## License
[GNU General Public License v3](http://www.gnu.org/licenses/gpl-3.0.html)
