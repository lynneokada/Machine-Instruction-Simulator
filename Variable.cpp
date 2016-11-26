#include "Variable.h"

// returns the name of this object stored in
// the name attribute
string Variable::getName() {
	return name;
}

// returns the type of this object stored in
// the type attribute
string Variable::getType() {
	return this->type;
}

// returns the value of this object
string Variable::getStringValue() {
	return val;
}

// prints out the value of this object
void Variable::out() {
	cout << getStringValue() << endl;
	//outfile << this->value << endl;
}

// sets teh value of this object to the char value
void Variable::setValue(char value)
{
	this->val = value;
}

// sets the value of this object to the string value
void Variable::setValue(string value)
{
	this->val = value;
}

void Variable::lock(int id)
{
	mtx.lock();
	owner = id;
}

void Variable::unlock(int id)
{
	if(locked != false)
	{
		if(owner == id)
		{
			mtx.unlock();
			owner = 0; //0 will represent null, counter for threads starts at 1
		}
	}
}