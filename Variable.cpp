#include "Variable.h"

string Variable::getName() {
	return name;
}

template <typename T>
void Variable::setValue(T val) {
	value = val;
}

string Variable::getStringValue() {
	return value;
}

void Variable::sleep(int sec) {
	this_thread::sleep_for(chrono::seconds(sec));
}

void Variable::out() {
	cout << getStringValue() << endl;
}