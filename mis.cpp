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
vector<vector<string>> v_line;
string LINE;

std::map<string, Math*> mathVars;
std::map<string, String*> stringVars;
std::map<string, Char*> charVars;

Mis::Mis() {} // constructor

ifstream Mis::openFiles(string filename) {
	size_t i = filename.rfind('.', filename.length());

	ifstream infile(filename);
	if (infile.fail()) {
		cerr << "Error opening file " << filename <<endl;
		exit(EXIT_FAILURE);
	}

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
		errfile << "error: file cannot be found" << endl;
		return;
	}
	int lineNumber = 0;

	//read each line of input file
	while(!input_file.eof()) {
		cout << "Test line: " << lineNumber <<endl; 
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

		if (strcmp(token[0],"LABEL")==0) {
		this->jmp.storeLabel(token[1],lineNumber);
		}

  		while (p!=0)
  		{
    		v_args.push_back(p);
    		p = std::strtok(NULL,DELIMITER_COMMA);
 		}

 		if(v_args.back().back() == '\r') {
 			v_args.back().pop_back();
 		}

		v_line.push_back(v_args);	// add arguments to v_line
		lineNumber++;
	}
}

void Mis::sleep(Math* var) {

	if (var->getType() != "Numeric") {
		return;
	}
	int sec = var->getValue();
	this_thread::sleep_for(chrono::seconds(sec));
}

void Mis::create_variable(vector<string> lines) {
	string name = lines[1];
	string var_type = lines[2];

	if (var_type == "REAL") {
		double real_value = stod(lines[3]);
		mathVars.insert(pair<string,Real*>(name, new Real(name, real_value)));

	} else if (var_type == "NUMERIC") {
		int num_value = stoi(lines[3]);
		mathVars.insert(pair<string,Numeric*>(name, new Numeric(name, num_value)));

	} else if (var_type == "STRING") {
		string string_value = lines[4];
		int size = stoi(lines[3]);
		stringVars[name] = new String(name, string_value, size);

	} else if (var_type == "CHAR") {
		char char_value = lines[3][1];
		charVars[name] = new Char(name, char_value);

	} else {
		errfile << "Not a supported type" << endl;
		exit(EXIT_FAILURE);
	}
}


vector<string> Mis::obtain_args(int index, vector<string> v_single_line) {
	vector<string> params;
	for (int i = 0; i < v_single_line.size(); i++) {
		cout << v_single_line[i] << endl;
	}
	// populate params with arguments for operations
	for(int j = 1; j < v_single_line.size(); j++) {

		if(j == 1 && (strcmp(v_single_line[0].c_str(), "OUT") == 0)) {
			params.push_back(v_single_line[1]);
			continue;
		}

		if(j == 1 && (v_single_line[j][0] == '$'))
		{
			continue;
		}

		if(j == 1 && (v_single_line[0].find("JMP") != string::npos)) {
			params.push_back(v_single_line[1]);
			continue;
		}

		string paramName = v_single_line[j];

		if (v_single_line[j][0] == '$') {
			// search name in variables map and obtain value
			params.push_back(paramName);
		} 
		else if (v_single_line[j].find_first_of("'") != string::npos && v_single_line[j].size() == 3) { //check for char
			std::regex rgx("('[^\"]')");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			char capture;
			capture = ((*begin).str())[1];
			Char* myChar = new Char(paramName, capture);
			charVars[paramName] = myChar;
			params.push_back(paramName);

		} else if(v_single_line[j].find_first_of("\"") != string::npos) { //check for string
			std::regex rgx("(\"[^\"]*\")");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			string capture = "";

			for (std::sregex_iterator i = begin; i != end; ++i) {
		        std::smatch match = *i;                                                 
		        std::string match_str = match.str(); 
		        capture.append(match_str);
		    }
		    String* myString = new String(paramName, capture);
		    stringVars[paramName] = myString;
		    params.push_back(paramName);

		} else if(v_single_line[j].find_first_of("0123456789") != string::npos) {
	
			std::regex rgx("((\\+|-)?[[:digit:]]+)(\\.([[:digit:]]+))?");
			auto begin = std::sregex_iterator(v_single_line[j].begin(), v_single_line[j].end(), rgx);
			auto end = std::sregex_iterator();
			string capture = "";

			double d = stod(paramName);
			if(v_single_line[j].find_first_of(".") == string::npos) {
				Numeric* myNumeric = new Numeric(paramName, (int)d);
				mathVars[paramName] = myNumeric;
				params.push_back(paramName);
			} else {
				Real* myReal = new Real(paramName, d);
				mathVars[paramName] = myReal;
				params.push_back(paramName);
			}
		} else {
			errfile << "Error: no matching types" << endl;
			exit(EXIT_FAILURE);
		}
	}
	return params;
}

void Mis::run() {
	for (int i=0; i<v_line.size()-1; i++) {

		string var = v_line[i][1];

		if (v_line[i][0] == "VAR") {
			this->create_variable(v_line[i]);
		}
		else if (v_line[i][0] == "ADD") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			mathVars[var]->add(params, mathVars);

		} else if (v_line[i][0] == "SUB") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			mathVars[var]->sub(params, mathVars);

		} else if (v_line[i][0] == "MUL") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			mathVars[var]->mul(params, mathVars);

		} else if (v_line[i][0] == "DIV") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			mathVars[var]->div(params, mathVars);

		} else if (v_line[i][0] == "ASSIGN") {
			vector<string> params = this->obtain_args(i,v_line[i]);
			if(mathVars.find(params[0]) != mathVars.end() && mathVars.find(params[0]) != mathVars.end()) {

				map<string, Math*>::iterator itOne =  mathVars.find(params[0]);
				map<string, Math*>::iterator itTwo =  mathVars.find(params[1]);

				itOne->second->setValue(itTwo->second->getValue());

			} else if(charVars.find(var) != charVars.end() && charVars.find(params[0]) != charVars.end()) {

				map<string, Char*>::iterator itOne =  charVars.find(params[0]);
				map<string, Char*>::iterator itTwo =  charVars.find(params[1]);

				itOne->second->setValue(itTwo->second->getValue());
			} else if(stringVars.find(var) != stringVars.end() && stringVars.find(params[0]) != stringVars.end()) {

				map<string, String*>::iterator itOne =  stringVars.find(params[0]);
				map<string, String*>::iterator itTwo =  stringVars.find(params[1]);

				itOne->second->setValue(itTwo->second->getValue());
			}

		} else if (v_line[i][0] == "OUT") {
			cout << "test" <<endl;
			vector<string> params = this->obtain_args(i,v_line[i]);
			for(int i = 0; i < params.size(); ++i) {
				string current = params[i];

				if(mathVars.find(current) != mathVars.end()) {
					outfile << mathVars[current]->getValue() << endl;
				}
				else if(charVars.find(current) != charVars.end()) {
					outfile << charVars[current]->getValue() << endl;
				}
				else if(stringVars.find(current) != stringVars.end()) {
					outfile << stringVars[current]->getValue() << endl;
				}
				else {
					errfile << "Invalid variable" << endl;
					exit(EXIT_FAILURE);
				}
			}
		} else if (v_line[i][0] == "SET_STR_CHAR") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(mathVars.find(params[0]) != mathVars.end() && charVars.find(params[1]) != charVars.end() && 
				stringVars.find(var) != stringVars.end()) {
				stringVars[var]->setStrChar(mathVars[params[0]], charVars[params[1]]);

			} else {
				errfile << "Error: one or more variables does not exist" << endl;
				exit(EXIT_FAILURE);
			}

		} else if (v_line[i][0] == "GET_STR_CHAR") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(mathVars.find(params[0]) != mathVars.end() && 
				charVars.find(params[1]) != charVars.end() && stringVars.find(var) != stringVars.end()) {
				stringVars[var]->getStrChar(mathVars[params[0]], charVars[params[1]]);

			} else {
				errfile << "Error: one or more variables does not exist" << endl;
				exit(EXIT_FAILURE);
			}

		} else if (v_line[i][0] == "SLEEP") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(params.size() != 1) {
				errfile << "Error, too many arguments" << endl;
				exit(EXIT_FAILURE);

			} else {
				this->sleep(mathVars[params[0]]);
			}
		} else if (v_line[i][0].find("JMP") != string::npos) {
			vector<string> params = this->obtain_args(i,v_line[i]);
			int labelIndex = this->jmp.compare(params, v_line[i][0], mathVars);
			if(labelIndex == -2) {
				errfile << "Not of supported JMP type" << endl;
				exit(EXIT_FAILURE);
			} else if (labelIndex == -1){
				continue;
			} else {
				i = labelIndex-1;
			}
		}
		else {
			errfile << "Error: instruction type is not valid" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

Mis::~Mis() {} // destructor
