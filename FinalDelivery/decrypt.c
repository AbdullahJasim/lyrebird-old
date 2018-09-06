/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include "decrypt.h"

char letters[96];
int values[128];

int decryptFiles (char inputFile[], char outputFile[]) {
	char c;
	int extraCounter = 0;
	int charCounter = 6;
	long long encryption;
	long long groupEncryption = 0;
	long long groupCypher = 0;
	char* lettersGroup;
	time_t currentTime;
	char* currentTimeString;
	int j;

	//Read input file
	FILE *fileOne = fopen(inputFile, "r");

	//Error: read file is null - return with an error code 1
	if(fileOne == NULL) {
		return 1;
	}

	FILE *fileTwo = fopen(outputFile, "w");

	//Error: output file is inaccessible  - return with an error code 1
	if(access(outputFile, F_OK) != -1) {
		fileTwo = fopen(outputFile, "w");
	} else {
		return 2;
	}

	defineArrays();
	
	while(1) {
		if(feof(fileOne)) {break;}

		c = fgetc(fileOne);
		
		if(c == '\n') {
			fputs("\n", fileTwo);
			extraCounter = 0;
			charCounter = 6;

		//Still at the same tweet
		} else {
			extraCounter++;
			//Do nothing and ignore this character, it's extra. Reset extra counter
			if(extraCounter == 8) {
				extraCounter = 0;

			//Not an extra character, find the encryption value
			} else { 
				encryption = getEncryptionValue(charCounter - 1, c);
				//Error: weird character in the input - this error is not yet implemented as the encyrption is assumed to be correct
				if(encryption == -1) {
					perror("This character will not be considered due to being unknown. \n");
				} else {

					//Add the encryption value of this character to the group
					groupEncryption += encryption; 
					charCounter--;

					//End of a group of 6 characters, reset the group encryption value to 0 and the character counter to 6
					//Then get the mapped value to the sum of the group encyrption value, convert the number to letters and write them to the output file
					if(charCounter == 0) {
						groupCypher = getCypher(groupEncryption, 1921821779, 4294434817);
						lettersGroup = decrypt(groupCypher);
						fputs(lettersGroup, fileTwo);
						groupEncryption = 0;
						groupCypher = 0;
						charCounter = 6;
					}
				}
			}
		}
	}

	//Close the file once we're at the end of the file and the whole loop has been broken, no more reading/writing need to be done
	fclose(fileOne); 
	fclose(fileTwo); 

	//The program has run successfully
	//Print out the message here
	currentTime = time(NULL);
	currentTimeString = ctime(&currentTime);

	for (j = 0; j < strlen(currentTimeString); j++) {
		if (currentTimeString[j] == '\n') {							
			currentTimeString[j] = '\0';
		}
	}

	return 0;
}

void defineArrays() {
	letters[0] = ' ';
	letters[1] = 'a';
	letters[2] = 'b';
	letters[3] = 'c';
	letters[4] = 'd';
	letters[5] = 'e';
	letters[6] = 'f';
	letters[7] = 'g';
	letters[8] = 'h';
	letters[9] = 'i';
	letters[10] = 'j';
	letters[11] = 'k';
	letters[12] = 'l';
	letters[13] = 'm';
	letters[14] = 'n';
	letters[15] = 'o';
	letters[16] = 'p';
	letters[17] = 'q';
	letters[18] = 'r';
	letters[19] = 's';
	letters[20] = 't';
	letters[21] = 'u';
	letters[22] = 'v';
	letters[23] = 'w';
	letters[24] = 'x';
	letters[25] = 'y';
	letters[26] = 'z';
	letters[27] = '#';
	letters[28] = '.';
	letters[29] = ',';
	letters[30] = '\'';
	letters[31] = '!';
	letters[32] = '?';
	letters[33] = '(';
	letters[34] = ')';
	letters[35] = '-';
	letters[36] = ':';
	letters[37] = '$';
	letters[38] = '/';
	letters[39] = '&';
	letters[40] = '\\';

	values[32] = 0;
	values[97] = 1;
	values[98] = 2;
	values[99] = 3;
	values[100] = 4;
	values[101] = 5;
	values[102] = 6;
	values[103] = 7;
	values[104] = 8;
	values[105] = 9;
	values[106] = 10;
	values[107] = 11;
	values[108] = 12;
	values[109] = 13;
	values[110] = 14;
	values[111] = 15;
	values[112] = 16;
	values[113] = 17;
	values[114] = 18;
	values[115] = 19;
	values[116] = 20;
	values[117] = 21;
	values[118] = 22;
	values[119] = 23;
	values[120] = 24;
	values[121] = 25;
	values[122] = 26;
	values[33] = 31;
	values[35] = 27;
	values[36] = 37;
	values[38] = 39;
	values[39] = 30;
	values[40] = 33;
	values[41] = 34;
	values[44] = 29;
	values[45] = 35;
	values[46] = 28;
	values[47] = 38;
	values[58] = 36;
	values[63] = 32;
	values[92] = 40;
}

long long getCypher(long long base, long long exponent, long long mod) {	
	unsigned long long resultOne = 1;
	unsigned long long resultTwo = 1;
//Base case 1: the power is 0, the result is 1 % mod
	if(exponent == 0) {
		return (1 % mod);

//Base case 2: the power is 1, the result is base % mod
	} else if(exponent == 1) {
		return (base % mod);

//Recursive case 1: the power is even, recrusive call using half the power
	} else if((exponent % 2) == 0){
		resultOne = getCypher(base, exponent / 2, mod);
		resultOne = (resultOne * resultOne) % mod;
		return resultOne;

//Recusrive case 2: the power is odd, split it into base case 1 and recursive case 1
	} else {
		resultOne = getCypher(base, 1, mod);
		resultTwo = getCypher(base, exponent - 1, mod);
		resultOne = (resultOne * resultTwo) % mod;
		return resultOne;
	}
}

char *decrypt(long long input) {
	static char letters[6];
	long long remainder = input % 41;
	letters[5] = getDecryptionValue((int) remainder);
	remainder = (input / 41) % 41;
	letters[4] = getDecryptionValue((int) remainder);
	remainder = (input / (long long) pow(41, 2)) % 41;
	letters[3] = getDecryptionValue((int) remainder);
	remainder = (input / (long long) pow(41, 3)) % 41;
	letters[2] = getDecryptionValue((int) remainder);
	remainder = (input / (long long) pow(41, 4)) % 41;
	letters[1] = getDecryptionValue((int) remainder);
	remainder = (input / (long long) pow(41, 5)) % 41;
	letters[0] = getDecryptionValue((int) remainder);
	return letters;
}

char getDecryptionValue(int x) {
	return letters[x];
}

long long getEncryptionValue(int power, char c) {
	long long result = 0;
	result = (long long) pow(41, power);
	result = result * values[(int) c];
	return result;
}
