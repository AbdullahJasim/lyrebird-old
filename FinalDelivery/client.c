/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include "client.h"

void main(int argc, char **argv) {
	int clientFD, portNum, freeProcesses, i;
	int childIndex = 0;
	char line[2060];
	char message[20];
	char timeStamp[50];
	char* ipAddress;
	in_addr_t ipBinary;
	struct sockaddr_in serverAddress;
  struct hostent *server;
	pid_t pid;

	//Get input parameters from user, the IP address of the host and the port number
	checkInputClient(argv);
	ipAddress = argv[1];
	portNum = atoi(argv[2]);
	ipBinary = inet_addr(ipAddress);

	//Connect to the server
	server = gethostbyaddr(&ipBinary, sizeof(ipBinary), AF_INET);

	bzero((char *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_addr.s_addr = ipBinary;
	
	clientFD = socket(AF_INET, SOCK_STREAM, 0);
	serverAddress.sin_family = AF_INET;
  bcopy((char *) server -> h_addr, (char *) &serverAddress.sin_addr.s_addr, server -> h_length);
	serverAddress.sin_port = htons(portNum);

	if (connect(clientFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
		perror("Unable to connect to this server. Please try again.\n");
		exit(EXIT_FAILURE);
	} else {
		strcpy (timeStamp, getTimeStamp (timeStamp));
		printf("[%s] lyrebird client: PID %d connected to server %s on port %d.\n", timeStamp, getpid(), ipAddress, portNum);
	}

	//Create child processes and manage them
	freeProcesses = getFreeProcesses();

	//Create the 2D arrays for the file directories between the parent and the children
	//One array is for parent to write and children to read, the other is the opposite
	//We also create an array to store the process ID's for children
	int parentToChild [freeProcesses][2];
	int childToParent [freeProcesses][2];
	int childrenPids [freeProcesses];

	//Create all the child process and setup the pipes between them and the parent process
	for (i = 0; i < freeProcesses; i++) {
		pipe(parentToChild[childIndex]);
		pipe(childToParent[childIndex]);
		pid = createChild(parentToChild[childIndex], childToParent[childIndex]);
		childrenPids[i] = pid;
		childIndex++;
	}

	//While loop to keep checking for any messages from child process and to manage connection to server
	while (1) {
		int n = handleChildren(childIndex, parentToChild, childToParent, childrenPids, clientFD, 0);
		if (n > 0) {
			handleChildren(childIndex, parentToChild, childToParent, childrenPids, clientFD, n);
			break;
		}
	}

	//Wait for all children to exit then close socket and exit
	int exitStatus;
	while(childIndex > 0) {
		pid = wait(&exitStatus);
		if(exitStatus > 0) {
			strcpy (timeStamp, getTimeStamp (timeStamp));
			printf("[%s] Child process ID #%d did not terminate successfully. \n", timeStamp, pid);
		}
		childIndex--;
	}

	strcpy (timeStamp, getTimeStamp (timeStamp));
	printf("[%s] lyrebird client: PID %d completed its tasks and is exiting successfully.\n", timeStamp, getpid());
	close(clientFD);
	exit(EXIT_SUCCESS);
}
