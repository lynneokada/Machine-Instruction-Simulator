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
	void setStrChar(Math* index, Char &ch);
	void getStrChar(Math* index, Char &ch);
};