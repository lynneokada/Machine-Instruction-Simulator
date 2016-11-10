#include "Mis.h"

int main(int argc, char *argv[]) 
{
	// create Mis and read file
	Mis mis;

	if (argc == 1) {
		cerr << "Please provide an input file" << endl;
		exit(EXIT_FAILURE);
	}

	ifstream input_file;
	input_file = mis.openFiles(argv[1]);
	cout << "Test" << endl;
	mis.parse_file(input_file);

	cout << "test2" << endl;
	// begin reading
	mis.run();
	// Numeric *a = new Numeric("test", 12.2);
	// std::map<string, Math*> map;
	// map["test"] = a;
	// dynamic_cast<Math*>(map["test"])->setValue(15);
	// map["test"]->out();
	// a->out();
	return 0;
}