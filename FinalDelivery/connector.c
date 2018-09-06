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

void handleRequests(int serverFD, FILE* configFile, FILE* loggingFile) {
	int readyToBreak = 0;
	int done = 0;
	int maxClients = 10;
	int j;
	fd_set clients;
	char message[20];
	int numOfClients = 0;

	//A dynamic array to store all the client file descriptors. Begin with 10, multiply by 2 everytime it overflows
	//And a dynamic array to store the corresponding IP addresses for the clients
	int *clientFDs = (int *) malloc (maxClients * sizeof(int));
	char (*clientIPs)[20] = malloc (maxClients * sizeof(char));

	listen(serverFD, 1);

	while(1) {
		//Ready to exit, inform all clients to close
		if (readyToBreak > 0) {
			waitOnClients(numOfClients, clients, serverFD, clientFDs, clientIPs, loggingFile);
			free(clientFDs);
			free(clientIPs);
			break;
		}

		if (done > 0) {readyToBreak = 1;}
		if (feof(configFile)) {	done = 1;}

		//Dynamic array overflow, reallocate to a larger one
		if (numOfClients == maxClients) {
			maxClients = maxClients * 2;
			clientFDs = (int *) realloc (clientFDs, maxClients * sizeof(int));
			clientIPs = realloc (clientIPs, maxClients * sizeof(char));
		}

		//Accept new connections and check existing ones if they're ready to receive new line
		numOfClients = acceptNewConnections(serverFD, clients, clientFDs, clientIPs, numOfClients, loggingFile);
		numOfClients = checkClients(numOfClients, clientFDs, clientIPs, clients, configFile, loggingFile);
	}

	return;
}

int acceptNewConnections(int serverFD, fd_set clients, int* clientFDs, char (*clientIPs)[20], int clientsNum, FILE* loggingFile) {
	socklen_t clientLength;
	int clientFD, j;
	struct sockaddr_in clientAddress;
	struct timeval tv;
	char timeStamp[50];
	char log[1200];

	tv.tv_sec = 1;
  tv.tv_usec = 0;

	FD_ZERO(&clients);
	FD_SET(serverFD, &clients);

	//A connection has been stablished, add it to the arrays and increment the number of current clinets by 1
	if (select(serverFD + 1, &clients, NULL, NULL, &tv) > 0) {
		clientLength = sizeof(clientAddress);
		clientFD = accept(serverFD, (struct sockaddr *) &clientAddress, &clientLength);
		clientFDs[clientsNum] = clientFD;
		inet_ntop(AF_INET, &(clientAddress.sin_addr.s_addr), clientIPs[clientsNum], 20);
		strcpy (timeStamp, getTimeStamp (timeStamp));
		snprintf(log, 1200, "[%s] Successfully connected to lyrebird client %s.\n", timeStamp, clientIPs[clientsNum]);
		fputs(log, loggingFile);
		clientsNum++;
	}

	return clientsNum;
}

int checkClients(int clientsNum, int* clientFDs, char (*clientIPs)[20], fd_set clients, FILE* configFile, FILE* loggingFile) {
	int i;
	char message[2060];
	char log[1200];
	char line[2060];
	char file[1024];
	char clientPid[30];
	char returnValue;
	char timeStamp[50];
	struct timeval tv;

	tv.tv_sec = 1;
  tv.tv_usec = 0;

	for (i = 0; i < clientsNum; i++) {
    FD_ZERO(&clients);
    FD_SET(clientFDs[i], &clients);
    select(clientFDs[i] + 1, &clients, NULL, NULL, &tv);
    if (FD_ISSET(clientFDs[i], &clients)) {
			//Check if the message is empty, if it is then the server has disconnected
			if (read(clientFDs[i], message, sizeof(message)) <= 0) {
				strcpy (timeStamp, getTimeStamp(timeStamp));
				snprintf(log, 1200, "[%s] lyrebird client %s has disconnected expectedly.\n", timeStamp, clientIPs[i]);
				fputs(log, loggingFile);
				clientsNum--;
			} else {
				bzero(line, 2060);
				strcpy(line, getNextLine(configFile, line));

				//We still have lines in the configuration file, send them to the client
				if (strcmp(line, "END OF FILE") != 0) {
					bzero(file, 1024);
					bzero(log, 1200);
					write(clientFDs[i], line, strlen(line) + 1);
					strcpy (timeStamp, getTimeStamp(timeStamp));
					strcpy (file, readFileOne (message, file, 1024));
					snprintf(log, 1200, "[%s] The lyrebird client %s has been given the task of decrypting %s.\n", timeStamp, clientIPs[i], file);
					fputs(log, loggingFile);
				} else {
					write(clientFDs[i], "We're done", strlen("We're done") + 1);
				}

				//If this is not the initial message from the children, then get the result from them and log it
				if (strcmp(message, "ready") != 0) {
					bzero(file, 1024);
					bzero(log, 1200);
					bzero(clientPid, 30);
					bzero(log, sizeof(log));
					strcpy (timeStamp, getTimeStamp(timeStamp));
					strcpy(file, readFileOne(message, file, 1024));
          strcpy(clientPid, readFileTwo(message, clientPid, 30));
					returnValue = readParamThree(message, returnValue);

					if (returnValue == '0') {
						snprintf(log, 1200, "[%s] The lyrebird client %s has successfully decrypted %s in process %s.\n", timeStamp, clientIPs[i], file, clientPid);
					} else {
						snprintf(log, 1200, "[%s] The lyrebird client %s has encountered an error: Unable to open file %s in process %s.\n", timeStamp, clientIPs[i], file, clientPid);
					}

					fputs(log, loggingFile);
					//printf("%s\n", log);
				}
			}
		}
	}

	return clientsNum;
}

void waitOnClients(int numOfClients, fd_set clients, int serverFD, int *clientFDs, char (*clientIPs)[20], FILE* loggingFile) {
	int i = 0;
	int j = numOfClients;
	char message[1200];
	int n;
	char log[1200];
	char file[1024];
	char clientPid[30];
	char returnValue;
	char timeStamp[50];

	while (j > 0) {
		for (i = 0; i < numOfClients; i++) {
			bzero(message, sizeof(message));
			while (strcmp(message, "DONE") != 0) {
				n = read(clientFDs[i], message, sizeof(message));

				//Receive any final messages from the clients and log them
				if (strcmp(message, "ready") != 0 && strcmp(message, "DONE") != 0 ) {
					bzero(log, sizeof(log));
					strcpy (timeStamp, getTimeStamp(timeStamp));
					strcpy(file, readFileOne(message, file, 1024));
          strcpy(clientPid, readFileTwo(message, clientPid, 30));
					returnValue = readParamThree(message, returnValue);

					if (returnValue == '0') {
						snprintf(log, 1200, "[%s] The lyrebird client %s has successfully decrypted %s in process %s.\n", timeStamp, clientIPs[i], file, clientPid);
					} else {
						snprintf(log, 1200, "[%s] The lyrebird client %s has encountered an error: Unable to open file %s in process %s.\n", timeStamp, clientIPs[i], file, clientPid);
					}

					fputs(log, loggingFile);
					//printf("%s\n", log);
				}

				write(clientFDs[i], "We're done", strlen(message) + 1);
				j--;
			}

			strcpy (timeStamp, getTimeStamp(timeStamp));
			snprintf(log, 1200, "[%s] lyrebird client %s has disconnected expectedly.\n", timeStamp, clientIPs[i]);
			fputs(log, loggingFile);
		}
	}
}
