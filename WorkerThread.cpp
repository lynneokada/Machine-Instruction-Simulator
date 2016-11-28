#include "WorkerThread.h"

WorkerThread::WorkerThread(vector<vector<string>> instructions, Mis* parent) //WorkerThread Constructor
{
	Mis mis;
	mis.setLines(lines);
	mis.loadVariables(parent);
};

void WorkerThread::loadVariables(Mis *parent)
{
	mis->loadVariables(parent);

}

WorkerThread::~WorkerThread() {};

void WorkerThread::setLines(vector<vector<string>> subset)
{
	mis->setLines(subset);
}

void WorkerThread::run(vector<string>* out, vector<string>* err)
{
	mis->run(out, err);
}

void WorkerThread::setFlag(bool flag)
{
	mis->setFlag(flag);
}

void WorkerThread::setId(int id) {
	mis->setId(id);
}