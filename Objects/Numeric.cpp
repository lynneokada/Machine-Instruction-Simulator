#include "Numeric.h"

Numeric::Numeric(string name, string value):
	name(name), value(value){}

int getValue() {
	return atoi(this.value);
}