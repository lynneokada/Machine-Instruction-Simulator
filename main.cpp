#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	std::string STRING;
	ifstream input_file;
	input_file.open("test.txt");
	if (!input_file.good()) {
		return 1;
		cout << "error: file cannot be found" << endl;
	}

	//create vector to store each line
	std::vector<std::string> v;

	//read each line of input file
	while(!input_file.eof()) {
		// read line into memory
		getline(input_file, STRING);
		cout << "string: " << STRING << endl;
		v.push_back(STRING);
	}

	cout << "vector size " << v.size() << endl;
	for (int i = 0; i < v.size(); i++) {
			cout << i <<" " << v[i] << endl;	
	}
}