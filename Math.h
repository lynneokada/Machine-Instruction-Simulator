#include <typeinfo>
#include <vector>
#include <stdlib.h>
#include <map>

#include "Variable.h"

class Math : public Variable
{
	private:
		std::string name;
		double value;
	public:
		Math(std::string p_name = "", double p_value= 0.0);
		virtual ~Math();
		template <typename T, typename W> void add(T names, W map);
		template <typename T, typename W> void sub(T names, W map);
		template <typename T, typename W> void mul(T names, W map);
		template <typename T, typename W> void div(T names, W map);
		template <typename T> void assign(T b);
		void sleep(int seconds); //needs to be in Variable
		virtual void out();
};