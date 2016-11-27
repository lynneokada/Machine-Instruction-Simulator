#include <atomic>
#include <thread>
#include <string>
#include "mis.h"

#ifndef __THREAD_H
#define __THREAD_H


class Mis;

class Thread
{
	private:
		vector<vector<string>> lines;
		string name;
		
	public:
		Mis *mis;
		Thread(std::vector<vector<string>> instructions, Mis* parent);
		~Thread();

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