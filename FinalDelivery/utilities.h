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
#include <time.h>
#include <string.h>

//Helper function to get a string for the current time stamp
char* getTimeStamp (char timeStamp[]);

//Helper function to perform sanity checks for input for the server
void checkInputServer (char **argv);

//Helper function to perform sanity checks for input for the client
void checkInputClient (char **argv);


//Function to open user specified files in read mode
FILE* openReadFile(char *fileName);

//Function to open user specified files in write mode
FILE* openWriteFile(char *fileName);
