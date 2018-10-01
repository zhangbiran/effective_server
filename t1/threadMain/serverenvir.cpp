#include "serverenvir.h"
#include <assert.h>

WindowsEnvir::WindowsEnvir()
{

}

WindowsEnvir::~WindowsEnvir()
{
	WSACleanup();
}

bool WindowsEnvir::startUp()
{
	WSADATA wsaData = { 0 };
	int errCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	return 0 == errCode;
}

void WindowsEnvir::clearUp()
{
	WSACleanup();
}
