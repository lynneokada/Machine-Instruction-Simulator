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
	template <typename T, typename W> void setStrChar(T index, W &ch);
	template <typename T, typename W> void getStrChar(T index, W &ch);
};