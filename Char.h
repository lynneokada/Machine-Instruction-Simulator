#include "Variable.h"

class Char : public Variable {
private:
	string name;
	char value;

public:
	Char(string p_name = "", char p_value = '\0');
	~Char();
	char getValue();
	void setValue(char val);
};