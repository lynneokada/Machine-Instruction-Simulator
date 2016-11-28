#include "ClientThread.h"

ClientThread::ClientThread(vector<string> instructions) //ClientThread Constructor
{
	Mis mis;
	mis.parseLines(instructions);
};

ClientThread::~ClientThread() {};


void ClientThread::run()
{
	mis->initializeVariables(threadMathVars,threadStringVars,threadCharVars);
	mis->run(outBuffer, errorBuffer);

}

void ClientThread::parseLines(std::vector<string> lines)
{
	mis->parseLines(lines);
}

void ClientThread::setFlag(bool flag)
{
	mis->setFlag(flag);
}

string ClientThread::getName() {
	return name;
}

vector<string> ClientThread::getOutput() {
	return *outBuffer;
}

// int main()
// {
// 	return 0;
// }