#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;

int main() {
	std::string STRING;
	ifstream input_file;
	input_file.open("test.txt");
	if (!input_file.good()) {
		return 1;
		cout << "error: file cannot be found" << endl;
	}

	//create array to store each line
	char buf[MAX_CHARS_PER_LINE];
	std::vector<std::string> v;

	//read each line of input file
	while(!input_file.eof()) {
		// read line into memory
		getline(input_file, STRING);
		v.push_back(STRING);
	}

	cout << "array size " << sizeof(v) << endl;
	for (int i = 0; i < sizeof(v); i++) {
			cout << v[i] << endl;	
	}
}