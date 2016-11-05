#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <array>
#include <map>
#include "Numeric.h"
#include "Char.h"
#include "String.h"
#include "Real.h"

class Mis {
public:
	Mis();	// constructor
	void instruction(string instruction_type);
	~Mis();	// destructor
};