#include "Math.h"

class Real : public Math {

private:
	string name;
	double value;
public:
	Real(std::string p_name = "", double p_value = 0.0);
	~Real();
	double getValue();
	void out();
	void setValue(double val);
};