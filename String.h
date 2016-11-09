#include "Variable.h"
#include "Numeric.h"
#include "Char.h"

class String : public Variable {
private:
	string name;
	int size;
	char value[size];
public:
	String(string p_name = "", string p_value = "", int p_size = 0);
	~String();
	string getValue();
	void setStrChar(Math* index, Char *ch);
	void getStrChar(Math* index, Char *ch);
};