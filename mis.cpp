#include "mis.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;
using std::string;

ofstream outfile;
ofstream errfile;

//maybe make hash defined instead? not sure if that'll work/whats more beneficial
const int MAX_CHARS_PER_INSTRUCTION = 2;
const char* const DELIMITER_SPACE = " ";
const char* const DELIMITER_COMMA = ",";

// declare vectors
vector<string> v_test;
vector< vector<string> > v_line;
string LINE;
std::map<std::string, Variable*> variables;

// declare types and maps
typedef void(Math::*mathFunction)(vector<string>, map<string, Variable*>);

typedef int(Char::*charFunction)(Variable*);
typedef int(String::*strFunction)(Variable*, Variable*);
typedef int(Jump::*jumpFunction)(vector<string>, string, map<string, Variable*>);

std::map<std::string, jumpFunction> jumpInstructions; //may not need
std::map<std::string, mathFunction> mathInstructions;



Mis::Mis() {
	//map that stores all of the default constructors
	variables["VARIABLE"] = new Variable();
	variables["MATH"] = new Math();
	variables["NUMERIC"] = new Numeric();
	variables["CHAR"] = new Char();
	variables["STRING"] = new String();
	variables["REAL"] = new Real();

	mathInstructions["ADD"] = &Math::add;
	mathInstructions["MUL"] = &Math::mul;
	mathInstructions["DIV"] = &Math::div;
	mathInstructions["SUB"] = &Math::sub;
	mathInstructions["ASSIGN"] = &Math::assign;
}


vector<string> Mis::obtain_args(int index, vector<string> v_single_line) {
	// retrieve all args and store in separate params vector
	vector<string> params;
	for(int j = 2; j<v_single_line.size(); j++){
		cout << "push_back " << v_line[index][j] << endl;
		params.push_back(v_line[index][j]);
	}

	return params;
}

void Mis::openFiles(string filename) {
	size_t i = filename.rfind('.', filename.length());

	if (i == string::npos || filename.substr(i, 
		filename.length()-i) != ".mis") {
        cerr << "Incorrect input file. Please provide a .mis file" << endl;
        exit(EXIT_FAILURE);
    }

	string basefile(basename(const_cast<char*> (filename.c_str())));

    char* out = strdup((basefile.substr(0, basefile.length()-3) + 
                        "out").c_str());
    outfile.open(out);
    if (!outfile.is_open()) {
        cerr << "Error opening outfile";
        exit(EXIT_FAILURE);
    }

    char* err = strdup((basefile.substr(0, basefile.length()-3) + 
                        "err").c_str());
    errfile.open(err);
    if (!errfile.is_open()) {
    	cerr << "Error opening errfile";
    	exit(EXIT_FAILURE);
    }
}

void Mis::parse_file(ifstream & input_file) {
	// check if file input is valid
	if (!input_file.good()) {
		cout << "error: file cannot be found" << endl;
		return;
	}

	//read each line of input file
	while(!input_file.eof()) {
		
		vector<string> v_args;	// create vector to hold instruction arguments
		
		getline(input_file, LINE);	// read line into memory
		v_test.push_back(LINE);

		char* instruction_line = strdup(LINE.c_str());

		// grab instruction
		char* token[MAX_CHARS_PER_INSTRUCTION] = {};
		token[0] = std::strtok(instruction_line, DELIMITER_SPACE);
		v_args.push_back(token[0]);

		// find first instance of ' ' and create substring of arguments
		std::size_t pos = LINE.find(DELIMITER_SPACE);
		string a = LINE.substr(pos+1);
		token[1] = std::strtok(strdup(a.c_str()), DELIMITER_COMMA);
		
		char * p = std::strtok(strdup(a.c_str()),DELIMITER_COMMA);
  		while (p!=0)
  		{
    		v_args.push_back(p);
    		p = std::strtok(NULL,DELIMITER_COMMA);
 		}

		v_line.push_back(v_args);	// add arguments to v_line 
	}

	// cout v_args
	cout << "vector size " << v_line.size() << endl;
	for (int i = 0; i < v_line.size(); i++) {
		cout << i << endl;
		for (int j=0; j < v_line[i].size(); j++) {
			cout << "args: " << v_line[i][j] << endl;
		}
	}
}

void Mis::instruction(string instruction_type) {
	cout << "hit" << endl;
	// variables.find(instruction_type);
	Variable * obj = variables[instruction_type]; 
}

Mis::~Mis() {}

int main(int argc, char *argv[]) {

//------------Working example of jump functionality-----------------
	Jump a;
	std::vector<string> v;
	// v.push_back("Label");
	v.push_back("b");
	v.push_back("c");
	string type = "JMPLT";
	std::map<string, Variable*> map;
	Math *b = new Math("testing", 45.0);

	Math *c = new Math("test", 12.0);
	map["b"] = b;
	map["c"] = c;
	Math d;
	d.add(v, map);
	d.out();

	a.storeLabel("Label", 6);
	// cout << a.compare(v, type, map); //compare is only interaction needed with JMP object
//------------------------------------------------------------------


	Mis mis;
	ifstream input_file (argv[1]);
	mis.parse_file(input_file);

	for (int i=0; i<v_line.size(); i++) {
		if(variables[v_line[i][1]]->getType() == "Char") //DOUBLE CHECK IF THIS IS THE CORRECT LINE TO LOOK AT
		{
			//then use Char function map
		}

		if(variables[v_line[i][1]]->getType() == "Real" || variables[v_line[i][1]]->getType() == "Numeric")
		{
			vector<string> params = mis.obtain_args(i, v_line[i]);

			(dynamic_cast<Math*>(variables[v_line[i][1]])->*mathInstructions[v_line[i][0]])(params, variables);
		}

		if(variables[v_line[i][1]]->getType() == "String")
		{
			//then use String function map
		}


		if (v_line[i][0] == "VAR") {
			mis.instruction(v_line[i][2]);

		} else if (v_line[i][0] == "ADD") {
			
		} else if (v_line[i][0] == "SUB") {

		} else if (v_line[i][0] == "MUL") {

		} else if (v_line[i][0] == "DIV") {

		} else if (v_line[i][0] == "ASSIGN") { //can be replaced by function pointers?
			// this->setValue(value);
		} else if (v_line[i][0] == "OUT") { //<--- should work for most all

		} else if (v_line[i][0] == "SET_STR_CHAR") {

		} else if (v_line[i][0] == "GET_STR_CHAR") {

		} else if (v_line[i][0] == "LABEL") {
			// Junmp a;
			// a.storeLabel();
		} else if (v_line[i][0].find("JMP") != string::npos) {

		}
	}
	
	return 0;
}