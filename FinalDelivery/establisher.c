/*
NAME: 							Abdullah Jasim
STUDENT NUMBER: 		301093885
SFU USERNAME: 			ajasim
LECTURE SECTION: 		D100
INSTRUCTOR'S NAME: 	Brian G. Booth
TA'S NAME: 					Scott Kristjanson
*/

#include "establisher.h"

int bindSocket(int serverFD, struct sockaddr_in serverAddress, int portNum) {
	socklen_t serverLength;
	
	serverAddress.sin_family = AF_INET;
	bind(serverFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

	serverLength = sizeof(serverAddress);	
	getsockname(serverFD, (struct sockaddr *) &serverAddress, &serverLength);
	
	portNum = ntohs(serverAddress.sin_port);
	return portNum;
}

char* getIPAddress(char ipaddress[]) {
	  struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa -> ifa_next) {
        if (!ifa -> ifa_addr) { continue;}
        if (ifa -> ifa_addr -> sa_family == AF_INET) {
            tmpAddrPtr = &((struct sockaddr_in *) ifa -> ifa_addr) -> sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
						if (strcmp(addressBuffer, "127.0.0.1") != 0 && strcmp(addressBuffer, "0.0.0.0") != 0) {
							strcpy(ipaddress, addressBuffer);
							break;
						}
        }
    }

    if (ifAddrStruct!= NULL) { freeifaddrs(ifAddrStruct);}
    return ipaddress;
}
