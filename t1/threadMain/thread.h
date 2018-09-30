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
	Thread(ThreadProc* command);
	void excute();

private:
	ThreadProc* _command;
	DWORD _threadId;
};

#endif
