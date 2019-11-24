#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

//implementation of functions in header file
int setupServerSocket(int portno){

}

int callServer(char* host, int portno); // Like new Socket in Java

int serverSocketAccept(int serverSocket); // Like ss.accept() in Java

void writeInt(int x, int socket); // Write an int over the given socket

int readInt(int socket); // Read an int from the given socket
