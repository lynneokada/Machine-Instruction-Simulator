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

		void unlock();
		void run();
		void setFlag(bool flag);
		string getName();
		void parseLines(std::vector<string>* lines);
		vector<string> getOutput();
		vector<string> getError();
};

#endif