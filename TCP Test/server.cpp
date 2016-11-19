#include "TCPServerSocket.h"
#include "TCPSocket.h"
#include "includes.h"
#include "common.h"

void terminate_with_error (const char * error_msg,int sock)
{
	printf ("%s\n",error_msg); // printing error
	perror("Socket Error:"); // printing system error

	if (sock != -1) // Close socket and exit is socket opened
	{
	close (sock);
	exit(1);
	}
}

int main (int argc,char ** argv) {
	int sock; // Socket Handler
	struct sockaddr_in serverAddr; // Server Address Structure
	struct sockaddr_in clientAddr; // Client Address Structure
	socklen_t sin_size = sizeof(struct sockaddr_in); // Address Structur Size
	
	// Try to allocate a socket and if fail we terminate with an error.
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) terminate_with_error("Error Creating Socket",sock);

	int sock_opt = 1; // An integer to be used with sock opt
	// Setting socket reuse option so after the program terminates we can acquire the socket again on the same port without going into a grace period.
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void *)&sock_opt,sizeof (sock_opt));
	serverAddr.sin_family = AF_INET; // Set the communication family
	serverAddr.sin_port = htons(9999); // Set the port number
	serverAddr.sin_addr.s_addr = INADDR_ANY;// Set the socket to operate on all IP address and network interfaces available
	bzero(&(serverAddr.sin_zero), 8); // We zero out the rest of the sockaddr_in to make it identical to sockaddr
	
	// Try to bind on the socket port, and if it fails we exit. Will fail if the socket is already acquired by another process
	// or the program runs with less priviledges that cannot allow binding
	if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1)
		terminate_with_error("Error Binding",sock);

	while(1)
	{
		// Create the socket liten queue with size 10.
		if (listen(sock, 10) == -1) 
			terminate_with_error("Error Listening: ",sock);

		int newsock = accept(sock, (struct sockaddr *)&clientAddr,&sin_size); // Wait for connection
	
		if ( newsock < 1 )
			terminate_with_error("Error Accepting Socket",0); // if failed exit.
		else {
			int maxBytes = 1024; // size of buffer
			char buffer[maxBytes]; // alocat buffer of 1 K
			memset(buffer,0,maxBytes); // initialize it.
			int bytes_read = recv (newsock,buffer,maxBytes,0); // read data from the socket
	
			// if returned number of bytes is bigger that zero then print information about client and the message
			if ( bytes_read > 0 ) 
				printf ("Received Message from %s:%d\n%s\n",(char*)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port,buffer);
			else
				perror("Error Receiving Message:"); // else print error through perror.
			close(newsock);// close the new socket
		}
	
		close(sock); // close the server socket
	}
}