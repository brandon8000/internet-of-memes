# This is the Makefile for Group 53's Asst3 project. This
# program uses our custom-made mymalloc library.
# Typing 'make' will create the necessary executable file.
#

# first we define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#	-pedantic will be necessary as the TAs seem to use it

CC = gcc
CFLAGS  = -g -Wall


# remove old builds and then start a new build
# CHANGE THIS BEFORE SUBMISSION (should be "default: clean server")
default: clean server library client

# Create the file server executable
server:
	$(CC) $(CFLAGS) -o server netfileserver.c

# Create the library object file
library: libnetfiles.h
	$(CC) $(CFLAGS) -c libnetfiles.c

# Create the client executable
client:
	$(CC) $(CFLAGS) -o client client.c libnetfiles.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and any ~ backup files:
clean:
	$(RM) client server *.o *~
