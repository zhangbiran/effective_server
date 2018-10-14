#include <iostream>
using namespace std;
#include <windows.h>
#include "gameserver.h"

int main(int argc, char** argv)
{
	if (!GameServer::instance()->startServer())
	{
		GameServer::instance()->stopServer();
	}

	getchar();
	return 0;
}