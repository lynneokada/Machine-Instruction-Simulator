#include "mis.h"
#include <typeinfo>

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
vector<vector<string>> v_line;
string LINE;

// std::map<string, Math*> instruction_math_map;
// std::map<string, String*> instruction_string_map;
// std::map<string, Char*> instruction_char_map;

std::map<string, Math*> mathVariables;
std::map<string, String*> stringVariables;
std::map<string, Char*> charVariables;

// declare types and maps
typedef void(Math::*mathFunction)(vector<string>, map<string, Math*>);

std::map<std::string, mathFunction> mathInstructions;

Mis::Mis() {	// constructor
	mathInstructions["ADD"] = &Math::add;
	mathInstructions["MUL"] = &Math::mul;
	mathInstructions["DIV"] = &Math::div;
	mathInstructions["SUB"] = &Math::sub;
	mathInstructions["ASSIGN"] = &Math::setValue;
}

ifstream Mis::openFiles(string filename) {
	size_t i = filename.rfind('.', filename.length());

	ifstream infile(filename);
	if (infile.fail()) {
		cerr << "Error opening file " << filename <<endl;
		exit(EXIT_FAILURE);
	}

	// try {
	// 	infile.open(filename);
	// }
	// catch (std::ios_base::failure& e) {
	// 	cerr << e.what() << endl;
	// 	exit(EXIT_FAILURE);
	// }

	if (i == string::npos || filename.substr(i, 
		filename.length()-i) != ".mis") {
        cerr << "Incorrect input file. Please provide a .mis file" << endl;
        exit(EXIT_FAILURE);
    }

	string basefile(basename(const_cast<char*> (filename.c_str())));

    char* out = strdup((basefile.substr(0, basefile.length()-3) + "out").c_str());
    outfile.open(out);
    if (!outfile.is_open()) {
        cerr << "Error opening outfile";
        exit(EXIT_FAILURE);
    }

    char* err = strdup((basefile.substr(0, basefile.length()-3) + "err").c_str());
    errfile.open(err);
    if (!errfile.is_open()) {
    	cerr << "Error opening errfile";
    	exit(EXIT_FAILURE);
    }

    return infile;
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
    		cout << "p: " << p << endl;
    		p = std::strtok(NULL,DELIMITER_COMMA);
 		}

 		// cout << "last paaram: " << v_args.back() << endl;

 		if(v_args.back().back() == '\r') {
 			v_args.back().pop_back();
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

void Mis::sleep(Math* var) {

	if (var->getType() != "Numeric") {
		return;
	}
	int sec = var->getValue();
	this_thread::sleep_for(chrono::seconds(sec));
}

void Mis::find_instruction(string instruction_type, string name, string value) {
	
}

void Mis::create_variable(vector<string> lines) {
	string name = lines[1];
	string var_type = lines[2];
	// (v_line[i][2], v_line[i][1], v_line[i][3])
	//  type 			name 			"value"
	if (var_type == "REAL") {
		double real_value = stod(lines[3]);
		mathVariables.insert(pair<string,Real*>(name, new Real(name, real_value)));
		// mathVariables[name] = new Real(name, real_value);
	} else if (var_type == "NUMERIC") {
		int num_value = stoi(lines[3]);
		mathVariables.insert(pair<string,Numeric*>(name, new Numeric(name, num_value)));
		// mathVariables[name] = new Numeric(name, num_value);
	} else if (var_type == "STRING") {
		string string_value = lines[4];
		cout << "string value: " << string_value <<endl;
		int size = stoi(lines[3]);
		stringVariables[name] = new String(name, string_value, size);
	} else if (var_type == "CHAR") {
		char char_value = lines[3][0];
		charVariables[name] = new Char(name, char_value);
	} else {
		cout << "wrong" << endl;
	}
}

// vector<string> Mis::obtain_args(int index, vector<string> v_single_line) {
// 	vector<string> params;
// 	for(unsigned int j = 2; j < v_single_line.size(); ++j){
// 		cout << "push_back " << v_line[index][j] << endl;
// 		params.push_back(v_line[index][j]);
// 	}
// 	cout << "Finished" << endl;

vector<string> Mis::obtain_args(int index, vector<string> v_single_line) {
	vector<string> params;	// returning vector
	// populate params with arguments for operations
	for(int j = 1; j < v_single_line.size(); j++) {
		if(j == 1 && v_single_line[j][0] == '$')
		{
			continue;
		}
		string paramName = v_single_line[j];
		cout << "Line contains: " << paramName << endl;

		if (v_single_line[j][0] == '$') {	// find variable names
			// search name in variables map and obtain value
			cout << "this is a variable" << endl;
			params.push_back(paramName);
		} 
		else if (v_single_line[j].find_first_of("'") != string::npos && v_single_line[j].size() == 3) { //check for char
			std::regex rgx("('[^\"]')");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			char capture;
			capture = ((*begin).str())[1];
			Char* myChar = new Char(paramName, capture);
			charVariables[paramName] = myChar;
			params.push_back(paramName);

		} else if(v_single_line[j].find_first_of("\"") != string::npos) { //check for string
			std::regex rgx("(\"[^\"]*\")");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			string capture = "";
			cout << "Single Line String: " << v_single_line[j] << endl;
			for (std::sregex_iterator i = begin; i != end; ++i) {
		        std::smatch match = *i;                                                 
		        std::string match_str = match.str(); 
		        capture.append(match_str);
		    }
		    String* myString = new String(paramName, capture);
		    stringVariables[paramName] = myString;
		    params.push_back(paramName);

		} else if(v_single_line[j].find_first_of("0123456789") != string::npos){
			// cout << "Found number" << endl;
			std::regex rgx("(-)?[0-9]+(\.[0-9]+)?");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			string capture = "";
			// for (std::sregex_iterator i = begin; i != end; ++i) {
			// 	cout << "Value of regex iterator: " << (*i).str() << endl;
		 //    }

			// cast double value as Math
			double d = stod(paramName);
			if(v_single_line[j].find_first_of(".") == string::npos) {
				Numeric* myNumeric = new Numeric(paramName, (int)d);
				mathVariables[paramName] = myNumeric;
				params.push_back(paramName);
			} else {
				Real* myReal = new Real(paramName, d);
				mathVariables[paramName] = myReal;
				params.push_back(paramName);
			}
			
			// add Math object title to params vector
			// cout << "push_back " << v_line[index][j] << endl;
		} else {
			//need to throw an error or at least print "no matching types"
			cout << "Error: no matching types" << endl;
		}
	}

	// for (int a=0; a<params.size(); a++) {
	// 	cout << "push back " << params[a] << endl;
	// }
	return params;
}

Mis::~Mis() {} // destructor

int main(int argc, char *argv[]) 
{

	Mis mis;
	// mis.jmp.storeLabel("Lab", 12);
	ifstream input_file (argv[1]);
	// mis.parse_file(input_file);

	// Math *a = new Math("name", 12.1);
	// Math *b = new Math("test", 150.3);
	// a->out();
	// a->setValue(b->getValue());
	// a->out();

	// Numeric *a = new Numeric("test", 12.12);
	// Real *b = new Real("testing", 12.12);
	// cout << a->getValue() << endl;
	// cout << b->getValue() << endl;
	// a->out();
	// std::map<string, Math*> map;
	// map["test"] = a;
	// map["testing"] = b;
	// map["testing"]->out();


//------------Working example of jump functionality-----------------
	// Jump a;
	// std::vector<string> v;
	// // v.push_back("Label");
	// v.push_back("b");
	// v.push_back("c");
	// string type = "JMPLT";
	// std::map<string, Variable*> map;
	// Math *b = new Math("testing", 45.0);

	// Math *c = new Math("test", 12.0);
	// map["b"] = b;
	// map["c"] = c;
	// Math d;
	// d.add(v, map);
	// d.out();

	// a.storeLabel("Label", 6);
	// cout << a.compare(v, type, map); //compare is only interaction needed with JMP object
//------------------------------------------------------------------


	input_file = mis.openFiles(argv[1]);
	mis.parse_file(input_file);

	for (int i=0; i<v_line.size(); i++) {
		string var = v_line[i][1];
		cout << v_line[i][0] << endl;

		if (v_line[i][0] == "VAR") {
			// mis.create_variable(v_line[i][2], v_line[i][1], v_line[i][3]);
			mis.create_variable(v_line[i]);
		}
		else if (v_line[i][0] == "ADD") {

			vector<string> params = mis.obtain_args(i,v_line[i]);
			mathVariables[var]->add(params, mathVariables);

		} else if (v_line[i][0] == "SUB") {

			vector<string> params = mis.obtain_args(i,v_line[i]);
			mathVariables[var]->sub(params, mathVariables);

		} else if (v_line[i][0] == "MUL") {

			vector<string> params = mis.obtain_args(i,v_line[i]);
			mathVariables[var]->mul(params, mathVariables);

			// a->mul(params, variables);
		} else if (v_line[i][0] == "DIV") {

			vector<string> params = mis.obtain_args(i,v_line[i]);
			mathVariables[var]->div(params, mathVariables);

		} else if (v_line[i][0] == "ASSIGN") { //<-----needs to be worked on/fixed
			// cout << "Assigning values" << endl;
			if(mathVariables.find(var) != mathVariables.end()) {

				map<string, Math*>::iterator itOne =  mathVariables.find(v_line[i][1]);
				map<string, Math*>::iterator itTwo =  mathVariables.find(v_line[i][2]);

				itOne->second->setValue(itTwo->second->getValue());

			} else if(charVariables.find(var) != charVariables.end()) {

				map<string, Char*>::iterator itOne =  charVariables.find(v_line[i][1]);
				map<string, Char*>::iterator itTwo =  charVariables.find(v_line[i][2]);

				itOne->second->setValue(itTwo->second->getValue());
			} else if(stringVariables.find(var) != stringVariables.end()) {

				map<string, String*>::iterator itOne =  stringVariables.find(v_line[i][1]);
				map<string, String*>::iterator itTwo =  stringVariables.find(v_line[i][2]);

				itOne->second->setValue(itTwo->second->getValue()); //--------------double check if its actually setValue
			}

		} else if (v_line[i][0] == "OUT") {
			vector<string> params = mis.obtain_args(i,v_line[i]);
			for(int i = 0; i < params.size(); ++i)
			{
				string current = params[i];
				if(mathVariables.find(current) != mathVariables.end())
					mathVariables[current]->out();
				else if(charVariables.find(current) != charVariables.end())
					charVariables[current]->out();
				else if(stringVariables.find(current) != stringVariables.end())
					stringVariables[current]->out();
				else
					cout << "Invalid variable" << endl;
			}
		} else if (v_line[i][0] == "SET_STR_CHAR") {
			vector<string> params = mis.obtain_args(i,v_line[i]);
			cout << "before: " << stringVariables[var]->getValue() << endl;
			stringVariables[var]->setStrChar(mathVariables[params[0]], charVariables[params[1]]);
			cout << "after: " << stringVariables[var]->getValue() << endl;
		} else if (v_line[i][0] == "GET_STR_CHAR") {

			vector<string> params = mis.obtain_args(i,v_line[i]);
			// stringVariables[var]->getStrChar(mathVariables[params[0]], charVariables[params[1]]);

		} else if (v_line[i][0] == "SLEEP") {

			vector<string> params = mis.obtain_args(i,v_line[i]);
			if(params.size() != 1) //checking if only 1 arg is given/is of type math
				cout << "Error, too many arguments" << endl;
			else {
				mis.sleep(mathVariables[params[0]]);
			}
		} else {
			//something went wrong
		}
	
	}
	
	// return 0;

	// Mis mis;
	// Numeric a("$var1", 12);

	// string filename = argv[argc-1];
	// ifstream testStream = mis.openFiles(filename);

	// mis.parse_file(testStream);

	// cout << a.getValue() << endl;
	// cout << "test " << a.getName() << endl;
	// a.out();

	// outfile << "test" <<endl;

	return 0;
}