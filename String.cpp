#include "String.h"

String::String(string p_name, string p_value):
	name(p_name), value(p_value){};

String::~String() {};

string String::getValue() {
	return this->value;
}

void setStrChar(Variable index, Variable ch) {
	int i = index->getValue();

	if (i < this->value.length() && i >= 0) {
		this->value[i] = ch->getValue();
	} else {
		printf("Error: index out of range - index %d in string %s\n",
			   i, this->getValue());
	}
}

void getStrChar(Variable index, Variable ch) {
	int i = index->getValue();

	if (i < this->value.length() && i >= 0) {
		ch->setValue(this->value[i]);
	} else {
		printf("Error: index out of range - index %d in string %s\n",
			   i, this->getValue());
	}
}

// int main() {
// 	String *str = new String();

// 	str->out();
// }