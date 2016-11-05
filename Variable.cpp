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

// auto Variable::getValue(auto val) {
// 	return value;
// }

void Variable::out() {
	cout << getStringValue() << endl;
}