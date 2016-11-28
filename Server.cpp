#include "Server.h"

#define MAX_QUEUE 15

Server::Server(int port, int maxQueue):serve(NULL, port, maxQueue) {

} //I think backlog represents max # of waiting clients?
// {
// 	serve = TCPServerSocket(NULL, port, maxQueue); //NULL represents listening from all addresses
// };

Server::~Server() {}

void Server::transmit(vector<string> in, TCPSocket* sock)
{
	int status;
	for (int i = 0; i < in.size(); ++i)
	{
		string testing = in[i];
		int size = testing.length();
		// cout << testing.length() << e=ndl;
		char packet[size+1];

		packet[0]=testing.length();
		// memcpy(packet, &size, sizeof(size));

		for (int i = 0; i < size+1; ++i)
		{
			packet[i+1] = testing[i];
			// cout << "Value of packet" << packet[i] << endl;
		}

		cout << "Testing packet: " << testing << endl;
		cout << "Size of packet: " << sizeof(packet) << endl;
		status = sock->writeToSocket (packet, sizeof(packet));
		// cout << " - Packet sent: " << status << endl;
		if (status == -1)
		{
			exit(1);
		}
	}
}

void Server::receive(std::vector<string>* buffer, TCPSocket* sock)
{
	char length[1];
	int bytesRead;
	string info;

	cout << "test\n";

	while((bytesRead != -1) && (strcmp(info.c_str(), "STOP") != 0)) {
		info = "";
		bytesRead = sock->readFromSocket(length, 1);
		if(bytesRead == -1)
		{
			perror("Error reading from socket");
			exit(1);
		}
		else
		{
			while(bytesRead < 1) //make sure we read the whole int - need to figure out how to not overwrite length every time
			{
				cout << "Shouldnt be here" << endl;
				bytesRead = bytesRead - sock->readFromSocket(length, bytesRead); //need to change this so length isnt overwritten every time
			}
		}

		// cout << "buffer size: " << buffer.size() << endl;
		//getting length of message
		unsigned int intLength = length[0];
		// printf("My number is: %d", atoi(length));
		// cout << "length: " << intLength << endl;

		char buff[intLength];
		bytesRead = sock->readFromSocket(buff, intLength);
		// cout << "Reading" << endl;
		for (int i = 0; i < intLength; ++i)
		{
			printf("%c\n", buff[i]);
		}
		if(bytesRead == -1)
		{
			perror("Error reading from socket");
			exit(1);
		}

		while (bytesRead != intLength)
		{
			bytesRead = sock->readFromSocket(buff, intLength-bytesRead);
		}

		//grabbing from sizeof(int) offset to end of message
		for (int i = 0; i < intLength; ++i)
		{
			info += buff[i];
		}

		buffer->push_back(info);
		cout << "info " << info << " " << bytesRead << endl;
		//wipe buffers at end?
	}

	cout << "Finished run" << endl;
}

void Server::spawnClientWorker(TCPSocket *socket) //DOES THIS WORK CONCURRENTLY?
{
	cout << "After" << endl;
	// Mis mis;
	// std::vector<string> out;
	// std::vector<string> error;
	vector<string>* lines = new std::vector<string> ();

	//receive all incoming transmissions
	receive(lines, socket);
	// cout << "test2\n";
	// cout << "Lines is being passed by VALUE" << lines->size() << endl;

	// for (int i = 0; i < lines->size(); ++i)
	// {
	// 	cout << "Work prease" << (*lines)[i] << endl;
	// }

	//initialize a clientThread after socket found
	ClientThread clientThread(lines);

	cout << "running" << endl;
	//start execution using mis object
	clientThread.run();

	cout << "getting output" << endl;
	//parse output from mis object
	//going to be a "setter" essentially
	vector<string> output = clientThread.getOutput();
	for (int i = 0; i < output.size(); ++i)
	{
		cout << output[i] << endl;
	}

	cout << "transmitting" << endl;
	//send it back to client using socket
	// transmit(output, socket);
}

std::thread Server::spawnClientWorkerThread(TCPSocket *socket)
{
	cout << "Before" << endl;
 	return std::thread([=] {spawnClientWorker(socket); });
}

int main(int argc, char const *argv[])
{
	if (argc != 2) { // Check on the number of arguments and exit if incorrect
		printf ("Usage: ./server <server-port>\n");
		exit(1);
	}

	const char* value = argv[1]; // convert const char* argvalue to int port address
	stringstream strValue;
	strValue << value;
	unsigned int port;
	strValue >> port;

	Server server(port, MAX_QUEUE);
	bool status = server.serve.initializeSocket();

	if(status == false) {
		perror("Error initializing socket");
		exit(1);
	}

	TCPSocket *sock;

	while(1)
	{
		sock = server.serve.getConnection(100,0, 65536, 65536); //timeout is 100 seconds and 0 milliseconds
		if(sock == NULL)
		{
			perror("Error creating new socket");
			exit(1);
		}

		//start client worker and let it handle parsing, spawn a new clientWorkerThread
		// std::thread m1(mis1.run(), &mis1);
		std::thread t = server.spawnClientWorkerThread(sock);
		t.join();
		// server.clients.push_back(t);
	}
	return 0;
}

//Server example
	// int sock; // Socket Handler
	// struct sockaddr_in serverAddr; // Server Address Structure
	// struct sockaddr_in clientAddr; // Client Address Structure
	// socklen_t sin_size = sizeof(struct sockaddr_in); // Address Structur Size
	
	// // Try to allocate a socket and if fail we terminate with an error.
	// if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) terminate_with_error("Error Creating Socket",sock);

	// int sock_opt = 1; // An integer to be used with sock opt
	// // Setting socket reuse option so after the program terminates we can acquire the socket again on the same port without going into a grace period.
	// setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void *)&sock_opt,sizeof (sock_opt));
	// serverAddr.sin_family = AF_INET; // Set the communication family
	// serverAddr.sin_port = htons(9999); // Set the port number
	// serverAddr.sin_addr.s_addr = INADDR_ANY;// Set the socket to operate on all IP address and network interfaces available
	// bzero(&(serverAddr.sin_zero), 8); // We zero out the rest of the sockaddr_in to make it identical to sockaddr
	
	// // Try to bind on the socket port, and if it fails we exit. Will fail if the socket is already acquired by another process
	// // or the program runs with less priviledges that cannot allow binding
	// if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1)
	// 	terminate_with_error("Error Binding",sock);

	// while(1)
	// {
	// 	// Create the socket listen queue with size 10.
	// 	if (listen(sock, 10) == -1) 
	// 		terminate_with_error("Error Listening: ",sock);

	// 	int newsock = accept(sock, (struct sockaddr *)&clientAddr,&sin_size); // Wait for connection
	
	// 	if ( newsock < 1 )
	// 		terminate_with_error("Error Accepting Socket",0); // if failed exit.
	// 	else {
	// 		int maxBytes = 1024; // size of buffer
	// 		char buffer[maxBytes]; // alocat buffer of 1 K
	// 		memset(buffer,0,maxBytes); // initialize it.
	// 		int bytes_read = recv (newsock,buffer,maxBytes,0); // read data from the socket
	
	// 		// if returned number of bytes is bigger that zero then print information about client and the message
	// 		if ( bytes_read > 0 ) 
	// 			printf ("Received Message from %s:%d\n%s\n",(char*)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port,buffer);
	// 		else
	// 			perror("Error Receiving Message:"); // else print error through perror.
	// 		close(newsock);// close the new socket
	// 	}
	
	// 	close(sock); // close the server socket