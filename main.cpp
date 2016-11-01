#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <array>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;
using std::string;

const int MAX_CHARS_PER_INSTRUCTION = 100;
const char* const DELIMITER_SPACE = " ";
const char* const DELIMITER_COMMA = ",";


int main(int argc, char *argv[]) {
	string STRING;
	ifstream input_file (argv[1]);
	
	if (!input_file.good()) {
		cout << "error: file cannot be found" << endl;
		return 1;
	}

	//create vector to store each line
	vector<string> v;

	//read each line of input file
	while(!input_file.eof()) {
		// read line into memory
		getline(input_file, STRING);
		v.push_back(STRING);

		char* instruction = strdup(STRING.c_str());

		// grab instruction
		char* token[MAX_CHARS_PER_INSTRUCTION] = {};
		token[0] = std::strtok(instruction, DELIMITER_SPACE);
		token[1] = std::strtok(NULL, DELIMITER_SPACE);

		// const char* pos = strchr(strdup(STRING.c_str()),DELIMITER_SPACE);
		cout << instruction << endl;
		
		std::size_t pos = STRING.find(DELIMITER_SPACE);
		cout << pos << endl;
		string a = STRING.substr(pos);
		cout << "substring: " << a << endl;

		token[2] = std::strtok(strdup(a.c_str()), DELIMITER_COMMA);
		cout << "comma: " << token[2] << endl;
	}

	cout << "vector size " << v.size() << endl;
	for (int i = 0; i < v.size()-1; i++) {
			cout << i <<" " << v[i] << endl;	
	}
}