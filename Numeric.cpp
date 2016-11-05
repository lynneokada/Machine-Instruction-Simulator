#include "Numeric.h"

Numeric::Numeric(std::string p_name, int p_value):name(p_name), value(p_value){};

Numeric::~Numeric(){};

int Numeric::getValue() {
	return this->value;
}

void Numeric::out()
{
	std::cout << getValue() << std::endl;
}

// int main()
// {
// 	Numeric *a = new Numeric("test", 12.0);

// 	Variable *b = dynamic_cast<Variable*>(a);
// 	Variable c;

// 	a->out();

// 	b->out();
// 	c.out();


// 	delete(a);

// 	return 0;
// }