#include <iostream>
#include <string>
#include <algorithm>

int main (int argc, char** argv) {

	if (argc == 1) {
		printf("Please provide an input file\n");
		exit(0);
	}

	
	for (int i = 1; i < argc; i++) {
		std::ifstream inFile("file"); 
  		std::count(std::istreambuf_iterator<char>(inFile), 
            	   std::istreambuf_iterator<char>(), '\n');
		for (std::string line; std::getline(input, line)) {

		}
	}
}