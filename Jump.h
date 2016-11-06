#include <map>
#include <string>
#include <vector>
#include "Variable.h"

class Jump
{
	private:
		std::map<string, int> labels;
	public:
		// int jumpTo(string name);
		void storeLabel(string names, int lineNum);
		int compare(vector<string> names, string type, map<string, Variable*> variables);
}; 