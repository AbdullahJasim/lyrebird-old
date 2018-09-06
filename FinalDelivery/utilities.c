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

char* getTimeStamp (char timeStamp[]) {
	int i = 0;
	time_t currentTime;

	currentTime = time(NULL);
	timeStamp = ctime(&currentTime);

	for (i = 0; i < strlen(timeStamp); i++) {
		if (timeStamp[i] == '\n') {							
			timeStamp[i] = '\0';
		}
	}

	return timeStamp;
}

void checkInputServer (char **argv) {
//Error: no config file was specified - inform user and terminate
	if(argv[1] == NULL) {
		perror("No configuration file was given. Terminating program.\n");
		exit(EXIT_FAILURE);
	}
//Error: no logging file was specified - inform user and terminate
	if(argv[2] == NULL) {
		perror("No logging file was given, Terminating program.\n");
		exit(EXIT_FAILURE);
	}

//Error: more than 2 parameters were given, take the first 2 and inform user
	if(argv[3] != NULL) {
		printf("More than two files were specified. Only considering first two parameters. \n");
	}
}

void checkInputClient (char **argv) {
//Error: no IP address was given - inform user and terminate
	if(argv[1] == NULL) {
		perror("No IP address was given. Terminating program.\n");
		exit(EXIT_FAILURE);
	}
//Error: no port number was specified - inform user and terminate
	if(argv[2] == NULL) {
		perror("No port number was given, Terminating program.\n");
		exit(EXIT_FAILURE);
	}

//Error: more than 2 parameters were given, take the first 2 and inform user
	if(argv[3] != NULL) {
		printf("More than two parameters were specified. Only considering first two parameters. \n");
	}
}

//Function to open user specified files in read mode
FILE* openReadFile(char *fileName) {
		FILE* file = fopen(fileName, "r");

//Error: the file specified does not exist - terminate program
	if(file == NULL) {
		perror("File to read from does not exist. Terminating program.\n");
		exit(EXIT_FAILURE);
	}

	return file;
}

FILE* openWriteFile(char *fileName) {
	FILE* file = fopen(fileName, "w");

//Error: the file specified does not exist - terminate program
	if(file == NULL) {
		perror("File to read from does not exist. Terminating program.\n");
		exit(EXIT_FAILURE);
	}

	return file;
}
