# Tanner_CSCI2270_FinalProject

## Project Summary
This program is a morse code translator. It can translate an english string into morse code and vice-versa. It can get input from and output to several different formats. The user merely needs to follow onscreen instructions to use this program.
A binary search tree is used to translate morse code into an english character, with the idea coming from [this image](http://apfelmus.nfshost.com/articles/fun-with-morse-code/morse-tree.png).
A class is used to handle the .wav files.

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

## Development
##### Group Members
-- Kian Tanner

##### Contributors
-- N/A

##### Open Issues/Bugs
* User has to press enter twice after typing input file name or input text (only occurs when output to a file is selected)
* Report any issues or bugs on GitHub page, or email to kian.tanner@colorado.edu

##### Future Enhancements 
* [ ] Check input text file to see if any characters don't have morse code equivalents and remove them
* [ ] Allow user to not type file extension when entering input or output file names
* [ ] Allow user to speed up audio output to make files that could be transmitted faster
* [ ] Use external library (or make your own if you're that good) to read an audio file with a person speaking and translate that to morse code
* [ ] Use external text-to-speech library to output english as an audio file
* Please email any other suggestions to kian.tanner@colorado.edu

##### Examples
```sh

```

##### Morse Code Standard
This program uses standard morse code with some extended prosigns. A full list of availible characters that may be used can be viewed by running the program and selecting
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
- Cplusplus.com, for its reference pages on the C++ standard library
- [Dillinger](dillinger.io), for an in-browser, WYSIWYG markdown editor

## License
[GNU General Public License v3](http://www.gnu.org/licenses/gpl-3.0.html)
