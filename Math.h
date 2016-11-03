#include <typeinfo>
#include <vector>
#include <stdlib.h>
#include "Variable.h"

class Math : public Variable
{
	private:
	public:
		std::string name;
		int value;
		Math();
		Math(std::string p_name, double p_value);
		virtual ~Math();
		template <typename T> void add(T list);
		template <typename T, typename W> void sub(T b, W c);
		template <typename T> void mul(T list);
		template <typename T, typename W> void div(T b, W c);
		template <typename T> void assign(T b);
		void sleep(int seconds);
		virtual void out();
};