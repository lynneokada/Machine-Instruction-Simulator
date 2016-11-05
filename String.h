#include "Variable.h"
#include "Numeric.h"
#include "Char.h"

class String : public Variable {
private:
	string name;
	string value;

public:
	String(string p_name = "", string p_value = "");
	~String();
	string getValue();
	void setStrChar(Numeric index, Char ch);
	void getStrChar(Numeric index, Char ch);
};