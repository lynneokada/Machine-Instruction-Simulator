#include "Real.h"

Real::Real(std::string p_name, double p_value):name(p_name), value(p_value){};

Real::~Real(){};

double Real::getValue()
{
	return value;
}