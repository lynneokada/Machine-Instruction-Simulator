#include <iostream>
#include <string>
#include <typeinfo>

// Operator() overload to return value of the object or int
// Implicit constructor constructor from primitive to object
// Use enableif to check types
// Printout in implicit




// How to possibly feed in list/array of objects as parameters (not vector)
// How to convert primitives to objects and determine correct type
// Detect if object of non-working type is being used as paramter of function and catch error
// Pass in vector of VAR objects as parameter for function
// Make sure we can pass vector of base level objects even when instantiated as child objects
// 	Look up OOP C++ vector

class Math
{
	private:
	public:
		int value = 0;
		Math(int a = 0)
		{
			value = a;
		};
		~Math(){};
		template <typename T, typename W> void sub(T b, W c);
		template <typename T, typename W> void div(T b, W c);
		template <typename T> void assign(T b);
		void out();
};

		void Math::out()
		{
			std::cout << this->value << std::endl;
		}
		
		template <typename T, typename W>
		void Math::sub(T b, W c)
		{
			this->value = (decltype(this))(b.getValue() - c.getValue());
		}

		template <typename T, typename W>
		void Math::div(T b, W c)
		{
			// this->setValue(b.value/c.value);
		}

		template <typename T>
		void Math::assign(T b)
		{
			this->value = b.value;
		}


int main()
{
	Math a;
	Math b(23);
	Math c(1);
	int myint = 12;
	int tryint = 1;

	a.sub(b, Math(6));

	Math test;
	test.out();

	// setting function pointer
	void (Math::*pSub)(auto, auto);
	pSub = &Math::sub;
	(test.*pSub)(myint, tryint);

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