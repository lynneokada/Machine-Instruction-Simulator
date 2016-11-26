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

void Thread::setLines(vector<vector<string>> subset)
{
	mis.setLines(subset);
}

void Thread::run(vector<string>* out, vector<string>* err)
{
	mis.run(vector<string>* out, vector<string>* err);
}

void Thread::setFlag(bool flag)
{
	mis.setFlag(flag);
}

int main()
{
	return 0;
}