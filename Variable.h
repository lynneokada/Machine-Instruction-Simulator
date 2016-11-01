#include <string>
#include <iostream>
#include <thread> //for the sleep function
#include <chrono> //for the sleep function

using std::string;

class Variable {

protected:
	string name;
	string value;

public:
	string getName();
	string getStringValue();
	string getValue();
	void setValue(string str);
	void out();
};