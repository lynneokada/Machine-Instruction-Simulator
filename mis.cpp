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

Mis::instruction(string ) {

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
	vector<vector<string>> v_line;
	vector<string> v_args;

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
		// read line into memory
		getline(input_file, LINE);
		v_test.push_back(LINE);

		char* instruction_line = strdup(LINE.c_str());
		cout << instruction_line << endl;

		// grab instruction
		char* token[MAX_CHARS_PER_INSTRUCTION] = {};
		token[0] = std::strtok(instruction_line, DELIMITER_SPACE);
		cout << token[0] << endl;

		token[1] = std::strtok(NULL, DELIMITER_COMMA);
		cout << token[1] << endl;

		// // const char* pos = strchr(strdup(LINE.c_str()),DELIMITER_SPACE);
		// cout << "instruction type: " << instruction_type << endl;
		
		// std::size_t pos = LINE.find(DELIMITER_SPACE);
		// // cout << "pos: " << pos << endl;
		// string a = LINE.substr(pos);
		// cout << "substring: " << a << endl;

		// token[2] = std::strtok(strdup(a.c_str()), DELIMITER_COMMA);
		// cout << "comma: " << token[2] << endl;
	}

	// cout << "vector size " << v_line.size() << endl;
	// for (int i = 0; i < v_line.size(); i++) {
	// 		cout << i <<" " << v_line[i] << endl;	
	// }
}