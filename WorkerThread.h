#ifndef __WORKERTHREAD_H
#define __WORKERTHREAD_H

#include <atomic>
#include <thread>
#include <string>
#include "mis.h"

class Mis;

class WorkerThread
{
	private:
		Mis *mis;
		vector<vector<string>> lines;
		string name;
		std::vector<string>* out;
		std::vector<string>* err;
		
	public:
		WorkerThread(vector<vector<string>> instructions, Mis* parent);
		~WorkerThread();
		
		void loadVariables(Mis *parent);
		void setLines(vector<vector<string>> subset);
		void run(vector<string>* out, vector<string>* err);
		void setFlag(bool flag);
		void getName();
		void setId(int id);
};

#endif