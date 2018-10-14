#ifndef __thread_h
#define __thread_h
#include <windows.h>

class ThreadProc
{
public:
	virtual int excute() = 0;
};

class Thread
{
public:
	void start();
	virtual int onStart() = 0;
private:
	DWORD _threadId;
};

#endif
