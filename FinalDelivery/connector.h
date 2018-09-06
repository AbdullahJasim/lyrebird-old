/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

//Function to handle all incoming requests from clients, be it new ones or existing ones
void handleRequests(int serverFD, FILE* configFile, FILE* loggingFile);

//Function to check if new clients are trying to connect. Store the FD in the dynamic array
int acceptNewConnections(int serverFD, fd_set clients, int* clientFDs, char (*clientIPs)[20], int i, FILE* loggingFile);

//Function to check if any of the existing connections are ready to receive a new line
int checkClients(int clientsNum, int* clientFDs, char (*clientIPs)[20], fd_set clients, FILE* configFile, FILE* loggingFile);

//Function to wait for clients to exit and pick up any last messages from them
void waitOnClients(int numOfClients, fd_set clients, int serverFD, int *clientFDs, char (*clientIPs)[20], FILE* loggingFile);
