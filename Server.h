#include <fstream>
#include "TCPSocket.h"
#include "includes.h"
#include "common.h"

class Server
{
	private:
		std::vector<string> inBuffer;
		std::vector<string> outBuffer;
		std::vector<string> errorBuffer;

	public:
		Server();
		~Server();		
};