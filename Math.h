#ifndef __MATH_H_
#define __MATH_H_

#include <typeinfo>
#include <vector>
#include <stdlib.h>
#include "Variable.h"
#include <map>

class Math : public Variable
{
	private:
		std::string name;
		double value;
	public:
		Math(std::string p_name = "", double p_value= 0.0);
		virtual ~Math();
		void add(std::vector<string> names, std::map<string, Variable*> map);
		void sub(std::vector<string> names, std::map<string, Variable*> map);
		void mul(std::vector<string> names, std::map<string, Variable*> map);
		void div(std::vector<string> names, std::map<string, Variable*> map);
		template <typename T> void assign(T b);
		virtual void out();
		double getValue();
};

#endif