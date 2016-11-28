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


Mis::Mis() // constructor
{
	outBuffer = new vector<string>();
	errBuffer = new vector<string>();

	mathVars = new map<string, Math*>;
	stringVars = new map<string, String*>;
	charVars = new map<string, Char*>;
}

Mis::~Mis() {} // destructor

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

void Mis::parseLines(vector<string>* lines)
{
	int lineNumber = 0;

	for (int i = 0; i < lines->size()-1; ++i)
	{
		vector<string> v_args;
		cout << "Line is: " << (*lines)[i] << endl;
		LINE = (*lines)[i];

		if (LINE.size() == 0) {
			v_args.push_back("");
			lineNumber++;
			continue;
		}

		char* instruction_line = strdup(LINE.c_str());
		cout << "LINE " << LINE << endl;
		// grab instruction
		char* token[MAX_CHARS_PER_INSTRUCTION] = {};
		token[0] = std::strtok(instruction_line, DELIMITER_SPACE);
		cout << "token[0] " << token[0] << endl;
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

		cout << "v_args: ";
		for (int i = 0; i < v_args.size(); ++i) {
			cout << v_args[i] << " ";
		}
		cout << endl;
		v_line.push_back(v_args);	// add arguments to v_line
		cout << "Vargs " << v_args[0] << endl;
		cout << "V_line: " << v_line[lineNumber][0] << " at: " << lineNumber << endl;
		lineNumber++;
	}
	cout << "Size" <<  v_line.size() << endl;
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
	cout << var->getType() << endl;
	if (var->getType() != "Numeric") {
		return;
	}
	int sec = var->getValue();
	cout << "Sleeping for " << sec << " seconds\n";
	this_thread::sleep_for(chrono::seconds(sec));
	cout << "Done sleeping" << endl;
}

void Mis::create_variable(vector<string> lines) {
	cout << "creating variable\n";
	string name = lines[1];
	string var_type = lines[2];

	if (var_type == "REAL") {
		cout << "real" << endl;
		double real_value = stod(lines[3]);
		mathVars->insert(pair<string,Real*>(name, new Real(name, real_value)));
	} else if (var_type == "NUMERIC") {
		cout << "numeric" << endl;
		int num_value = stoi(lines[3]);
		mathVars->insert(pair<string,Numeric*>(name, new Numeric(name, num_value)));
	} else if (var_type == "STRING") {
		cout << "string" << endl;
		string string_value = lines[4];
		int size = stoi(lines[3]);
		(*stringVars)[name] = new String(name, string_value, size);
	} else if (var_type == "CHAR") {
		cout << "char" << endl;
		char char_value = lines[3][1];
		(*charVars)[name] = new Char(name, char_value);
	} else {
		errBuffer->push_back("Not a supported type");
		exit(EXIT_FAILURE);
	}
}


vector<string> Mis::obtain_args(int index, vector<string> v_single_line) 
{
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
			} else if (v_single_line[0].find("SLEEP") != string::npos) {
				
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
			(*charVars)[paramName] = myChar;
			params.push_back(paramName);

		} else if (regex_match(paramName, strRgx)) { // check for string
		    String* myString = new String(paramName,paramName,paramName.length());
		    (*stringVars)[paramName] = myString;
		    params.push_back(paramName);

		} else if (regex_match(paramName, realRgx)) { // check for real
			Real* myReal = new Real(paramName, stod(paramName));
			(*mathVars)[paramName] = myReal;
			params.push_back(paramName);

		} else if (regex_match(paramName, numRgx)) { // check for numeric
			Numeric* myNumeric = new Numeric(paramName, stoi(paramName));
			(*mathVars)[paramName] = myNumeric;
			params.push_back(paramName);

		} else {
			errBuffer->push_back("Error: no matching types for "+ paramName + " on line " + to_string(index + 1));
			exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
		}
	}
	return params;
}

void Mis::run(vector<string>* out, vector<string>* err) 
{ 
	
	// outfile << "Starting: " << name << endl;	//ONLY FOR DEBUGGING PURPOSES SHOULD BE REMOVED FOR ACTUAL SUBMISSION
	// out->push_back("Testing");
	cout << "starting:\n";
	// outBuffer = out;
	// errBuffer = err;
	cout << "v_line " << v_line.size() << endl;
	cout << "Buffers set" << endl;

	for (int i=0; i<v_line.size(); 	i++) {	
		cout << "index " << i << v_line[i][0] << endl;
		if (v_line[i].size() < 2) {
			continue;
		};

		string var = v_line[i][1];

		if (v_line[i][0] == "VAR") {
			
			this->create_variable(v_line[i]);

		} else if (v_line[i][0] == "ADD") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			(*mathVars)[var]->add(params, *mathVars);

		} else if (v_line[i][0] == "SUB") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			// (*mathVars)[var]->sub(params, mathVars);
			// cout << (*mathVars)[var]->getValue() << endl;

			// if ((*mathVars)[params[0]]->getType() == "Numeric") {
			// 	int x = (*mathVars)[var]->sub(params, mathVars);
			// 	(*mathVars)[var]->setValue(x);
			// } else {
			// 	double x = (*mathVars)[var]->sub(params, mathVars);
			// 	(*mathVars)[var]->setValue(x);
			// }

			double x = (*mathVars)[var]->sub(params, *mathVars);
			(*mathVars)[var]->setValue(x);

			// cout << (*mathVars)[var]->getValue() << endl;e

		} else if (v_line[i][0] == "MUL") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			(*mathVars)[var]->mul(params, *mathVars);

		} else if (v_line[i][0] == "DIV") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			(*mathVars)[var]->div(params, *mathVars);

		} else if (v_line[i][0] == "ASSIGN") {

			vector<string> params = this->obtain_args(i,v_line[i]);
			if(mathVars->find(params[0]) != mathVars->end()) {
				if((*mathVars)[params[0]]->getType() == "Numeric")
				{
					int x = (*mathVars)[params[0]]->getValue();
					(*mathVars)[var]->setValue(x);
				}

				else
				{
					double x = (*mathVars)[params[0]]->getValue();
					(*mathVars)[var]->setValue(x);
				}

			} else if(charVars->find(var) != charVars->end()) {
				(*charVars)[var]->setValue((*charVars)[params[0]]->getValue());

			} else if(stringVars->find(var) != stringVars->end()) {
				int state = (*stringVars)[var]->setValue((*stringVars)[params[0]]->getValue());
				//throw an error if the length of the new string exceeds the max of the current one
				if(state != 0)
				{
					errBuffer->push_back("New String is longer than max size");
					exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
				}
			}

		} else if (v_line[i][0] == "OUT") {
			vector<string> params = this->obtain_args(i,v_line[i]);
			for(int j = 0; j < params.size(); ++j) {
				string current = params[j];

				if(mathVars->find(current) != mathVars->end()) {
					outBuffer->push_back(to_string((*mathVars)[current]->getValue()));
				}
				else if(charVars->find(current) != charVars->end()) {
					outBuffer->push_back(to_string((*charVars)[current]->getValue()));
				}
				else if(stringVars->find(current) != stringVars->end()) {
					outBuffer->push_back((*stringVars)[current]->getValue());
				}
				else {
					errBuffer->push_back("Invalid variable " + current + " on line " + to_string(i + 1));
					exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
				}
			}
		} else if (v_line[i][0] == "SET_STR_CHAR") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(mathVars->find(params[0]) != mathVars->end() && charVars->find(params[1]) != charVars->end() && 
				stringVars->find(var) != stringVars->end()) {
				(*stringVars)[var]->setStrChar((*mathVars)[params[0]], (*charVars)[params[1]]);

			} else {
				errBuffer->push_back("Error: one or more variables does not exist");
				exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
			}

		} else if (v_line[i][0] == "GET_STR_CHAR") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(mathVars->find(params[0]) != mathVars->end() && 
				charVars->find(params[1]) != charVars->end() && stringVars->find(var) != stringVars->end()) {
				(*stringVars)[var]->getStrChar((*mathVars)[params[0]], (*charVars)[params[1]]);

			} else {
				errBuffer->push_back("Error: one or more variables does not exist");
				exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
			}

		} else if (v_line[i][0] == "SLEEP") {
			cout << v_line[i][0] << v_line[i][1] << endl;
			vector<string> params = this->obtain_args(i,v_line[i]);
			if(params.size() != 1) {
				errBuffer->push_back("Error, too many arguments");
				exit(EXIT_FAILURE); //change to something thatll exit to mis.out function

			} else {
				cout << "sleeping" << endl;
				this->sleep((*mathVars)[params[0]]);
			}
		} else if (v_line[i][0].find("JMP") != string::npos) {
			vector<string> params = this->obtain_args(i,v_line[i]);
			
			int labelIndex = this->jmp.compare(params, v_line[i][0], *mathVars);
			if (labelIndex == -2) {
				errBuffer->push_back("Label " + v_line[i][1] + " called on line " + to_string(i + 1) + " does not exist");
				exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
			}
			
			if(labelIndex == -2) {
				errBuffer->push_back("Not of supported JMP type");
				exit(EXIT_FAILURE);
			} else if (labelIndex == -1){
				continue;
			} else {
				i = labelIndex-1;
			}
		} else if(v_line[i][0] == "THREAD_BEGIN") {
			int end = 0;
			vector<vector<string>> subset;
			for (int j = i; j < v_line.size(); ++j)
			{
				if(v_line[j][0] == "THREAD_END")
				{
					end = j;
					break;
				}
			}

			if(end != 0)
			{
				for (int index = i; index <= end; ++index)
				{
					for (int j = 0; j < v_line[index].size(); ++j)
					{
						subset[index].push_back(v_line[index][j]);
					}
				}
				workers.push_back(spawnWorkerThread(subset));
			}

			else
			{
				errBuffer->push_back("THREAD_BEGIN does not have matching THREAD_END");
				break;
			}

		} else if(v_line[i][0] == "BARRIER") {
			if(isWorker == false)
			{
				this->joinThreads();
			}
			else 
			{
				errBuffer->push_back("Error: this is not a client thread and cannot call BARRIER");
				exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
			}
		} else if (v_line[i][0] == "LABEL") {
			continue;
		}
		else {
			errBuffer->push_back("Error: instruction " + v_line[i][0] +" on line " + to_string(i) +" is not a valid type");
			exit(EXIT_FAILURE); //change to something thatll exit to mis.out function
		}
	}
}

std::thread Mis::spawnWorkerThread(vector<vector<string>> subset)
{
	threadCount++;
	return std::thread([=] {spawnWorker(subset);});
}

void Mis::spawnWorker(vector<vector<string>> subset)
{
	WorkerThread t(subset, this);
	t.setLines(subset);
	t.setFlag(true);
	t.setId(id);
	t.run(outBuffer, errBuffer);
}

void Mis::setFlag(bool flag) //differentiates between Client thread and Subset thread
{
	isWorker = flag;
}

void Mis::setLines(vector<vector<string>> subset)
{
	v_line = subset;
}

void Mis::bufferWrite(vector<string> *buffer, string message) //use for all the writing to buffers
{
	mtx.lock();
	buffer->push_back(message);
	mtx.unlock();
}

void Mis::joinThreads()
{
	for (int i = 0; i < workers.size(); ++i)
	{
		workers[i].join();
	}
}

void Mis::lock(string variable)
{
	if(isWorker == true)
	{
		if(mathVars->find(variable) != mathVars->end())
			(*mathVars)[variable]->lock(id);
		else if(charVars->find(variable) != charVars->end())
			(*charVars)[variable]->lock(id);
		else if(stringVars->find(variable) != stringVars->end())
			(*stringVars)[variable]->lock(id);
		else
			bufferWrite(errBuffer, "Variable doesn't exist");
	}
	else
		bufferWrite(errBuffer, "Cannot call lock from outside an MIS thread");
}

void Mis::unlock(string variable)
{
	if(isWorker == true)
	{
		if(mathVars->find(variable) != mathVars->end())
			(*mathVars)[variable]->unlock(id);
		else if(charVars->find(variable) != charVars->end())
			(*charVars)[variable]->unlock(id);
		else if(stringVars->find(variable) != stringVars->end())
			(*stringVars)[variable]->unlock(id);
		else
			bufferWrite(errBuffer, "Variable doesn't exist");
	}
	else
		bufferWrite(errBuffer, "Cannot call unlock from outside an MIS thread");
}

void Mis::loadVariables(Mis* mis) {
	this->mathVars = mis->mathVars;
	this->stringVars = mis->stringVars;
	this->charVars = mis->charVars;
}

void Mis::initializeVariables(std::map<string, Math*>* threadMathVars, 
	std::map<string, String*>* threadStringVars, std::map<string, Char*>* threadCharVars) {
	cout << "test\n";
	mathVars = threadMathVars;
	cout << "test1\n";
	stringVars = threadStringVars;
	cout << "test2\n";
	charVars = threadCharVars;
	cout << "test3\n";
}

void Mis::setId(int num)
{
	id = num;
}