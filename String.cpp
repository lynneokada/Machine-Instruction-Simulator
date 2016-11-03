#include "String.h"

String::String(string p_name, string p_value):name(p_name), value(p_value){};

String::~String() {

};

string String::getValue() {
	return this->value;
}

int main() {
	String *str = new String();

	cout << str->getValue() << endl;
}