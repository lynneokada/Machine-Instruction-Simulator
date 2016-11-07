#include "mis.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;
using std::string;


//maybe make hash defined instead? not sure if that'll work/whats more beneficial
const int MAX_CHARS_PER_INSTRUCTION = 2;
const char* const DELIMITER_SPACE = " ";
const char* const DELIMITER_COMMA = ",";

// declare vectors
vector<string> v_test;
vector< vector<string> > v_line;
string LINE;
std::map<string, Variable*> variables;

std::map<string, Math*> instruction_math_map;
std::map<string, String*> instruction_string_map;
std::map<string, Char*> instruction_char_map;

// declare types and maps
typedef int(Numeric::*numFunction)(Variable*);
typedef int(Real::*realFunction)(Variable*, Variable*);
typedef int(Char::*charFunction)(Variable*);
typedef int(String::*strFunction)(Variable*, Variable*);
typedef int(Jump::*jumpFunction)(vector<string>, string, map<string, Variable*>);

std::map<std::string, jumpFunction> jumpInstructions;

Mis::Mis() {
	//map that stores all of the default constructors
	variables["VARIABLE"] = new Variable();
	variables["MATH"] = new Math();
	variables["NUMERIC"] = new Numeric();
	variables["CHAR"] = new Char();
	variables["STRING"] = new String();
	variables["REAL"] = new Real();

	//map that stores all of instructions
	// typedef void (Math::*pSub)(Math, Math);
	// pSub = &Math::sub;
	// instruction_math_map["SUB"] = pSub;
	// instruction_math_map.insert(std::make_pair("SUB",pSub));
	// instruction_math_map.emplace("SUB", pSub);
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

	// // cout v_args
	// cout << "vector size " << v_line.size() << endl;
	// for (int i = 0; i < v_line.size(); i++) {
	// 	cout << i << endl;
	// 	for (int j=0; j < v_line[i].size(); j++) {
	// 		cout << "args: " << v_line[i][j] << endl;
	// 	}
	// }
}

void Mis::instruction(string instruction_type) {
	variables.find(instruction_type);
}

// void Mis::(vector<string> v_) {
// 	for(int j = 2; i < v_line[i].size(); j++){
// 				params.push_back(v_lines[i][j]);
// 			}
// }

Mis::~Mis() {}

int main(int argc, char *argv[]) {
// //------------Working example of jump functionality-----------------
// 	Jump a;
// 	std::vector<string> v;
// 	v.push_back("Label");
// 	v.push_back("b");
// 	v.push_back("c");
// 	string type = "JMPLT";
// 	std::map<string, Variable*> map;
// 	Math *b = new Math();
// 	Math *c = new Math("test", 12.0);
// 	map["b"] = b;
// 	map["c"] = c;

// 	a.storeLabel("Label", 6);
// 	cout << a.compare(v, type, map); //compare is only interaction needed with JMP object
// //------------------------------------------------------------------

	Mis mis;
	ifstream input_file (argv[1]);
	mis.parse_file(input_file);

	for (int i=0; i<v_line.size(); i++) {

		cout << v_line[i][0] << endl;

		if (v_line[i][0] == "VAR") {
			mis.instruction(v_line[i][2]);
		} else if (v_line[i][0] == "ADD") {
			// retrieve all args and store in separate params vector
			vector<string> params;
			for(int j = 2; j < v_line[i].size(); j++){
				cout << "push_back " << v_line[i][j] << endl;
				params.push_back(v_line[i][j]);
			}
			// variables[v_line[i][1]]->mathInstructions[v_line[i][0]](params, variables);
			
				
		} else if (v_line[i][0] == "SUB") {

		} else if (v_line[i][0] == "MUL") {

		} else if (v_line[i][0] == "DIV") {

		} else if (v_line[i][0] == "ASSIGN") { //<-----should be same for all types
			// this->setValue(value);
		} else if (v_line[i][0] == "OUT") { //<--- should work for most all

		} else if (v_line[i][0] == "SET_STR_CHAR") {

		} else if (v_line[i][0] == "GET_STR_CHAR") {

		} else if (v_line[i][0] == "LABEL") {
			Jump a;
			// a.storeLabel();
		} else if (v_line[i][0].find("JMP") != string::npos) {

		}
	}
	
	return 0;
}