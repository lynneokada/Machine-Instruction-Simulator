#include "String.h"

String::String(string p_name, string p_value):
	name(p_name), value(p_value){};

String::~String() {};

string String::getValue() {
	return this->value;
}

// template <typename T, typename W>
void String::setStrChar(Numeric index, Char ch) {
	int i = index.getValue();



	if (i < this->value.length() && i >= 0) {
		this->value[i] = ch.getValue();
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

// template <typename T, typename W>
void String::getStrChar(Numeric index, Char ch) {
	int i = index.getValue();

	if (i < this->value.length() && i >= 0) {
		ch.setValue(this->value[i]);
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

// int main() {
// 	String *str = new String();

// 	str->out();
// }