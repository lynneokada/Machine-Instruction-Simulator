#include "Jump.h"
using namespace std;
//Make sure same label doesnt map to different line numbers

// int Jump::jumpTo(string name)
// {
// 	return labels[name]
// }



//-1 return means an error occurred with finding the type of Jump instruction
//-2 means conditional is not true so no jump occurs
int Jump::compare(vector<string> names, string type, map<string, Variable*> variables)
{
	std::string z = "Z";
	switch(std::stoi(type))
	{
		// case std::stoi(z):
		// 	if(variables[names[1]] == 0)
		// 		return labels[names[0]];
		// 	else
		// 		return -2;
		// case stoi("NZ"):
		// 	if(variables[names[1]] != 0)
		// 		return labels[names[0]];
		// 	else
		// 		return -2;
		// case stoi("GT"):
		// 	if(variables[names[1]] > variables[names[1]])
		// 		return labels[names[0]];
		// 	else
		// 		return -2;
		// case stoi("GTE"):
		// 	if(variables[names[1]] >= variables[names[1]])
		// 		return labels[names[0]];
		// 	else
		// 		return -2;
		// case stoi("LT"):
		// 	if(variables[names[1]] < variables[names[1]])
		// 		return labels[names[0]];
		// 	else
		// 		return -2;
		// case stoi("LTE"):
		// 	if(variables[names[1]] <= variables[names[1]])
		// 		return labels[names[0]];
		// 	else
		// 		return -2;
		// case stoi(""):
		// 	return labels[names[0]];
		// default:
		// 	return -1;
	}
	return -1;
}

void Jump::storeLabel(string name, int lineNum)
{
	labels[name] = lineNum;
}