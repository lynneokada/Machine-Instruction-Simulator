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

void Variable::sleep(int sec) {
	this_thread::sleep_for(chrono::seconds(sec));
}

void Variable::out() {
	cout << getStringValue() << endl;
	//outfile << this->value << endl;
}