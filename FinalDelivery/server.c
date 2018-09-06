/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include "utilities.c"
#include "filesReader.c"
#include "establisher.c"
#include "connector.c"
#include "memwatch.h"

void main (int argc, char **argv);

void main (int argc, char **argv) {
	int serverFD, portNum, clients;
	char timeStamp[50], ipaddress[20];
	struct sockaddr_in serverAddress;
	FILE* configFile;
	FILE* loggingFile;

	//Input sanity checks
	checkInputServer(argv);
	configFile = openReadFile(argv[1]);
	loggingFile = openWriteFile(argv[2]);

	int n = isFileEmpty(configFile);
	if (n <= 0) {
		perror("Configuration file is empty. Terminating program.\n");
		exit(EXIT_SUCCESS);
	}
	
	//Create internet stream socket
	serverFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFD < 0) {
		strcpy (timeStamp, getTimeStamp (timeStamp));
		printf("[%s] Opening the socket failed. Terminating program.\n", timeStamp);
		exit(EXIT_FAILURE);
	}

	//Reset the inital values of the server address
	bzero((char *) &serverAddress, sizeof(serverAddress));
	
	//Get port number and IP address
	portNum = bindSocket(serverFD, serverAddress, portNum);
	strcpy(ipaddress, getIPAddress(ipaddress));

	//Output initial message
	strcpy (timeStamp, getTimeStamp (timeStamp));
	printf("[%s] lyrebird.server: PID %d on host %s, port %d\n", timeStamp, getpid(), ipaddress, portNum);

	//Call the function to handle all incoming requests
	handleRequests(serverFD, configFile, loggingFile);

	fclose(configFile);
	fclose(loggingFile);
	strcpy (timeStamp, getTimeStamp (timeStamp));
	printf("[%s] lyrebird server: PID %d completed its tasks and is exiting successfully.\n", timeStamp, getpid());
	exit(EXIT_SUCCESS);
}
