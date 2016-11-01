#include "Functions.h"
// Operator() overload to return value of the object or int
// Implicit constructor constructor from primitive to object
// Use enableif to check types
// Printout in implicit




// How to possibly feed in list/array of objects as parameters (not vector) - not likely
// How to convert primitives to objects and determine correct type - can implicitly convert to Math type for operations
// Detect if object of non-working type is being used as paramter of function and catch error
// Pass in vector of VAR objects as parameter for function
// Make sure we can pass vector of base level objects even when instantiated as child objects
// 		Look up OOP C++ vector
// Make sure atoi works for strings/whatever we represent Char and String with

Math::Math(int a = 0)
{
	value = a;
}

Math::~Math()
{

};

void Math::out()
{
	std::cout << this->value << std::endl;
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
	std::this_thread::sleep_for(std::chrono::seconds(sec));
}


int main()
{
	Math a;
	Math b(23);
	Math c(1);
	int myint = 12;
	int tryint = 1;
	std::string test1 = "122";
	char tester = '1';
	int x = atoi(&tester);

	Math test;
	test.out();

	// setting function pointer
	void (Math::*pSub)(Math, Math);
	pSub = &Math::sub;
	(test.*pSub)(myint, tryint);
	test.out();

	test.sleep(5);
	// Math::sleep(12);


	void (Math::*pDiv)(Math, Math);
	pDiv = &Math::div;
	(test.*pDiv)(myint, tryint);
	test.out();

	// a.sub(b, c);
	std::cout << "Testing SUB of objects: " << "\n";
	a.out();

	std::cout << "Type is: " << typeid(b).name() << std::endl;

	// a.sub(b, 12);
	// std::cout << "Testing SUB of mixed types: " << "\n";
	// a.out();

	// a.sub(23, 1);
	// std::cout << "Testing SUB of ints: " << "\n";
	a.out();

	return 0;
}