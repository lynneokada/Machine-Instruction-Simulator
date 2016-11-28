#include "ClientThread.h"

ClientThread::ClientThread(vector<string>* instructions) //ClientThread Constructor
{
	mis.parseLines(instructions);
};

ClientThread::~ClientThread() {};


void ClientThread::run()
{
	cout << "variables initialized\n";
	mis.run(outBuffer, errorBuffer);
}


void ClientThread::parseLines(std::vector<string>* lines)
{
	mis.parseLines(lines);
}

void ClientThread::setFlag(bool flag)
{
	mis.setFlag(flag);
}

string ClientThread::getName() {
	return name;
}

vector<string> ClientThread::getOutput() {
	return *outBuffer;
}

vector<string> ClientThread::getError() {
	return *errorBuffer;
}