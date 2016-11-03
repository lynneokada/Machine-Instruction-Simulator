#include "Real.h"

Real::Real(std::string p_name = "", double p_value = 0.0):name(p_name), value(p_value){};
Real::Real()
{
	name = "";
	value = 0.0;
};

Real::~Real(){};

double Real::getValue()
{
	return value;
}