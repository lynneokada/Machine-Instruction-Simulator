#include "Numeric.h"


Numeric::Numeric(std::string p_name, int p_value):name(p_name), value(p_value){};

Numeric::~Numeric()
{

};

// Numeric::Numeric(string name, string value):
// 	name(name), value(value){}

int Numeric::getValue() {
	return this->value;
}
