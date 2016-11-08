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
	cout << "Change " << this->value << " to " << val <<endl;
	this->value = val;
	cout << "Value of " << this->name << " is now " << this->value << endl;
}

// int main() {
// 	Char *ch = new Char();

// 	ch->setValue('X');
// 	cout << ch->getValue() << endl;
// }