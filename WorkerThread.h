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

		//pass subset of v_line into function and do ::run as is own thread
		//need to figure out how to call threads using run and still writing to same output file
		//	-doesnt need to write to output file, just a buffer
		//	-buffer is globally accessed by only each CLIENT, not overall
		//	-need to make buffer to store to
		//spawns thread after reading input

		//requires implementing mutexes on all variables
		//	-is recursive locking allowed?
		//	-do threads HAVE to be unlocked ever or is it valid for it to just lock?
		void lock();


		//need to be careful about unlocking a previously unlocked variable
		//	-possibly use an atomic boolean to represent locked/unlocked state
		//		-needs to utilize double check locking
		void unlock();

		void loadVariables(Mis *parent);
		void setLines(vector<vector<string>> subset);
		void run(vector<string>* out, vector<string>* err);
		void setFlag(bool flag);
		void getName();
		void setId(int id);
};

#endif