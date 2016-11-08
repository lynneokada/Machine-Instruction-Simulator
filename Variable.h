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
	string val;
	string type;
public:
	string getName();
	void sleep(int sec);
	virtual string getType();
	string getStringValue();
	// template <typename T> void setValue(T val);
	virtual void out();
	void setValue(char value);
	void setValue(string value);
};

#endif