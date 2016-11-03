#include <string>
#include "Math.h"

class Real : public Math {

public:
	// string name;
	string name;
	double value;
	Real(std::string p_name, double p_value);
	Real();
	~Real();
	double getValue();
}