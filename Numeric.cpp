#include "Numeric.h"


Numeric::Numeric(std::string p_name = "", int p_value=0):name(p_name), value(p_value){};

Numeric::Numeric()
{
	name = "";
	value = 0;
};

Numeric::~Numeric()
{

};

// Numeric::Numeric(string name, string value):
// 	name(name), value(value){}

int Numeric::getValue() {
	return this->value;
}
