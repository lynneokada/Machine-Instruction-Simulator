# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#	Makefile for Unix & Linux Systems	#
#	using a GNU C++ compiler	#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# compiler flags
#	-g	--Enable debugging
#	-Wall	--Turn on all warnings
#	-D_USE_FIXED_PROTOTYPES_
#	--Force the compiler to use the correct headers
#	-ansi	--Don't use GNU ext; do use ansi standard.

GPP = g++ -std=c++14
GPPFLAGS = -O3 -Wall

all: main

#Link command:
main: Math.o Real.o Numeric.o Variable.o String.o Char.o mis.o
	$(GPP) $(GPPFLAGS) Variable.o Math.o Real.o Numeric.o String.o Char.o mis.o -o main

#Compilation commands:
Variable.o: Variable.cpp
	$(GPP) $(GPPFLAGS) -c Variable.cpp -o Variable.o

Math.o: Math.cpp
	$(GPP) $(GPPFLAGS) -c Math.cpp -o Math.o

Real.o: Real.cpp
	$(GPP) $(GPPFLAGS) -c Real.cpp -o Real.o

Numeric.o: Numeric.cpp
	$(GPP) $(GPPFLAGS) -c Numeric.cpp -o Numeric.o

String.o: String.cpp
	$(GPP) $(GPPFLAGS) -c String.cpp -o String.o


Char.o: Char.cpp
	$(GPP) $(GPPFLAGS) -c Char.cpp -o Char.o


mis.o: mis.cpp
	$(GPP) $(GPPFLAGS) -c mis.cpp -o mis.o


#make clean
clean:
	rm -f *.exe
	rm -f *.o

%.o: %.cc
	g++ -c $< -o $@