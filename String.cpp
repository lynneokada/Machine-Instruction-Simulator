#include "String.h"

String::String(string p_name, string p_value):name(p_name), value(p_value)
{
	type = "String";
	std::cout << "String created" << std::endl;
};

String::~String() {};

string String::getValue() {
	return this->value;
}

void String::setStrChar(Math* index, Char &ch) {
	int i = index->getValue();

	if (i < this->value.length() && i >= 0) {
		this->value[i] = ch.getValue();
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

void String::getStrChar(Math* index, Char &ch) {
	int i = index->getValue();

	if (i < this->value.length() && i >= 0) {
		cout << this->value[i] << endl;
		ch.setValue(this->value[i]);
		cout << ch.getValue() << " test" << endl;
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

// int main() {
// 	printf("test\n");
// 	String *str = new String("$var1", "testing123");

// 	Math* index = new Math("$var2", 3);
// 	Char ch("$var3", 'T');
// 	Math* index2 = new Math("$var4", 5);

// 	str->setStrChar(index, ch);
// 	cout << str->getValue() << endl;

// 	str->getStrChar(index2, ch);
// 	cout << ch.getValue() << endl;

// 	cout << str->getValue() << endl;

// 	cout << ch.getValue() << endl;
// 	cout << str->getValue()[index2->getValue()] << endl;
// 	str->getStrChar(index2, ch);
// 	cout << ch.getValue() << endl;

// 	ch.setValue('S');
// 	cout << ch.getValue() << endl;

// }