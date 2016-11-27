#ifndef __VAR_H_
#define __VAR_H_

#include <string>
#include <iostream>
#include <stdlib.h>
#include <thread> //for the sleep function
#include <chrono> //for the sleep function
#include <mutex>
#include <atomic>

using namespace std;

// using std::string;

class Variable {

protected:
	string name;
	string val;
	string type;
	std::mutex mtx;
	std::atomic<bool> locked{false};
	std::atomic<int> owner;

public:
	string getName();
	virtual string getType();
	string getStringValue();
	virtual void out();
	void setValue(char value);
	void setValue(string value);
	void lock(int id);
	void unlock(int id);
};

#endif