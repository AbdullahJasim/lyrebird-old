/*
NAME: 				Abdullah Jasim
STUDENT NUMBER: 	301093885
SFU USERNAME: 		ajasim
LECTURE SECTION: 	D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 			Scott Kristjanson
*/

//The function to define the 2 mapping arrays. The first one (letters) is to get the letter from an int value for decryption
//The second array (values) is to get the encryption value from the ASCII value of each letter
void defineArrays();

//The function to get the mapped value for each group of 6
//A combination of modular exponentiation and exponentiation by squaring is used t get the result
//(base ^ a) mod m = (((base ^ a - b) mod m) * ((base ^ b) mod m))) mod m
//When the power is even, find the modular exponentiation of its half. When it's odd, find the modular expoentiation of it - 1, and its half
//When the power is 1 or 0, we have a base case 
long long getCypher(long long base, long long exponent, long long mod);

//The function to get the 6 characters from the value gotten from the map formular
char *decrypt(long long input);

//The function to return the letter from the int value
char getDecryptionValue(int x);

//The function to get the encryption value of each character
long long getEncryptionValue(int power, char c);
