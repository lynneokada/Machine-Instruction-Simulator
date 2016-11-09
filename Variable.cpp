#include "Variable.h"

string Variable::getName() {
	return name;
}

string Variable::getType() {
	return this->type;
}

// template <typename T>
// void Variable::setValue(T val) {
// 	value = val;
// }

string Variable::getStringValue() {
	return val;
}

void Variable::out() {
	cout << getStringValue() << endl;
	//outfile << this->value << endl;
}

void Variable::setValue(char value)
{
	cout << "Variable::setValue char" << endl;
	this->val = value;
}

void Variable::setValue(string value)
{
	cout << "Variable::setValue string" << endl;
	this->val = value;
}