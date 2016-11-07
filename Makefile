# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
#	Makefile for Unix & Linux Systems	#
#	using a GNU C++ compiler	#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 

# compiler flags
#	-g	--Enable debugging
#	-Wall	--Turn on all warnings
#	-D_USE_FIXED_PROTOTYPES_
#	--Force the compiler to use the correct headers
#	-ansi	--Don't use GNU ext; do use ansi standard.

GPP = g++ -std=c++14
GPPFLAGS = -O3 -Wall

all : main

#Link command:
main : mis.o Variable.o Math.o String.o Char.o Numeric.o Real.o Jump.o
	$(GPP) $(GPPFLAGS) mis.o Variable.o Math.o String.o Char.o \
	Numeric.o Real.o Jump.o -o main

#Compilation commands:
%.o : %.cpp
	$(GPP) $(GPPFLAGS) -c $<

clean :
	- rm *.o main 

# Dependencies

mis.o: mis.cpp Variable.h Math.h String.h Char.h Numeric.h Real.h
Variable.o: Variable.cpp Variable.h
Math.o: Math.cpp Math.h Variable.h
String.o: String.cpp String.h Variable.h Numeric.h Char.h
Char.o: Char.cpp Char.h Variable.h
Numeric.o: Numeric.cpp Numeric.h Math.h
Real.o: Real.cpp Real.h Math.h
Jump.o: Jump.cpp
