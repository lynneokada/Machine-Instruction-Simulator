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
		void add(std::vector<string> names, std::map<string, Math*> map);
		void sub(std::vector<string> names, std::map<string, Math*> map);
		void mul(std::vector<string> names, std::map<string, Math*> map);
		void div(std::vector<string> names, std::map<string, Math*> map);
		virtual void out();
		virtual double getValue();
		void setValue(std::vector<string> names, std::map<string, Math*> map);
		void setValue(int value);
		void setValue(double val, Math &test);
		//can use template for function params but still needs to return 
};

#endif