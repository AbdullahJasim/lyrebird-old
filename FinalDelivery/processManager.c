/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include "processManager.h"

int getFreeProcesses () {
	int totalProcesses;

	totalProcesses = sysconf(_SC_NPROCESSORS_ONLN);
	return (totalProcesses - 1);
}

pid_t createChild (int parentToChild[], int childToParent[]) {
	pid_t pid;
	pid = fork();

	if (pid == 0) {
		close(parentToChild[1]);
		close (childToParent[0]);
		receiveLine(parentToChild[0], childToParent[1]);
		return pid;
	} else if (pid > 0) {
		close(parentToChild[0]);
		close(childToParent[1]);
		return pid;
	} else {
		perror("Forking failed. \n");
	}
}

int handleChildren(int numOfChildren, int parentToChild[][2], int childToParent[][2], int* childrenPids, int clientFD, int exit) {
	int i;
	fd_set set;
	FD_ZERO(&set);
	char message[2060];
	struct timeval tv;

	tv.tv_sec = 1;
  tv.tv_usec = 0;

	//The client has already been informed by the server to exit
	//Send any last messages and tell the children to exit
	if (exit > 0) {
		for (i = 0; i < numOfChildren; i++) {
			if (i != exit) {
				read (childToParent[i][0], message, sizeof(message));
				write(clientFD, message, strlen(message) + 1);
				read(clientFD, message, sizeof(message));
			}
			write(parentToChild[i][1], "\0", 2);
		}
		write(clientFD, "DONE", strlen("DONE") + 1);
		return 1;
	}

	for (i = 0; i < numOfChildren; i++) {
		bzero(message, 2060);

		FD_ZERO(&set);
		FD_SET(childToParent[i][0], &set);
		select(childToParent[i][0] + 1, &set, NULL, NULL, &tv);
		
		//A message has been received, send it to the server and receive the reply
		//Check if the reply is an indication to exit
		if (FD_ISSET(childToParent[i][0], &set)) {
			read (childToParent[i][0], message, sizeof(message));
			write(clientFD, message, strlen(message) + 1);
			bzero(message, 2060);
			read(clientFD, message, sizeof(message));
			if (strcmp(message, "We're done") != 0) {
				write(parentToChild[i][1], message, strlen(message) + 1);
			} else {
				return i;
			}
		}				
	}

	return 0;
}

void receiveLine (int fdIn, int fdOut) {
	int i, j, n;
	char message[2060];
	int busy = 0;
	char fileOne[1024];
	char fileTwo[1024];
	char timeStamp[50];

	//Inform the parent that the child is ready initially
	write (fdOut, "ready", strlen("ready") + 1);

	while (1) {
		read(fdIn, message, sizeof(message));
		if (strcmp(message, "Exit Now") == 0) {
			bzero(message, sizeof(message));
			write(fdOut, "OK", strlen("OK") + 1);
		} else if (strcmp(message, "\0") != 0) {
			strcpy (fileOne, readFileOne (message, fileOne, 1024));
			strcpy (fileTwo, readFileTwo (message, fileTwo, 1024));
			n = decryptFiles(fileOne, fileTwo);
			bzero(message, sizeof(message));			

			//Need to pass in n along with the file names and the process ID
			//The server should decide which message to output according to it
			snprintf(message, 2060, "%s %d %d", fileOne, getpid(), n);
			write(fdOut, message, strlen(message) + 1);
		} else if (strcmp(message, "\0") == 0) {
			close(fdIn);
			close(fdOut);
			exit(EXIT_SUCCESS);
		}
	}
}
