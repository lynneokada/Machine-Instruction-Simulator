#include "Char.h"

// constructor
Char::Char(string p_name, char p_value):name(p_name), value(p_value)
{
	type = "Char";
	std::cout << "Char created" << std::endl;
};

// destructor
Char::~Char() {};

// returns the value of this object
char Char::getValue() {
	return this->value;
}

// set the value of this object to the character val
void Char::setValue(char val) {
	this->value = val;
}