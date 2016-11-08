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

	if (i == string::npos || filename.substr(i, filename.length()-i) != ".mis") {
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

void Mis::find_instruction(string instruction_type, string name, string value) {
	
}

void Mis::create_variable(string var_type, string name, string value) {
	if (var_type == "REAL") {
		double real_value = stod(value);
		mathVariables.insert(pair<string,Real*>(name, new Real(name, real_value)));
		// mathVariables[name] = new Real(name, real_value);
	} else if (var_type == "NUMERIC") {
		int num_value = stoi(value);
		mathVariables.insert(pair<string,Numeric*>(name, new Numeric(name, num_value)));
		mathVariables[name] = new Numeric(name, num_value);
	} else if (var_type == "STRING") {
		string string_value = value;
		stringVariables[name] = new String(name, string_value);
	} else if (var_type == "CHAR") {
		char char_value = value[0];
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
	for(int j = 2; j < v_single_line.size(); j++){

		if (v_single_line[j][0] == '$') {	// find variable names
			// search name in variables map and obtain value
			cout << "this is a variable" << endl;
			params.push_back(v_single_line[j]);
		} 
		else if (v_single_line[j].find_first_not_of("0123456789") == string::npos) {
			//has to be either a char or a string
			std::regex rgx("(\"[^\"]*\")||('[^\"]*')");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			string capture = "";
			for (std::sregex_iterator i = begin; i != end; ++i) {
		        std::smatch match = *i;                                                 
		        std::string match_str = match.str(); 
		        capture.append(match_str);
		    }
		} else {
			int ch;
			for (int k = 0; k < v_single_line[j].size(); k++) {
				ch = v_single_line[j][k];
				if (('0' <= ch && ch <= '9') || ch == '+' || ch == '-' || ch == '.') {
					// validate individual characters
				} else {
					cout << v_single_line[j] << " is not a valid argument." << endl;
					exit(EXIT_FAILURE);
				}
			}
			// cast double value as Math
			double d = stod(v_single_line[j]);
			Math * myD = new Math(v_single_line[j], d);
			mathVariables[v_single_line[j]] = myD;
			// add Math object title to params vector
			cout << "push_back " << v_line[index][j] << endl;
			params.push_back(v_single_line[j]);
		}
	}

	for (int a=0; a<params.size(); a++) {
		cout << "push back " << params[a] << endl;
	}
	return params;
}

Mis::~Mis() {} // destructor

int main(int argc, char *argv[]) 
{

	Mis mis;
	// mis.jmp.storeLabel("Lab", 12);
	ifstream input_file (argv[1]);
	mis.parse_file(input_file);

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
			mis.create_variable(v_line[i][2], v_line[i][1], v_line[i][3]);
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
			
			//vector<string> params = mis.obtain_args(i,v_line[i]);

			if(mathVariables.find(var) != mathVariables.end()) {
				// cout << "Math found" << endl;
				// Math *first = (mathVariables[v_line[i][1]]);
				// Math *second = (mathVariables[v_line[i][2]]);
				// cout << typeid(mathVariables[v_line[i][2]]).name() << endl;
				// mathVariables[v_line[i][2]]->setValue(2);


				// cout << "1st value: " << mathVariables[v_line[i][1]]->getValue() << endl;
				// cout << "Second value: " << mathVariables[v_line[i][2]]->getValue() << endl;

				map<string, Math*>::iterator itOne =  mathVariables.find(v_line[i][1]);
				map<string, Math*>::iterator itTwo =  mathVariables.find(v_line[i][2]);

				itOne->second->setValue(itTwo->second->getValue());
				// itOne->second->out();
				// cout << "test" << endl;

				// cout << "Set to: " << mathVariables[v_line[i][1]]->getValue() << endl;
			} else if(charVariables.find(var) != charVariables.end()) {
				// cout << "Char found" << endl;
				// Char *first = (charVariables[v_line[i][1]]);
				// Char *second = (charVariables[v_line[i][2]]);
				// first->setValue(second->getValue());

				map<string, Char*>::iterator itOne =  charVariables.find(v_line[i][1]);
				map<string, Char*>::iterator itTwo =  charVariables.find(v_line[i][2]);

				itOne->second->setValue(itTwo->second->getValue());
			} else if(stringVariables.find(var) != stringVariables.end()) {

				map<string, String*>::iterator itOne =  stringVariables.find(v_line[i][1]);
				map<string, String*>::iterator itTwo =  stringVariables.find(v_line[i][2]);

				itOne->second->setValue(itTwo->second->getValue()); //--------------double check if its actually setValue
				// cout << "Str found" << endl;
				// String *first = (stringVariables[v_line[i][1]]);
				// String *second = (stringVariables[v_line[i][2]]);
				// first->setValue(second->getValue());
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

		} else if (v_line[i][0] == "GET_STR_CHAR") {

		} else if (v_line[i][0] == "LABEL") { //need to preprocess this in beginning of scan
			//mis.jmp.storeLabel(v_line[i][1], v_line[i][2]);
		} else if (v_line[i][0].find("JMP") != string::npos) {
			vector<string> params = mis.obtain_args(i,v_line[i]);
			mis.jmp.compare(params, v_line[i][0], mathVariables);
		}
		else
		{
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