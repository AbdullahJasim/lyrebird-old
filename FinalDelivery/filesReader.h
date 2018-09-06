/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include <stdio.h>
#include <math.h>
#include <unistd.h>

//Function to read in the first file in a line. Starts at the beginning of the line and ends at the first space
char* readFileOne (char line[], char fileOne[], int fileSize);

//function to read the second file in a line. Starts after the first space and ends at the second space or end of line
char* readFileTwo (char line[], char fileTwo[], int fileSize);

//Function to read a third parameter in a line, only reads a single character
char readParamThree (char line[], char returnValue);

//Function to read an entire line in a file
char* getNextLine(FILE* configFile, char* line);

//Function to check that a file is empty or not
int isFileEmpty(FILE* configFile);
