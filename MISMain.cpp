#include "Mis.h"
#include <thread>
#include <atomic> //may not need - need to confirm

int main(int argc, char *argv[]) 
{
	// create Mis and read file
	Mis mis1, mis2;

	//disabled for testing purposes
	// if (argc != 2) {
	// 	cerr << "Usage:  ./main testFile.mis" << endl;
	// 	exit(EXIT_FAILURE);
	// }

	//Threading example using multiple input files - need to replicate on cliet side parsing/multi client threading on server
	ifstream input_file1, input_file2;
	input_file1 = mis1.openFiles(argv[1]);
	input_file2 = mis2.openFiles(argv[2]);

	mis1.parse_file(input_file1);
	mis2.parse_file(input_file2);

	mis1.name = "MIS1";
	mis2.name = "MIS2";

	std::thread m1(mis1.run, &mis1);
	std::thread m2(mis2.run, &mis2);

	m1.join();
 	m2.join();

	return 0;
}