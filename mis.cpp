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

Mis::Mis() {

}

void Mis::instruction(string instruction_type) {

}

int main(int argc, char *argv[]) {
	string LINE;
	ifstream input_file (argv[1]);
	static int line_number = 0;
	
	if (!input_file.good()) {
		cout << "error: file cannot be found" << endl;
		return 1;
	}

	//create vector to store each line
	vector<string> v_test;
	
	vector< vector<string> > v_line;

	//map that stores all of the default constructors
	std::map<std::string, Variable*> variables;
	variables["VARIABLE"] = new Variable();
	variables["MATH"] = new Math();
	variables["NUMERIC"] = new Numeric();
	variables["CHAR"] = new Char();
	variables["STRING"] = new String();
	variables["REAL"] = new Real();


	//read each line of input file
	while(!input_file.eof()) {
		line_number++;
		vector<string> v_args;
		// read line into memory
		getline(input_file, LINE);
		v_test.push_back(LINE);

		char* instruction_line = strdup(LINE.c_str());
		cout << instruction_line << endl;

		// grab instruction
		char* token[MAX_CHARS_PER_INSTRUCTION] = {};
		token[0] = std::strtok(instruction_line, DELIMITER_SPACE);
		v_args.push_back(token[0]);
		cout << token[0] << endl;

		// find first instance of ' ' and create substring of arguments
		std::size_t pos = LINE.find(DELIMITER_SPACE);
		string a = LINE.substr(pos+1);
		cout << "substring: " << a << endl;
		token[1] = std::strtok(strdup(a.c_str()), DELIMITER_COMMA);
		
		char * p = std::strtok(strdup(a.c_str()),DELIMITER_COMMA);
  		while (p!=0)
  		{
    		std::cout << "p " << p << '\n';
    		v_args.push_back(p);
    		p = std::strtok(NULL,DELIMITER_COMMA);
 		}

		v_line.push_back(v_args);	// add arguments to v_line 
	}

	cout << "vector size " << v_line.size() << endl;
	for (int i = 0; i < v_line.size(); i++) {
		cout << i << endl;
		for (int j=0; j < v_line[i].size(); j++) {
			cout << "arguments: " << v_line[i][j] << endl;
		}
	}
}