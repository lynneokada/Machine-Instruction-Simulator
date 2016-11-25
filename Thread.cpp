#include "Thread.h"

Thread::Thread(std::vector<vector<string>> instructions, Mis* parent)
{
	Mis mis;
	mis.parseLines(instructions);
	mis.loadVariables(&parent); //mis.mathVars = &parent.mathVars
};

void Thread::loadVariables(Mis *parent)
{
	
}

Thread::~Thread() {};

void makeThread();
{}

int main()
{
	return 0;
}