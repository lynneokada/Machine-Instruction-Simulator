#include "Real.h"

// constructor
Real::Real(std::string p_name, double p_value):name(p_name), value(p_value)
{
	type = "Real";
	std::cout << "Real created" << std::endl;
};

// destructor
Real::~Real(){};

// returns the value of this object
double Real::getValue()
{
	return value;
}

// prints out the value of this object
void Real::out()
{
	printf("%f\n", value);
}

