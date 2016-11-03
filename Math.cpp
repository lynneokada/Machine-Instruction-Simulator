#include "Math.h"
using namespace std;
// Operator() overload to return value of the object or int
// Implicit constructor constructor from primitive to object
// Use enableif to check types
// Printout in implicit


// How to possibly feed in list/array of objects as parameters (not vector) - not likely without weird stuff
// How to convert primitives to objects and determine correct type - can implicitly convert to Math type for operations
// Detect if object of non-working type is being used as paramter of function and catch error
// Pass in vector of Math objects as parameter for function - need to dynamic_cast
// Make sure we can pass vector of base level objects even when instantiated as child objects - upcast/downcast

Math::Math(std::string p_name, double p_value):name(p_name),value(p_value)
{
};

Math::Math()
{
	name = "";
	value = 0.0;
};

Math::~Math()
{
}

void Math::out()
{
	cout << this->value << endl;
}

template <typename T, typename W>
void Math::sub(T b, W c)
{
	this->value = (decltype(this->value))(b.value - c.value);
}

template <typename T, typename W>
void Math::div(T b, W c)
{
	this->value = (b.value / c.value);
}

template <typename T>
void Math::assign(T b)
{
	this->value = b.value;
}

// Needs to be a VAR function
void Math::sleep(int sec)
{
	this_thread::sleep_for(chrono::seconds(sec));
}

template <typename T>
void Math::add(T list)
{
	int sum = 0;
	for (int i = 0; i < list.size(); i++)
    {
    	sum += list[i].value;
    }
    this->value = sum;
}

template <typename T>
void Math::mul(T list)
{
	int product = 0;
	for (int i = 0; i < list.size(); i++)
    {
    	product *= list[i].value;
    }
    this->value = product;
}

int main()
{

	
	Math a;
	Math b("test", 23);
	// Math c(1);
	// int test1 = 12;
	// int test2 = 1;

	// Math test;
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

	// std::vector<Math> m;
	// m.push_back(test);
	// m.push_back(b);
	// m[1].out();

	// // std::vector<Variable> v;
	// // Variable test3;
	// Math * pMath = new Math(100);


	// auto myTuple = make_tuple("Foo", 1337, 42, b);


	// cout << get<0>(myTuple) << endl; // Access element by index: "Foo"
	// cout << get<1>(myTuple) << endl; // Access element by index: 1337
	// cout << get<2>(myTuple) << endl; // Access element by index: 42
	// get<3>(myTuple).out();

	// auto myTuple = tuple_cat(myTuple, make_tuple(c));
	// get<4>(myTuple).out();
	return 0;
}
