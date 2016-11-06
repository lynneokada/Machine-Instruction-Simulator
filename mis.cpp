#include "mis.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;
using std::string;

const int MAX_CHARS_PER_INSTRUCTION = 2;
const char* const DELIMITER_SPACE = " ";
const char* const DELIMITER_COMMA = ",";

// declare vectors
vector<string> v_test;
vector< vector<string> > v_line;
string LINE;
std::map<std::string, Variable*> variables;

Mis::Mis() {
	//map that stores all of the default constructors
	variables["VARIABLE"] = new Variable();
	variables["MATH"] = new Math();
	variables["NUMERIC"] = new Numeric();
	variables["CHAR"] = new Char();
	variables["STRING"] = new String();
	variables["REAL"] = new Real();	
}

void Mis::parse_file(ifstream & input_file) {
	// check if file input is valid
	if (!input_file.good()) {
		cout << "error: file cannot be found" << endl;
		return;
	}

	//read each line of input file
	while(!input_file.eof()) {
		
		vector<string> v_args;	// create vector to hold instruction arguments
		
		getline(input_file, LINE);	// read line into memory
		v_test.push_back(LINE);

		char* instruction_line = strdup(LINE.c_str());

		// grab instruction
		char* token[MAX_CHARS_PER_INSTRUCTION] = {};
		token[0] = std::strtok(instruction_line, DELIMITER_SPACE);
		v_args.push_back(token[0]);

		// find first instance of ' ' and create substring of arguments
		std::size_t pos = LINE.find(DELIMITER_SPACE);
		string a = LINE.substr(pos+1);
		token[1] = std::strtok(strdup(a.c_str()), DELIMITER_COMMA);
		
		char * p = std::strtok(strdup(a.c_str()),DELIMITER_COMMA);
  		while (p!=0)
  		{
    		v_args.push_back(p);
    		p = std::strtok(NULL,DELIMITER_COMMA);
 		}

		v_line.push_back(v_args);	// add arguments to v_line 
	}

	// cout v_args
	cout << "vector size " << v_line.size() << endl;
	for (int i = 0; i < v_line.size(); i++) {
		cout << i << endl;
		for (int j=0; j < v_line[i].size(); j++) {
			cout << "args: " << v_line[i][j] << endl;
		}
	}
}

void Mis::instruction(string instruction_type) {
	cout << "hit" << endl;
	variables.find(instruction_type);
}

Mis::~Mis() {

}

int main(int argc, char *argv[]) {
	
	Mis mis;
	ifstream input_file (argv[1]);
	mis.parse_file(input_file);

	for (int i=0; i<v_line.size(); i++) {
		if (v_line[i][0] == "VAR") {
			mis.instruction(v_line[i][2]);
		} else if (v_line[i][0] == "ADD") {

		} else if (v_line[i][0] == "SUB") {

		} else if (v_line[i][0] == "MUL") {

		} else if (v_line[i][0] == "DIV") {

		} else if (v_line[i][0] == "ASSIGN") {

		} else if (v_line[i][0] == "OUT") {

		} else if (v_line[i][0] == "SET_STR_CHAR") {

		} else if (v_line[i][0] == "GET_STR_CHAR") {

		} else if (v_line[i][0] == "LABEL") {

		} else if (v_line[i][0] == "JMP") {

		}
	}
	
	return 1;
}