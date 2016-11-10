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
public:
	Mis();	// constructor
	Jump jmp;
	void parse_file(ifstream & input_file);
	void create_variable(vector<string> lines);
	vector<string> obtain_args(int index, vector<string> v_single_line);
	ifstream openFiles(string filename);
	void sleep(Math* var);
	void run();
	~Mis();	// destructor
};