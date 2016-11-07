#include "Jump.h"
using namespace std;
//Make sure same label doesnt map to different line numbers
//Refactor if-else blocks to function pointers or something else
//Check if bad value is passed to map and catch error for Jump and instructions
//Change Jump to operator overloading

std::map<std::string, Jump*> jumps;

// jumps["JUMP"] = new Variable();
// jumps["JUMPZ"] = new Math();
// jumps["JUMPNZ"] = new Numeric();
// jumps["JUMPGT"] = new Char();
// jumps["JUMPGTE"] = new String();
// jumps["REAL"] = new Real();


template <typename T>
int Jump::zero(T var)
{
	return (dynamic_cast<Math*>(var)->getValue() == 0 ? 1 : 0);
}

template <typename T>
int Jump::notZero(T var)
{
	return (dynamic_cast<Math*>(var)->getValue() != 0 ? 1 : 0);
}

template <typename T, typename W>
int Jump::greater(T varA, W varB)
{
	return (dynamic_cast<Math*>(varA)->getValue() > dynamic_cast<Math*>(varB)->getValue() ? 1 : 0);
}

template <typename T, typename W>
int Jump::less(T varA, W varB)
{
	return (dynamic_cast<Math*>(varA)->getValue() < dynamic_cast<Math*>(varB)->getValue() ? 1 : 0);
}

template <typename T, typename W>
int Jump::greaterEqual(T varA, W varB)
{
	return (dynamic_cast<Math*>(varA)->getValue() >= dynamic_cast<Math*>(varB)->getValue() ? 1 : 0);
}

template <typename T, typename W>
int Jump::lessEqual(T varA, W varB)
{
	return (dynamic_cast<Math*>(varA)->getValue() <= dynamic_cast<Math*>(varB)->getValue() ? 1 : 0);
}

int Jump::compare(vector<string> names, string type, map<string, Variable*> variables)
{
	// int (Jump::*pZero)(Math*);
	// pZero = &Jump::zero;
	// int answer = Jump::zero(variables[(names[1])]);
	if(names.size() == 2)
	{
		//CHECK FOR MAP.END() BEFORE GOING THROUGH CHECK
		if(variables.find(names[1]) != variables.end()) //check if first variable exists
		{	if(zero(variables[(names[1])]) == 1)
			{
				return labels[names[0]];
			}
		}
	}

	if(names.size() == 3)
	{
		if((variables.find(names[1]) != variables.end()) && (variables.find(names[2]) != variables.end())) //check if both variables exist
		{
			if(lessEqual(variables[(names[1])], variables[(names[2])]) == 1)
			{
				return labels[names[0]];
			}
		}
	}

	return 0; 	//condition does not hold true
}

void Jump::storeLabel(string name, int lineNum)
{
	labels[name] = lineNum;
}


// int main()
// {

// 	a.compare(v, type, map);
// 	return 0;
// }