#include "Mis.h"

int main(int argc, char *argv[]) 
{
	// create Mis and read file
	Mis mis;

	if (argc != 2) {
		cerr << "Usage:  ./main testFile.mis" << endl;
		exit(EXIT_FAILURE);
	}

	ifstream input_file;
	input_file = mis.openFiles(argv[1]);
	mis.parse_file(input_file);

	// begin reading
	mis.run();

	return 0;
}