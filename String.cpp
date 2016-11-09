#include "String.h"

String::String(string p_name, string p_value, int p_size):name(p_name), size(p_size)
{
	if(p_value.length <= p_size)
	{
		for(int i = 0; i < p_value.length; i++)
		{
			
		}
	{
	else
		//throw some sort of error here
	type = "String";
	std::cout << "String created" << std::endl;
};

String::~String() {};

string String::getValue() {
	return this->value;
}

void String::setStrChar(Math* index, Char *ch) {
	cout << "ch value: " << ch->getValue() << endl;
	int i = index->getValue();

	if (i < this->size && i >= 0) {
		value[i] = ch->getValue();
		cout << "this value is now: " << this->value << endl;
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

void String::getStrChar(Math* index, Char *ch) {
	int i = index->getValue();

	if (i < this->size && i >= 0) {
		// cout << this->value[i] << endl;
		ch->setValue(this->value[i]);
		// cout << ch->getValue() << " test" << endl;
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