#ifndef _LIBNETFILES_H_
#define _LIBNETFILES_H_

    #include <stdlib.h>
    
    // This constant represents the maximum length of a file path that we will accept
    #define MAX_FILE_PATH 300

    // a sample type definition that is exported by library:
	struct foo_struct {  
		int x;
        float y;
        char* words;
    };
    typedef struct foo_struct foo_struct;

    // a sample global variable that is exported by library
    // "extern" means that this is not a variable declaration, it 
    // just defines that a variable named total_foo of type int
    // exists and you can use it (its declaration is in some library source file)
    extern int total_foo; 	

    // a sample function prototype for a function exported by library:
    extern void foolio();
    
    extern int netserverinit(char* hostname);

	/* For extension A only
	extern int netserverinit(char* hostname, int filemode);
	*/

	extern char* sendRequest(char* message);
	
    /*
    The argument flags must include one of the following access modes: O_RDONLY, O_WRONLY, or O_RDWR.
    These request opening the file read-only, write-only, or read/write, respectively.
	RETURN VALUE
		netopen() returns the new file descriptor, or -1 if an error occurred (in which case, errno is set appropriately).
	ERRORS (check open manpage for definition)
	reqiured:
		EACCES
		EINTR
		EISDIR
		ENOENT
		EROFS
	optional (you may want/need)
		ENFILE
		EWOULDBLOCK
		EPERM
    */
    extern int netopen(const char* pathname, int flags);
    
    /*
    RETURN VALUE
		Upon successful completion, netread() should return a non-negative integer indicating the
		number of bytes actually read. Otherwise, the function should return -1 and set errno to
		indicate the error.
	ERRORS (check manpage for definition)
	required:
		ETIMEDOUT
		EBADF
		ECONNRESET
    */
    extern ssize_t netread(int fildes, void* buf, size_t nbyte);
    
    /*
    RETURN VALUE
		Upon successful completion, netwrite() should return the number of bytes actually written to
		the file associated with fildes. This number should never be greater than nbyte. Otherwise, -1
		should be returned and errno set to indicate the error.
	ERRORS
	required:
		EBADF
		ETIMEOUT
		ECONNRESET
    */
    extern ssize_t netwrite(int fildes, const void* buf, size_t nbyte);
    
    /*
    RETURN VALUE
		netclose() returns zero on success. On error, -1 is returned, and errno is set appropriately.
		ERRORS
			ERRORS
			EBADF
    */
    extern int netclose(int fd);

#endif

