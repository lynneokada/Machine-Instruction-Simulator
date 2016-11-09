#include "Math.h"
using namespace std;

// How to possibly feed in list/array of objects as parameters (not vector) - not likely without weird stuff
// How to convert primitives to objects and determine correct type - can implicitly convert to Math type for operations
// Detect if object of non-working type is being used as paramter of function and catch error
// Pass in vector of Math objects as parameter for function - need to dynamic_cast
// Make sure we can pass vector of base level objects even when instantiated as child objects - upcast/downcast


//Dynamic cast as type and make type a variable of each object

Math::Math(std::string p_name, double p_value):name(p_name),value(p_value) 
{
	type = "Math";
};

Math::~Math() {}

void Math::out()
{
	//what actually goes in here?
	printf("%f\n", value);
}

void Math::sub(std::vector<string> names, std::map<string, Math*> map)
{
	value = decltype(value)((map[names[0]])->getValue() - map[names[1]]->getValue());
}

void Math::div(std::vector<string> names, std::map<string, Math*> map)
{
	value = decltype(value)((map[names[0]])->getValue()/map[names[1]]->getValue());
}



// template <typename T>
// void assign(T param)
// {
// 	//maybe should make Math::setValue assign rather than other way round
// 	if(getType() == "Numeric")
// 		value = (int)param->getValue();
// 	else
// 		value = (double)param->getValue();
// }

void Math::add(std::vector<string> names, std::map<string, Math*> map)
{
	cout << "Math::add" << endl;
	decltype(value) sum = 0;
	for (unsigned int i = 0; i < names.size(); ++i)
	{
		cout << "loop i: " << i << endl;
		sum += map[names[i]]->getValue();
	}
	value = sum;
	cout << "Math::add finish" << endl;
	cout << value << endl;
}

void Math::mul(std::vector<string> names, std::map<string, Math*> map)
{
	decltype(value) product = 0;
	for (unsigned int i = 0; i < names.size(); ++i)
	{
		product *= map[names[i]]->getValue();
	}
	value = product;
}

double Math::getValue()
{
	return value;
}

void Math::setValue(std::vector<string> names, std::map<string, Math*> map)
{	
	// value = map[names[0]]->getValue();
}

void Math::setValue(double val)
{
	cout << "Math::setValue double: " << val << endl;
	// Math *casted = dynamic_cast<Math*>(&test);
	value = val;
	cout << value << endl;
}

void Math::setValue(int val)
{
	cout << "Math::setValue int: " << val <<  endl;
	value = val;
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
