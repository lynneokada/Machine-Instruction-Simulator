#include "String.h"

String::String(string p_name, string p_value, int max):name(p_name), size(max)
{
	if(p_value.length() <= max && max <= 256) {
		int diff = max - p_value.length();
		value = p_value;
		for (int i = 0; i < diff; ++i)
		{
			value.append(" ");
		}
	} else {
		std::cout << "Error: size does not match actual length" << endl;
		//throw some sort of error here
	}
	type = "String";
	std::cout << "String created" << std::endl;
};

String::~String() {};

string String::getValue() {
	return this->value;
}

void String::setStrChar(Math* index, Char *ch) {
	int i = index->getValue();

	if (i < this->size && i >= 0) {
		value[i] = ch->getValue();
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

void String::getStrChar(Math* index, Char *ch) {
	int i = index->getValue();

	if (i < this->size && i >= 0) {
		ch->setValue(this->value[i]);
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

void String::out() {
	cout << value << endl;
}

void String::setValue(string val) {

	value = val;
	cout << "setValue" << endl;
}