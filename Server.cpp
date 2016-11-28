#include "Server.h"

#define MAX_QUEUE 15

Server::Server(int maxQueue):serve(NULL, 9999, maxQueue) {}
Server::~Server() {}

void Server::transmit(vector<string> in, TCPSocket* sock)
{
	int status;
	for (int i = 0; i < in.size(); ++i)
	{
		string testing = in[i];
		int size = testing.length();
		char packet[size+1];

		packet[0]=testing.length();

		for (int i = 0; i < size+1; ++i)
		{
			packet[i+1] = testing[i];
		}

		status = sock->writeToSocket (packet, sizeof(packet));

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

	cout << " " << endl;

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
				bytesRead = bytesRead - sock->readFromSocket(length, bytesRead); //need to change this so length isnt overwritten every time
			}
		}

		//getting length of message
		unsigned int intLength = length[0];

		char buff[intLength];
		bytesRead = sock->readFromSocket(buff, intLength);

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
	}
}

void Server::spawnClientWorker(TCPSocket *socket) //DOES THIS WORK CONCURRENTLY?
{
	vector<string>* lines = new std::vector<string> ();
	vector<string> output;
	vector<string> error;

	//receive all incoming transmissions
	receive(lines, socket);

	//initialize a clientThread after socket found
	ClientThread clientThread(lines);

	//start execution using mis object
	try
	{
		clientThread.run();
	}

	catch(...)
	{
		cout << "Error occurred running ClientThread" << endl;
	}

	//parse output from mis object
	output = clientThread.getOutput();

	//send it back to client using socket
	transmit(output, socket);

	//parse output from mis object
	error = clientThread.getError();

	//send it back to client using socket
	transmit(output, socket);
}

std::thread Server::spawnClientWorkerThread(TCPSocket *socket)
{
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
		// t.join();
		server.clients.push_back(server.spawnClientWorkerThread(sock));
	}
	return 0;
}