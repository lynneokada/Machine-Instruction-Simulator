#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char *argv[]) {
	std::string STRING;
	ifstream input_file (argv[1]);
	
	if (!input_file.good()) {
		cout << "error: file cannot be found" << endl;
		return 1;
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