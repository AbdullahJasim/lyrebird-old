/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>

//Function to bind the server file descriptor to the socket
//Bind to port an undeclared value to make sure that we get an available port
//Then get the port number from the socket
int bindSocket(int serverFD, struct sockaddr_in serverAddress, int portNum);

//Function to get the UP address of the current local machine
//Taken from http://stackoverflow.com/questions/212528/get-the-ip-address-of-the-machine
//And modified to fit the situation
char* getIPAddress(char ipaddress[]);
