#include <string>
#include "Math.h"

class Numeric : public Math 
{
	private:
		std::string name;
		int value;
	public:
		Numeric(std::string p_name="", int p_value=0);
		~Numeric();
		int getValue();
		void out();
};