/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include <stdio.h>
#include <unistd.h>
#include "filesReader.c"

//Function to calculate how many processes we can create on the current machine
int getFreeProcesses ();

//Function to create a child, returns its process ID
pid_t createChild (int parentToChild[], int childToParent[]);

//Function for the child to get a line from the parent
void receiveLine (int fdIn, int fdOut);

//Function for the parent to handle its children. Returns the index of the child it was at when the server asked it to exit
int handleChildren(int numOfChildren, int parentToChild[][2], int childToParent[][2], int* childrenPids, int clientFD, int exit);
