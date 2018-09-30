#include "thread.h"
#include <windows.h>

DWORD WINAPI threadProc(LPVOID param)
{
	ThreadProc* command = (ThreadProc*)param;
	return command->excute();
}

Thread::Thread(ThreadProc* command)
{
	_command = command;
}

void Thread::excute()
{
	CreateThread(NULL, 0, threadProc, _command, 0, &_threadId);
}
