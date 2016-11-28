#ifndef __MIS_H
#define __MIS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <array>
#include <map>
#include <libgen.h>
#include <thread>
#include "Numeric.h"
#include "Char.h"
#include "String.h"
#include "Real.h"
#include "Jump.h"
// #include "ClientThread.h"
#include "WorkerThread.h"
#include <regex>
#include <mutex>

class Mis {
private:
	ofstream outfile;
	ofstream errfile;
	vector<string> v_test;
	vector<vector<string>> v_line;
	string LINE;

	std::map<string, Math*> *mathVars;
	std::map<string, String*> *stringVars;
	std::map<string, Char*> *charVars;

	bool isWorker = false;
	vector<std::thread> workers;
	std::mutex mtx;
	int threadCount = 1;
	int id;

public:
	Mis();	// constructor
	~Mis();	// destructor
	vector<string>* outBuffer;
	vector<string>* errBuffer;
	Jump jmp;
	string name; //ONLY FOR DEBUGGING PURPOSES SHOULD BE REMOVED FOR ACTUAL SUBMISSION
	void parse_file(ifstream & input_file);
	void parseLines(vector<string>* lines);
	void create_variable(vector<string> lines);
	vector<string> obtain_args(int index, vector<string> v_single_line);
	ifstream openFiles(string filename);
	void sleep(Math* var);
	void run(vector<string>* out, vector<string>* errfile);
	void barrier(); //need to implement
	void spawnWorker(vector<vector<string>> subset); //need to implement
	void setFlag(bool flag);
	std::thread spawnWorkerThread(vector<vector<string>> subset);
	void setLines(vector<vector<string>> subset);
	void bufferWrite(vector<string> *buffer, string message);
	void joinThreads();
	void lock(string variable);
	void unlock(string variable);
	void loadVariables(Mis* mis);
	void initializeVariables(std::map<string, Math*>* threadMathVars,
		std::map<string, String*>* threadStringVars,
		std::map<string, Char*>* threadCharVars);
	void setId(int num);
};

#endif