#include <string>

class Variable {

protected:
	string name;
	string value;

public:
	string getName();
	void getStringValue();
	void setValue(string str);
	void out();
}