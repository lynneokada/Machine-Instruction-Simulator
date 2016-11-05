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
%.o : %.cpp
	$(GPP) $(GPPFLAGS) -c $<
