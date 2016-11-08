#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include "Math.h"

class Jump
{
	private:
		std::map<string, int> labels;
	public:
		Jump();
		~Jump();
		void storeLabel(string names, int lineNum);
		int compare(vector<string> names, string type, map<string, Math*> variables);
		template <typename T> int zero(T var);
		template <typename T> int notZero(T var);
		template <typename T, typename W> int greater(T varA, W varB);
		template <typename T, typename W> int less(T varA, W varB);
		template <typename T, typename W> int greaterEqual(T varA, W varB);
		template <typename T, typename W> int lessEqual(T varA, W varB);
}; 