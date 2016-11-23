#include "mis.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;
using std::string;
using std::regex;


//maybe make hash defined instead? not sure if that'll work/whats more beneficial
const int MAX_CHARS_PER_INSTRUCTION = 2;
const char* const DELIMITER_SPACE = " ";
const char* const DELIMITER_COMMA = ",";


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
		vector<string> v_args;	// create vector to hold instruction arguments
		
		getline(input_file, LINE);	// read line into memory
		v_test.push_back(LINE);


		if (LINE.size() == 0) {
			v_args.push_back("");
			lineNumber++;
			continue;
		}

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
	string paramName;

	// regexs to match literals against
	regex charRgx("'([^\"]|(\\\\[nrt]))'");
	regex strRgx("\"[^\"]*\"");
	regex realRgx("((\\+|-)?[[:digit:]]+)(\\.([[:digit:]]+))");
	regex numRgx("((\\+|-)?[[:digit:]]+)");

	// populate params with arguments for operations
	for(int j = 1; j < v_single_line.size(); j++) {

		// special cases for the first 
		if (j == 1) {
			if (strcmp(v_single_line[0].c_str(), "OUT") == 0) {
				// do nothing
			} else if (v_single_line[0].find("JMP") != string::npos) {
				params.push_back(v_single_line[1]);
				continue;
			} else if (v_single_line[j][0] == '$') {
				continue; 	// ignore the first parameter (it is the var that the
							// function is being called on)
			}
		}

		paramName = v_single_line[j];

		// cout << "obtain_args " << paramName << endl;
		if (paramName[0] == '$') { // this is a variable
			// search name in variables map and obtain value
			params.push_back(paramName);
		} // otherwise, we check to see if it matches any literals

		else if (regex_match(paramName, charRgx)) { // check for char
			char charVal = paramName[paramName.size() - 2];
			if (paramName.size() == 4) {
				if (charVal == 'n') {
					charVal = '\n';
				} else if (charVal == 'r') {
					charVal = '\r';
				} else if (charVal == 't') {
					charVal = '\t';
				}
			}
			Char* myChar = new Char(paramName, charVal);
			charVars[paramName] = myChar;
			params.push_back(paramName);

		} else if (regex_match(paramName, strRgx)) { // check for string
		    String* myString = new String(paramName,paramName,paramName.length());
		    stringVars[paramName] = myString;
		    params.push_back(paramName);

		} else if (regex_match(paramName, realRgx)) { // check for real
			Real* myReal = new Real(paramName, stod(paramName));
			mathVars[paramName] = myReal;
			params.push_back(paramName);

		} else if (regex_match(paramName, numRgx)) { // check for numeric
			Numeric* myNumeric = new Numeric(paramName, stoi(paramName));
			mathVars[paramName] = myNumeric;
			params.push_back(paramName);

		} else {
			errfile << "Error: no matching types for " << paramName << " on line " << index + 1 << endl;
			exit(EXIT_FAILURE);
		}
	}
	return params;
}

void Mis::run() {
	cout << "Starting: " << name << endl;	//ONLY FOR DEBUGGING PURPOSES SHOULD BE REMOVED FOR ACTUAL SUBMISSION

	for (int i=0; i<v_line.size(); i++) {	
		if (v_line[i].size() < 2) {
			continue;
		};

		string var = v_line[i][1];

		if (v_line[i][0] == "VAR") {
			this->create_variable(v_line[i]);
		}
		else if (v_line[i][0] == "ADD") {

			vector<string> params = this->obtain_args(i,v_line[i]);

			if (!(params.size() >= 2 && params.size() <= 13)) {
				errfile << "Incorrect number of arguments to function ADD on line " << i + 1 << endl;
				exit(EXIT_FAILURE);
			}

			for (int j = 0; j < params.size(); j++) {
				if (mathVars.find(params[j]) == mathVars.end()) {
					errfile << "The parameter " << params[j] << " of function ADD on line " 
					<< i + 1 << " is not a Math type\n";
				exit(EXIT_FAILURE);
				}
			}

			if (mathVars[var]->getType() == "Numeric") {
				int x = mathVars[var]->add(params, mathVars);
				mathVars[var]->setValue(x);
			} else {
				double x = mathVars[var]->add(params, mathVars);
				mathVars[var]->setValue(x);
			}

			cout << mathVars[var]->getValue() <<endl;

		} else if (v_line[i][0] == "SUB") {

			vector<string> params = this->obtain_args(i,v_line[i]);

			if (params.size() != 2) {
				errfile << "Incorrect number of arguments to function SUB on line " << i + 1 << endl;
				exit(EXIT_FAILURE);
			}
			
			for (int j = 0; j < params.size(); j++) {
				if (mathVars.find(params[j]) == mathVars.end()) {
					errfile << "The parameter " << params[j] << " of function SUB on line " 
					<< i + 1 << " is not a Math type\n";
				exit(EXIT_FAILURE);
				}
			}

			if (mathVars[var]->getType() == "Numeric") {
				int x = mathVars[var]->sub(params, mathVars);
				mathVars[var]->setValue(x);
			} else {
				double x = mathVars[var]->sub(params, mathVars);
				mathVars[var]->setValue(x);
			}

		} else if (v_line[i][0] == "MUL") {

			vector<string> params = this->obtain_args(i,v_line[i]);

			if (!(params.size() >= 2 && params.size() <= 13)) {
				errfile << "Incorrect number of arguments to function MUL on line " << i + 1 << endl;
				exit(EXIT_FAILURE);
			}

			for (int j = 0; j < params.size(); j++) {
				if (mathVars.find(params[j]) == mathVars.end()) {
					errfile << "The parameter " << params[j] << " of function MUL on line " 
					<< i + 1 << " is not a Math type\n";
				exit(EXIT_FAILURE);
				}
			}

			if (mathVars[var]->getType() == "Numeric") {
				int x = mathVars[var]->mul(params, mathVars);
				mathVars[var]->setValue(x);
			} else {
				double x = mathVars[var]->mul(params, mathVars);
				mathVars[var]->setValue(x);
			}

		} else if (v_line[i][0] == "DIV") {

			vector<string> params = this->obtain_args(i,v_line[i]);

			if (params.size() != 2) {
				errfile << "Incorrect number of arguments to function DIV on line " << i + 1 << endl;
				exit(EXIT_FAILURE);
			}

			for (int j = 0; j < params.size(); j++) {
				if (mathVars.find(params[j]) == mathVars.end()) {
					errfile << "The parameter " << params[j] << " of function DIV on line " 
					<< i + 1 << " is not a Math type\n";
				exit(EXIT_FAILURE);
				}
			}

			if (mathVars[var]->getType() == "Numeric") {
				int x = mathVars[var]->div(params, mathVars);
				mathVars[var]->setValue(x);
			} else {
				double x = mathVars[var]->div(params, mathVars);
				mathVars[var]->setValue(x);
			}

			cout << mathVars[var]->getValue() <<endl;

		} else if (v_line[i][0] == "ASSIGN") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			if(mathVars.find(params[0]) != mathVars.end()) {
				if(mathVars[params[0]]->getType() == "Numeric")
				{
					int x = mathVars[params[0]]->getValue();
					mathVars[var]->setValue(x);
				}

				else
				{
					double x = mathVars[params[0]]->getValue();
					mathVars[var]->setValue(x);
				}

			} else if(charVars.find(var) != charVars.end()) {
				charVars[var]->setValue(charVars[params[0]]->getValue());

			} else if(stringVars.find(var) != stringVars.end()) {
				int state = stringVars[var]->setValue(stringVars[params[0]]->getValue());
				//throw an error if the length of the new string exceeds the max of the current one
				if(state != 0)
				{
					errfile << "New String is longer than max size" << endl;
					exit(EXIT_FAILURE);
				}
			}

		} else if (v_line[i][0] == "OUT") {
			vector<string> params = this->obtain_args(i,v_line[i]);
			for(int j = 0; j < params.size(); ++j) {
				string current = params[j];

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
					errfile << "Invalid variable " << current << " on line " << i + 1 << endl;
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
			if (labelIndex == -2) {
				errfile << "Label " << v_line[i][1] << " called on line " << i + 1 << " does not exist" << endl;
				exit(EXIT_FAILURE);
			}
			
			if(labelIndex == -2) {
				errfile << "Not of supported JMP type" << endl;
				exit(EXIT_FAILURE);
			} else if (labelIndex == -1){
				continue;
			} else {
				i = labelIndex-1;
			}
		} else if (v_line[i][0] == "LABEL") {
			continue;
		}
		else {
			errfile << "Error: instruction " << v_line[i][0] << " on line " << i << " is not a valid type" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

Mis::~Mis() {} // destructor
