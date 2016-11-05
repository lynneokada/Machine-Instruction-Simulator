#ifndef __VAR_H_
#define __VAR_H_

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
	void sleep(int sec);
	string getStringValue();
	template <typename T> void setValue(T val);
	virtual void out();
};

#endif