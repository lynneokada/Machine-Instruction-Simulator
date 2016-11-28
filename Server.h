#ifndef __SOCKET_H_
#define __SOCKET_H_

#include <fstream>
#include <thread>
#include "TCPSocket.h"
#include "TCPServerSocket.h"
#include "mis.h"
#include "ClientThread.h"

class Server
{
	private:
		std::vector<string> inBuffer;
		std::vector<string> outBuffer;
		std::vector<string> errorBuffer;
	public:
		std::vector<thread> clients; //going to be MIS object threads i think
		TCPServerSocket serve;
		Server(int port, int maxQueue);
		~Server();
		void transmit(vector<string> in, TCPSocket* sock);
		void receive(std::vector<string>* buffer, TCPSocket* sock);		
		vector< vector<string> > parse(vector<string> buffer);
		void spawnClientWorker(TCPSocket *socket);
		std::thread spawnClientWorkerThread(TCPSocket *socket);
};

#endif