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

class Mis {
public:
	Mis();	// constructor
	void parse_file(ifstream & input_file);
	void find_instruction(string instruction_type, string name, string value);
	void create_variable(string var_type, string name, string value);
	vector<Math*> obtain_args(int index, vector<string> v_single_line);
	ifstream openFiles(string filename);
	~Mis();	// destructor
};