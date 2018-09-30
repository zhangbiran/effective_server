#ifndef __windows_envir_h
#define __windows_envir_h

#include <windows.h>
#pragma comment(lib, "ws2_32.lib")


class ServerEnvir
{	
public:
	virtual ~ServerEnvir() {}
	virtual void startUp() = 0;
};

class WindowsEnvir : public ServerEnvir
{
public:
	WindowsEnvir();
	~WindowsEnvir();
	void startUp();
};

	






#endif