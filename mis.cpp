#include "mis.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::array;
using std::string;
using std::regex;

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
		throw std::invalid_argument("Error during execution of program");
	}

	if (i == string::npos || filename.substr(i, 
		filename.length()-i) != ".mis") {
        cerr << "Incorrect input file. Please provide a .mis file" << endl;
        throw std::invalid_argument("Error during execution of program");
    }

	string basefile(basename(const_cast<char*> (filename.c_str())));

    char* out = strdup((basefile.substr(0, basefile.length()-3) + "out").c_str());
    outfile.open(out);
    if (!outfile.is_open()) {
        cerr << "Error opening outfile";
        throw std::invalid_argument("Error during execution of program");
    }

    char* err = strdup((basefile.substr(0, basefile.length()-3) + "err").c_str());
    errfile.open(err);
    if (!errfile.is_open()) {
    	cerr << "Error opening errfile";
    	throw std::invalid_argument("Error during execution of program");
    }

    return infile;
}

//parse the lines coming in from the ClientThread's socket
void Mis::parseLines(vector<string>* lines)
{
	int lineNumber = 0;

	for (int i = 0; i < lines->size()-1; ++i)
	{
		vector<string> v_args;
		LINE = (*lines)[i];

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
	if (var->getType() != "Numeric")
		return;
	
	int sec = var->getValue();
	this_thread::sleep_for(chrono::seconds(sec));
}

//wrap primitive in an object so it can interface with the other functions
void Mis::create_variable(vector<string> lines) {
	string name = lines[1];
	string var_type = lines[2];

	if (var_type == "REAL") {
		double real_value = stod(lines[3]);
		mathVars->insert(pair<string,Real*>(name, new Real(name, real_value)));

	} else if (var_type == "NUMERIC") {
		int num_value = stoi(lines[3]);
		mathVars->insert(pair<string,Numeric*>(name, new Numeric(name, num_value)));

	} else if (var_type == "STRING") {
		string string_value = lines[4];
		int size = stoi(lines[3]);
		(*stringVars)[name] = new String(name, string_value, size);

	} else if (var_type == "CHAR") {
		char char_value = lines[3][1];
		(*charVars)[name] = new Char(name, char_value);

	} else {
		bufferWrite(errBuffer,"Not a supported type");
		throw std::invalid_argument("Error during execution of program");
	}
}

//determine which arguments are going to be used as parameters for a given function
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
			bufferWrite(errBuffer,"Error: no matching types for "+ paramName + " on line " + to_string(index + 1));
			throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
		}
	}
	return params;
}

//main execution of each thread's instructions
void Mis::run(vector<string>* out, vector<string>* err) 
{ 
	for (int i=0; i<v_line.size(); 	i++) {	
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

			double x = (*mathVars)[var]->sub(params, *mathVars);
			(*mathVars)[var]->setValue(x);

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
					bufferWrite(errBuffer,"New String is longer than max size");
					throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
				}
			}

		} else if (v_line[i][0] == "OUT") {
			vector<string> params = this->obtain_args(i,v_line[i]);
			for(int j = 0; j < params.size(); ++j) {
				string current = params[j];

				if(mathVars->find(current) != mathVars->end()) {
					bufferWrite(outBuffer,to_string((*mathVars)[current]->getValue()));
				}
				else if(charVars->find(current) != charVars->end()) {
					bufferWrite(outBuffer,to_string((*charVars)[current]->getValue()));
				}
				else if(stringVars->find(current) != stringVars->end()) {
					bufferWrite(outBuffer,(*stringVars)[current]->getValue());
				}
				else {
					bufferWrite(errBuffer,"Invalid variable " + current + " on line " + to_string(i + 1));
					throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
				}
			}
		} else if (v_line[i][0] == "SET_STR_CHAR") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(mathVars->find(params[0]) != mathVars->end() && charVars->find(params[1]) != charVars->end() && 
				stringVars->find(var) != stringVars->end()) {
				(*stringVars)[var]->setStrChar((*mathVars)[params[0]], (*charVars)[params[1]]);

			} else {
				bufferWrite(errBuffer,"Error: one or more variables does not exist");
				throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
			}

		} else if (v_line[i][0] == "GET_STR_CHAR") {
			vector<string> params = this->obtain_args(i,v_line[i]);

			if(mathVars->find(params[0]) != mathVars->end() && 
				charVars->find(params[1]) != charVars->end() && stringVars->find(var) != stringVars->end()) {
				(*stringVars)[var]->getStrChar((*mathVars)[params[0]], (*charVars)[params[1]]);

			} else {
				bufferWrite(errBuffer,"Error: one or more variables does not exist");
				throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
			}

		} else if (v_line[i][0] == "SLEEP") {
			vector<string> params = this->obtain_args(i,v_line[i]);
			if(params.size() != 1) {
				bufferWrite(errBuffer,"Error, too many arguments");
				throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function

			} else {
				this->sleep((*mathVars)[params[0]]);
			}
		} else if (v_line[i][0].find("JMP") != string::npos) {
			vector<string> params = this->obtain_args(i,v_line[i]);
			
			int labelIndex = this->jmp.compare(params, v_line[i][0], *mathVars);
			if (labelIndex == -2) {
				bufferWrite(errBuffer,"Label " + v_line[i][1] + " called on line " + to_string(i + 1) + " does not exist");
				throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
			}
			
			if(labelIndex == -2) {
				bufferWrite(errBuffer,"Not of supported JMP type");
				throw std::invalid_argument("Error during execution of program");
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
				bufferWrite(errBuffer,"THREAD_BEGIN does not have matching THREAD_END");
				break;
			}

		} else if(v_line[i][0] == "BARRIER") {
			if(isWorker == false)
			{
				this->joinThreads();
			}
			else 
			{
				bufferWrite(errBuffer,"Error: this is not a client thread and cannot call BARRIER");
				throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
			}
		} else if (v_line[i][0] == "LABEL") {
			continue;
		}
		else {
			bufferWrite(errBuffer,"Error: instruction " + v_line[i][0] +" on line " + to_string(i) +" is not a valid type");
			throw std::invalid_argument("Error during execution of program"); //change to something thatll exit to mis.out function
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
	mathVars = threadMathVars;
	stringVars = threadStringVars;
	charVars = threadCharVars;
}

void Mis::setId(int num)
{
	id = num;
}