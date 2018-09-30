#include "serverenvir.h"
#include <assert.h>

WindowsEnvir::WindowsEnvir()
{

}

WindowsEnvir::~WindowsEnvir()
{
	WSACleanup();
}

void WindowsEnvir::startUp()
{
	WSADATA wsaData = { 0 };
	int errCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	assert(0 == errCode);
}