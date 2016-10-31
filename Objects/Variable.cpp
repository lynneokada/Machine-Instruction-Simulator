#include "Variable.h"

string getName() {
	return name;
}

void setValue(string str) {
	this.value = str;
}

void getStringValue() {
	return this.value;
}

void out() {
	printf("%s", this.getStringValue());
}