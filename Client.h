#include <vector>
#include <iostream>
#include <fstream>
#include "TCPSocket.h"
#include "includes.h"
#include "common.h"

class Client
{
	private:
		std::vector<string> inBuffer;
		std::vector<string> outBuffer;
		std::vector<string> errorBuffer;
		ofstream outfile;
		ofstream errfile;
		struct packet;

	public:
		Client();
		~Client();
		vector<string> parse_file(ifstream & input_file);		
		ifstream openFiles(string filename);
		void transmit();
		void receive();
};