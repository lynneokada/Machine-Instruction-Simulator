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

all : server client

#Link command:
server : mis.o Variable.o Math.o String.o Char.o Numeric.o Real.o Jump.o MISMain.o Server.o TCPSocket.o TCPServerSocket.o
	$(GPP) $(GPPFLAGS) mis.o Variable.o Math.o String.o Char.o \
	Numeric.o Real.o Jump.o MISMain.o Server.o TCPSocket.o TCPServerSocket.o -o server

client : mis.o Variable.o Math.o String.o Char.o Numeric.o Real.o Jump.o MISMain.o Client.o TCPSocket.o TCPServerSocket.o
	$(GPP) $(GPPFLAGS) mis.o Variable.o Math.o String.o Char.o \
	Numeric.o Real.o Jump.o MISMain.o Client.o TCPSocket.o TCPServerSocket.o -o client

#Compilation commands:
%.o : %.cpp
	$(GPP) $(GPPFLAGS) -c $<

clean :
	- rm *.o main *.out *.err

# Dependencies
MISMain.o: MISMain.cpp mis.h 
mis.o: mis.cpp Variable.h Math.h String.h Char.h Numeric.h Real.h
Variable.o: Variable.cpp Variable.h
Math.o: Math.cpp Math.h Variable.h
String.o: String.cpp String.h Variable.h Numeric.h Char.h
Char.o: Char.cpp Char.h Variable.h
Numeric.o: Numeric.cpp Numeric.h Math.h
Real.o: Real.cpp Real.h Math.h
Jump.o: Jump.cpp Jump.h Math.h
Server.o: Server.cpp Server.h TCPServerSocket.h TCPSocket.h mis.h
Client.o: Client.cpp Client.h TCPSocket.h
TCPSocket.o: TCPSocket.cpp TCPSocket.h includes.h
TCPServerSocket.o: TCPServerSocket.cpp TCPServerSocket.h TCPSocket.h includes.h
