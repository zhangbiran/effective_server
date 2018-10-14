#include "thread.h"
#include <windows.h>

DWORD WINAPI threadProc(LPVOID param)
{
	Thread* thread = (Thread*)param;
	return (DWORD)thread->onStart();
}


void Thread::start()
{
	CreateThread(NULL, 0, threadProc, this, 0, &_threadId);
}


