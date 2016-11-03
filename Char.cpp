#include "Char.h"

Char::Char(string p_name, char p_value):
	name(p_name), value(p_value){};

Char::~Char() {};

char Char::getValue() {
	return this->value;
}

void Char::setValue(char val) {
	this->value = val;
}


// int main() {
// 	Char *ch = new Char();

// 	ch->setValue('X');
// 	cout << ch->getValue() << endl;
// }