#include <string>
#include <iostream>
#include <stdlib.h>
#include <thread> //for the sleep function
#include <chrono> //for the sleep function

using namespace std;

// using std::string;

class Variable {

protected:
	string name;
	string value;

public:
	string getName();
	string getStringValue();
	// auto getValue(auto val);
	template <typename T> void setValue(T val);
	virtual void out();
};