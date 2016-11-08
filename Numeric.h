#ifndef __NUMERIC_H_
#define __NUMERIC_H_

#include "Math.h"

class Numeric : public Math 
{
	private:
		std::string name;
		int value;
	public:
		Numeric(std::string p_name="", int p_value=0);
		~Numeric();
		void out();
};

#endif