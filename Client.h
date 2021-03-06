#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <libgen.h>
#include "TCPSocket.h"

class Client
{
	private:

	public:
		Client();
		~Client();
		ifstream openFiles(string filename);
		vector<string> parse_file(ifstream & input_file);
		void transmit(vector<string> in, TCPSocket sock);
		void receive(std::vector<string> buffer, TCPSocket sock);
};

#endif