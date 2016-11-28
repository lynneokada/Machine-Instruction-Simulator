#include "Numeric.h"

//Change constructor to take in two strings and stoi the value
Numeric::Numeric(std::string p_name, int p_value):name(p_name), value(p_value)
{
	cout << "numeric created\n";
	type = "Numeric";
	cout << "test\n";	
};

// Destructor
Numeric::~Numeric(){};

// returns the value of the Numeric object
double Numeric::getValue()
{
	return (double)value;
}

// prints out the value of this object
void Numeric::out()
{
	std::cout << value << std::endl;
}

void Numeric::setValue(int val)
{
	value = val;
}