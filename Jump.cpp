#include "Jump.h"
#include <iostream>

using namespace std;
//Make sure same label doesnt map to different line numbers
//Refactor if-else blocks to function pointers or something else
//Check if bad value is passed to map and catch error for Jump and instructions
//Change Jump to operator overloading


typedef int(Jump::*single)(Math*);
typedef int(Jump::*dual)(Math*, Math*);

std::map<std::string, single> jumpSingle;
std::map<std::string, dual> jumpDual;


Jump::Jump()
{
	jumpSingle["JMPZ"] = &Jump::zero;
	jumpSingle["JMPNZ"] = &Jump::notZero;
	jumpDual["JMPGT"] = &Jump::greater;
	jumpDual["JMPGTE"] = &Jump::greaterEqual;
	jumpDual["JMPLT"] = &Jump::less;
	jumpDual["JMPLTE"] = &Jump::lessEqual;
};

Jump::~Jump() {};


template <typename T>
int Jump::zero(T var)
{
	return (var)->getValue() == 0 ? 1 : -1;
}

template <typename T>
int Jump::notZero(T var)
{
	return (var)->getValue() != 0 ? 1 : -1;
}

template <typename T, typename W>
int Jump::greater(T varA, W varB)
{
	return (varA)->getValue() > varB->getValue() ? 1 : -1;
}

template <typename T, typename W>
int Jump::less(T varA, W varB)
{
	return (varA)->getValue() < varB->getValue() ? 1 : -1;
}

template <typename T, typename W>
int Jump::greaterEqual(T varA, W varB)
{
	return (varA)->getValue() >= varB->getValue() ? 1 : -1;
}

template <typename T, typename W>
int Jump::lessEqual(T varA, W varB)
{
	return (varA)->getValue() <= varB->getValue() ? 1 : -1;
}


//CHECK FOR MAP.END() BEFORE GOING THROUGH CHECK
int Jump::compare(vector<string> names, string type, map<string, Math*> variables)
{
	if(names.size() == 1)
	{
		return labels[names[0]];
	}

	if(names.size() == 2)
	{
		Math * param1 = variables[(names[1])];
		if(variables.find(names[1]) != variables.end()) //check if first variable exists
		{	if((this->*jumpSingle[type])(param1) == 1)
			{
				return labels[names[0]];
			}
		}
	}

	if(names.size() == 3)
	{
		if((variables.find(names[1]) != variables.end()) && (variables.find(names[2]) != variables.end())) //check if both variables exist
		{
			Math * param1 = variables[(names[1])];
			Math * param2 = variables[(names[2])];
			if((this->*jumpDual[type])(param1, param2) == 1)
			{
				return labels[names[0]];
			}
		}
	}

	return -2; 	//condition caused an error
}

void Jump::storeLabel(string name, int lineNum)
{
	labels[name] = lineNum;
	cout << labels["LAB1"] << endl;
}