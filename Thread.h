#include <atomic>
#include <thread>
#include <string>
#include "mis.h"

class Thread
{
public:
	Thread();
	~Thread();

	//pass subset of v_line into function and do ::run as is own thread
	//need to figure out how to call threads using run and still writing to same output file
	//	-doesnt need to write to output file, just a buffer
	//	-buffer is globally accessed by only each CLIENT, not overall
	//	-need to make buffer to store to
	//spawns thread after reading input
	void makeThread(std::vector<string> instructions, Mis mis);

	//requires implementing mutexes on all variables
	//	-is recursive locking allowed?
	//	-do threads HAVE to be unlocked ever or is it valid for it to just lock?
	void lock();


	//need to be careful about unlocking a previously unlocked variable
	//	-possibly use an atomic boolean to represent locked/unlocked state
	//		-needs to utilize double check locking
	void unlock();
	

};