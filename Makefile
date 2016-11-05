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
main: Math.o Real.o Numeric.o Variable.o
	$(GPP) $(GPPFLAGS) Variable.o Math.o Real.o Numeric.o -o main

#Compilation commands:
Variable.o: Variable.cpp
	$(GPP) $(GPPFLAGS) -c Variable.cpp -o Variable.o

Math.o: Math.cpp
	$(GPP) $(GPPFLAGS) -c Math.cpp -o Math.o

Real.o: Real.cpp
	$(GPP) $(GPPFLAGS) -c Real.cpp -o Real.o

Numeric.o: Numeric.cpp
	$(GPP) $(GPPFLAGS) -c Numeric.cpp -o Numeric.o

#make clean
clean:
	rm -f *.exe
	rm -f *.o

%.o: %.cc
	g++ -c $< -o $@