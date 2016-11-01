#include <string>
#include <iostream>

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