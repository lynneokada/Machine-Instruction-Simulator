#include "String.h"

// constructor
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
		cerr << "size does not match actual length" << endl;
		exit(EXIT_FAILURE);
	}
	type = "String";
};

// destructor
String::~String() {};

// returns the value of this object
string String::getValue() {
	return this->value;
}

// set the character of this object's string value at
// the given index to the given character
void String::setStrChar(Math* index, Char *ch) {
	int i = index->getValue();

	if (i < this->size && i >= 0) {
		value[i] = ch->getValue();
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

// set the given character to the character at the given
// index of this object's string
void String::getStrChar(Math* index, Char *ch) {
	int i = index->getValue();

	if (i < this->size && i >= 0) {
		ch->setValue(this->value[i]);
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

// print out this object's value
void String::out() {
	cout << value << endl;
}

// set this object's value to the string specified by val
void String::setValue(string val) {

	value = val;
	cout << "setValue" << endl;
}