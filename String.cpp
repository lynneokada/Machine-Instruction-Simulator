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

template <typename T, typename W>
void String::setStrChar(T index, W &ch) {
	int i = index.getValue();



	if (i < this->value.length() && i >= 0) {
		this->value[i] = ch.getValue();
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

template <typename T, typename W>
void String::getStrChar(T index, W &ch) {
	int i = index.getValue();

	Char *castCh = dynamic_cast<Char*>(&ch);

	if (i < this->value.length() && i >= 0) {
		cout << this->value[i] << endl;
		castCh->setValue(this->value[i]);
		cout << castCh->getValue() << " test" << endl;
	} else {
		cout << "Error: index out of range - index " << i 
		<< " in string " << this->getValue() << endl;
	}
}

// int main() {
// 	String *str = new String();


// 	String str("$var1", "testing123");
// 	Numeric index("$var2", 3);
// 	Char ch("$var3", 'T');
// 	Numeric index2("$var4", 5);

// 	str.setStrChar(index, ch);
// 	cout << str.getValue() << endl;

// 	str.getStrChar(index2, ch);
// 	cout << ch.value << endl;

// 	cout << str.getValue() << endl;

// 	cout << ch.getValue() << endl;
// 	cout << str.getValue()[index2.getValue()] << endl;
// 	str.getStrChar(index2, ch);
// 	cout << ch.getValue() << endl;

// 	ch.setValue('S');
// 	cout << ch.getValue() << endl;

// }