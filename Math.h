#include <typeinfo>
#include <vector>
#include <stdlib.h>
#include "Variable.h"

class Math
{
	private:
	public:
		int value = 0;
		Math(int a);
		~Math();
		template <typename T, typename W> void sub(T b, W c);
		template <typename T, typename W> void div(T b, W c);
		template <typename T> void assign(T b);
		void sleep(int seconds);
		void out();
};