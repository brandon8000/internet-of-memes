#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "libnetfiles.h"
#define MAXRCVLEN 2048
#define PORTNUM 9000

int total_foo = 42;

void foolio(){
	printf("\t\tThis is your library speaking. Our global variable, total_foo, is: %d",total_foo);
	
}

//this is where the real code begins!

extern int netserverinit(char* hostname){
	return -1;
}

/* For extension A only
extern int netserverinit(char* hostname, int filemode){
	return -1;
}
*/

extern char* sendRequest(char* message){
	void* babyBuff = malloc(sizeof(char) * MAXRCVLEN);
	int mysocket;
	struct sockaddr_in dest;
	int delivered;
	
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t socksize = sizeof(struct sockaddr_in);
	memset(&dest, 0, sizeof(dest)); /* zero the struct */
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number*/
	dest.sin_port = htons(PORTNUM); /* set destination port number*/
	
	connect(mysocket, (struct sockaddr *) &dest, sizeof(struct sockaddr) );
	delivered = sendto(mysocket, message, strlen(message), 0, (struct sockaddr *) &dest, sizeof(struct sockaddr));
	printf("\t%d out of %d bytes were sent\n",delivered, (int) strlen(message) );
	
	recvfrom(mysocket, babyBuff, MAXRCVLEN, 0, (struct sockaddr *) &dest, &socksize);
	printf("\tReceived %s\n", (char*) babyBuff );
	
	close(mysocket);
	return babyBuff;
}

extern int netopen(const char* pathname, int flags){
	//maybe do some error checking
	char* paramBundle = (char*) malloc( sizeof(char*) * (strlen(pathname) +1 ) );
	sprintf(paramBundle, "o%d%s",flags,pathname);
	return *( (int*) sendRequest(paramBundle) );
}
/*
extern ssize_t netread(int fildes, void* buf, size_t nbyte){
	//maybe do some error checking
	char* paramBundle = (char*) malloc( sizeof(char*) * (strlen(pathname) +1 ) );
	sprintf(paramBundle, "o%d%s",flags,pathname);
	return *( (int*) sendRequest(paramBundle) );
}

extern ssize_t netwrite(int fildes, const void* buf, size_t nbyte){
	//maybe do some error checking
	char* paramBundle = (char*) malloc( sizeof(char*) * (strlen(pathname) +1 ) );
	sprintf(paramBundle, "o%d%s",flags,pathname);
	return *( (int*) sendRequest(paramBundle) );
}
*/
extern int netclose(int fd){
	//maybe do some error checking
	// This allocation of 3 bytes assumes one byte for the first character
	// and a maximum of 2 bytes for the passed in file descriptor
	//(which means a file descriptor of 99 or less)
	char* paramBundle = (char*) malloc( sizeof(char*) * 3);
	sprintf(paramBundle, "c%d",fd);
	return *( (int*) sendRequest(paramBundle) );
}

