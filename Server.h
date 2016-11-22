#include <fstream>
#include <thread>
#include "TCPSocket.h"
#include "TCPSocketServer.h"
#include "mis.h"

class Server
{
	private:
		std::vector<string> inBuffer;
		std::vector<string> outBuffer;
		std::vector<string> errorBuffer;
		std::vector<thread> clients; //going to be MIS object threads i think

	public:
		Server();
		~Server();
		void transmit(vector<string> in, TCPSocket sock);
		void receive(std::vector<string> buffer, TCPSocket sock);		
		vector<vector<string>> parse(vector<string> buffer);
		void spawnClientThread(TCPSocket* socket);
};