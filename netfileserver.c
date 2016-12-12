#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#define MAXRCVLEN 2048
#define PORTNUM 9000

int main(int argc, char *argv[])
{
	struct sockaddr_in dest; /* socket info about the machine connecting to us */
	struct sockaddr_in serv; /* socket info about our server */
	int mysocket; /* socket used to listen for incoming connections*/
	
	printf("Firing up the server, dude!\n");
	socklen_t socksize = sizeof(struct sockaddr_in);
	memset(&serv, 0, sizeof(serv)); /* zero the struct before filling the fields */
	serv.sin_family = AF_INET; /* set the type of connection to TCP/IP */
	serv.sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
	serv.sin_port = htons(PORTNUM); /* set the server port number */
	mysocket = socket(AF_INET, SOCK_STREAM, 0); /* bind serv information to mysocket */
	bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
	
	/* start listening, allowing a queue of up to 1 pending connection */
	printf("Server listening on __ <-- localhost? port number?\n");
	listen(mysocket, 1);
	int consocket = accept(mysocket, (struct sockaddr *) &dest, &socksize);
	char* request = (char*) malloc(sizeof(char)*MAXRCVLEN);
	//void* request = malloc(requestSize);
	
	int msglen = -1;
	int firstParam = -1;
	//int secondParam = -1;
	//char* response;
	//a boolean flag to let us know when the server has accomplished its mission.
	int responseSent;
	//int loopCounter;
	int delivered = -32;
	while(consocket)
	{
		/*Spawn a thread to do the real work*/
		responseSent = -1;
		
		recvfrom(consocket, request, MAXRCVLEN, 0, (struct sockaddr *) &dest, &socksize);
		printf("Incoming connection from %s with the following request: %s of length %d\n",	inet_ntoa(dest.sin_addr), request, (int) strlen(request) );
		msglen = (int) strlen(request);
		switch(request[0]){
		case 'r':
			printf("We will read another day...\n");
			break;
		case 'w':
			printf("We will write another day...\n");
			break;
		case 'o':
			if(msglen > 2)
				firstParam = atoi( &(request[1]) );
			else{
				sendto(consocket, "qed", 3, 0, (struct sockaddr *) &dest, socksize);
				++responseSent;
				break;
			}
			char* path = (char*) malloc(sizeof(char) * (msglen-2) );
			path = &(request[2]);
			printf("These are the inputs:\n");
			printf("\tpath: %s\n\tflag: %d\n",path,firstParam);
			int fildes = open(path, firstParam);
			printf("Returning %d to the client, of size %d\n", fildes, (int) sizeof(&fildes) );
			delivered = sendto(consocket, &fildes, (int) sizeof(&fildes), 0, (struct sockaddr *) &dest, socksize);
			printf("\t%d out of %d bytes were returned\n",delivered,(int) sizeof(&fildes));
			++responseSent;
			break;
		case 'c':
			// need to add some kind of code here because GCC throws errors when
			// you start a case block with a declaration;
			delivered = -33;
			char* givenInteger = (char*) malloc(sizeof(char) * (msglen-1) );
			givenInteger = &(request[1]);
			int output = close(atoi(givenInteger));
			delivered = sendto(consocket, &output, (int) sizeof(&output), 0, (struct sockaddr *) &dest, socksize);
			printf("\t%d out of %d bytes were returned\n",delivered,(int) sizeof(&output));
			++responseSent;
			break;
		default:
			//set errors
			printf("Bad command given!\n");
			break;
		}
		if(responseSent > -1)
			break;
	}
	// I think this was just extra:
	//	consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
	printf("We are about to close everything!\n");
	close(consocket);
	close(mysocket);
	return EXIT_SUCCESS;
}
