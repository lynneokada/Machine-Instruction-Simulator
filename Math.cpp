#include "Math.h"
using namespace std;

// How to possibly feed in list/array of objects as parameters (not vector) - not likely without weird stuff
// How to convert primitives to objects and determine correct type - can implicitly convert to Math type for operations
// Detect if object of non-working type is being used as paramter of function and catch error
// Pass in vector of Math objects as parameter for function - need to dynamic_cast
// Make sure we can pass vector of base level objects even when instantiated as child objects - upcast/downcast


//Dynamic cast as type and make type a variable of each object

Math::Math(std::string p_name, double p_value):name(p_name),value(p_value) {};

Math::~Math() {}

void Math::out()
{
	//what actually goes in here?
	printf("%f\n", value);
}

void Math::sub(std::vector<string> names, std::map<string, Variable*> map)
{
	value = decltype(value)(dynamic_cast<Math*>(map[names[0]])->getValue()-dynamic_cast<Math*>(map[names[1]])->getValue());
}

void Math::div(std::vector<string> names, std::map<string, Variable*> map)
{
	value = decltype(value)(dynamic_cast<Math*>(map[names[0]])->getValue()/dynamic_cast<Math*>(map[names[1]])->getValue());
}

template <typename T>
void Math::assign(T b)
{
	//maybe should make Math::setValue assign rather than other way round
	this->setValue(b.getValue);
}

void Math::add(std::vector<string> names, std::map<string, Variable*> map)
{
	decltype(value) sum = 0;
	for (int i = 0; i < names.size(); ++i)
	{
		sum += dynamic_cast<Math*>(map[names[i]])->getValue();
	}
	value = sum;
}

void Math::mul(std::vector<string> names, std::map<string, Variable*> map)
{
	decltype(value) product = 0;
	for (int i = 0; i < names.size(); ++i)
	{
		product *= dynamic_cast<Math*>(map[names[i]])->getValue();
	}
	value = product;
}

double Math::getValue()
{
	return this->value;
}

// int main()
// {

	
// 	Math a;
// // 	Math b("test", 23);
// // 	// Math c(1);
// // 	// int test1 = 12;
// // 	// int test2 = 1;

// 	Math test;
// 	test.sub(a, a);
// test.out();	

// // setting function pointer
// void (Math::*pSub)(Math, Math);
// pSub = &Math::sub;
// (test.*pSub)(test1, test2);
// test.out();

// void (Math::*pDiv)(Math, Math);
// pDiv = &Math::div;
// (test.*pDiv)(test1, test2);
// test.out();


// 	return 0;
// }
