#ifndef __CLIENTTHREAD_H
#define __CLIENTTHREAD_H

#include <atomic>
#include <thread>
#include <string>
#include "mis.h"

class ClientThread
{
	private:
		Mis mis;
		vector<vector<string>> lines;
		string name;
		vector<string>* inBuffer = new vector<string>();
		vector<string>* outBuffer = new vector<string>();
		vector<string>* errorBuffer = new vector<string>();
		//maps to variables per client
		map<string, Math*>* threadMathVars; 
		map<string, String*>* threadStringVars;
		map<string, Char*>* threadCharVars;
		
	public:
		ClientThread(vector<string>* instructions);
		~ClientThread();

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
		void run();
		void setFlag(bool flag);
		string getName();
		void parseLines(std::vector<string>* lines);
		vector<string> getOutput();
};

#endif