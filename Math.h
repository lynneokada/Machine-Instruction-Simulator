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
		double sub(std::vector<string> names, std::map<string, Math*> map);
		void mul(std::vector<string> names, std::map<string, Math*> map);
		void div(std::vector<string> names, std::map<string, Math*> map);
		virtual void out();
		virtual double getValue();
		virtual void setValue(double val);
		virtual void setValue(int val);
		//can use template for function params but still needs to return 
};

#endif