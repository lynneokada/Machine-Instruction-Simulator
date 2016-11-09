#include "Char.h"

Char::Char(string p_name, char p_value):name(p_name), value(p_value)
{
	type = "Char";
	std::cout << "Char created" << std::endl;
};

Char::~Char() {};

char Char::getValue() {
	return this->value;
}

void Char::setValue(char val) {
	this->value = val;
}