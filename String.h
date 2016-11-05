#include "Variable.h"

class String : public Variable {
private:
	string name;
	string value;

public:
	String(string p_name = "", string p_value = "");
	~String();
	string getValue();
	void setStrChar(Variable index, Variable ch);
	void getStrChar(Variable index, Variable ch);
};