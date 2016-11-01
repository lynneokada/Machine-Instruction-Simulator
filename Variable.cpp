#include "Variable.h"

string Variable::getName() {
	return name;
}

void Variable::setValue(string str) {
	this->value = str;
}

string Variable::getStringValue() {
	return this->value;
}

void Variable::out() {
	std::cout << this->getStringValue() << std::endl;
}