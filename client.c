#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "libnetfiles.h"

#define MAXRCVLEN 500
#define PORTNUM 9000

void sampleConnection(){
	char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
	int len, mysocket;
	struct sockaddr_in dest;
	
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&dest, 0, sizeof(dest)); /* zero the struct */
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("127.0.0.1"); /* set destination IP number*/
	dest.sin_port = htons(PORTNUM); /* set destination port number*/
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
	len = recv(mysocket, buffer, MAXRCVLEN, 0);

	/* We have to null terminate the received data ourselves */
	buffer[len] = '\0';
	printf("\tReceived %s (%d bytes).\n", buffer, len);
	close(mysocket);
}

int main(int argc, char *argv[])
{
	int choice = -1;
	
	printf("Welcome to the client software. Ready to interact with remote files?\n");
	while(choice != 0){
		printf("What would you like to do?\n1. Test a local connection to the server.\n0. Quit.\n");
		scanf("%d", &choice);
		puts("");
		switch(choice){
		case 0:
			foolio();
			break;
		case 1:
			sampleConnection();
			break;
		default:
			printf("That is not a valid option!\n");
		}
		puts("");
	}
	printf("Thank you for your participation!\n");
	return EXIT_SUCCESS;
}
