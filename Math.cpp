#include "Math.h"
using namespace std;

// How to possibly feed in list/array of objects as parameters (not vector) - not likely without weird stuff
// How to convert primitives to objects and determine correct type - can implicitly convert to Math type for operations
// Detect if object of non-working type is being used as paramter of function and catch error
// Pass in vector of Math objects as parameter for function - need to dynamic_cast
// Make sure we can pass vector of base level objects even when instantiated as child objects - upcast/downcast


// constructor
Math::Math(std::string p_name, double p_value):name(p_name),value(p_value) 
{
	type = "Math";
};

// destructor
Math::~Math() {}

// print value of this object
void Math::out()
{
	printf("%f\n", value);
}

// subtraction function that takes in a vector of the names of the parameters,
// as well as the map of currently existing Math variables from their name
// to their object. Then it performs subtraction on the two objects specified
// by names. The result is stored in the value parameter of the object calling
// this function
void Math::sub(std::vector<string> names, std::map<string, Math*> map)
{
	value = decltype(value)((map[names[0]])->getValue() - map[names[1]]->getValue());
}

// division function that takes in a vector of the names of the parameters,
// as well as the map of currently existing Math variables from their name
// to their object. Then it performs division on the two objects specified
// by names. The result is stored in the value parameter of the object calling
// this function
void Math::div(std::vector<string> names, std::map<string, Math*> map)
{
	value = decltype(value)((map[names[0]])->getValue()/map[names[1]]->getValue());
}

// addition function that takes in a vector of the names of the parameters,
// as well as the map of currently existing Math variables from their name
// to their object. Then it performs addition on the objects (1-12) specified
// by names. The result is stored in the value parameter of the object calling
// this function
void Math::add(std::vector<string> names, std::map<string, Math*> map)
{
	decltype(value) sum = 0;
	for (unsigned int i = 0; i < names.size(); ++i)
	{
		sum += map[names[i]]->getValue();
	}
	value = sum;
}

// multiplication function that takes in a vector of the names of the parameters,
// as well as the map of currently existing Math variables from their name
// to their object. Then it performs multiplication on the objects (1-12) specified
// by names. The result is stored in the value parameter of the object calling
// this function
void Math::mul(std::vector<string> names, std::map<string, Math*> map)
{
	decltype(value) product = 0;
	for (unsigned int i = 0; i < names.size(); ++i)
	{
		product *= map[names[i]]->getValue();
	}
	value = product;
}

// returns the value of this object
double Math::getValue()
{
	return value;
}

// sets the value of a Real object to val
void Math::setValue(double val)
{
	value = val;
}

void Math::setValue(int val)
{
	value = val;
}

