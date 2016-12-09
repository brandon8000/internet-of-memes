#include <stdio.h>
//I don't know how many imports we will need, LOL
//#include <unistd.h>
//#include <stdlib.h>
//#include <errno.h>
#include "libnetfiles.h"

int total_foo = 42;

void foolio(){
	printf("\t\tThis is your library speaking. Our global variable, total_foo, is: %d",total_foo);
	
}

//this is where the real code begins!

extern int netopen(const char* pathname, int flags){
	return -1;
}

extern ssize_t netread(int fildes, void* buf, size_t nbyte){
	return -1;
}

extern ssize_t netwrite(int fildes, const void* buf, size_t nbyte){
	return -1;
}

extern int netclose(int fd){
	return -1;
}

