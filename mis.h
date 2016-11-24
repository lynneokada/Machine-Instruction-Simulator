#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <array>
#include <map>
#include <libgen.h>
#include "Numeric.h"
#include "Char.h"
#include "String.h"
#include "Real.h"
#include "Jump.h"
#include <regex>

class Mis {
private:
	ofstream outfile;
	ofstream errfile;
	vector<string> v_test;
	vector< vector<string> > v_line;
	string LINE;
	vector<string> outBuffer;
	vector<string> errBuffer;

	std::map<string, Math*> mathVars;
	std::map<string, String*> stringVars;
	std::map<string, Char*> charVars;
public:
	Mis();	// constructor
	~Mis();	// destructor
	Jump jmp;
	string name; //ONLY FOR DEBUGGING PURPOSES SHOULD BE REMOVED FOR ACTUAL SUBMISSION
	void parse_file(ifstream & input_file);
	void parseLines(vector<string> lines);
	void create_variable(vector<string> lines);
	vector<string> obtain_args(int index, vector<string> v_single_line);
	ifstream openFiles(string filename);
	void sleep(Math* var);
	void run();
	void barrier(); //need to implement
	void spawnWorker(vector<string> lines); //need to implement
	vector<string> output();
	vector<string> errors();
};