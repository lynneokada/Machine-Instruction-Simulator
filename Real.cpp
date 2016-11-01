#include "Real.h"

Real::Real(string name, string value):
	name(name), value(value)
{
}

double getValue() {
	return std::stof(this.value);
}