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

char* readFileOne (char line[], char fileOne[], int fileSize) {
	int i = 0;
	int j = 0;

	bzero(fileOne, fileSize);

	while (line[i] != ' ' && line[i] != '\n') {
		fileOne[j] = line[i];
		i++; j++;
		if (i >= fileSize) { perror("Input file size is too long\n");	break;}
	}

	fileOne[i] = '\0';
	return fileOne;
}

char* readFileTwo (char line[], char fileTwo[], int fileSize) {
	int i = 0;
	int j = 0;

	bzero(fileTwo, fileSize);

	while (line[i] != ' ') { i++;}
	i++;

	while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0') {
		fileTwo[j] = line[i];
		i++;
		j++;
		if (i >= fileSize) { perror("Output file size is too long\n"); break;}
	}

	fileTwo[i] = '\0';
	return fileTwo;
}

char readParamThree (char line[], char returnValue) {
	int i = 0;
	
	while (line[i] != ' ') { i++;}
	i++;
	while (line[i] != ' ') { i++;}
	i++;

	return line[i];
}

char* getNextLine(FILE* configFile, char* line) {
	char c;
	int i = 0;
	
	bzero(line, sizeof(line));

	while(1) {
		if(feof(configFile)) { strcpy(line, "END OF FILE");	break;}

		c = fgetc(configFile);

		if (c == '\n' || c == '\0') { line[i] = '\n'; break;
		} else { line[i] = c;	i++; }
	}

	return line;
}

int isFileEmpty(FILE* configFile) {
	fseek(configFile, 0, SEEK_END);
	unsigned long len = (unsigned long) ftell(configFile);
	if (len > 0) {
		rewind(configFile);
		return 1;
	} else {
		return 0;
	}
}
