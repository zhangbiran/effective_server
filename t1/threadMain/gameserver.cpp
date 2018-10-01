#include "gameserver.h"
#include "serverenvir.h"
#include "threadprocs.h"

GameServer* GameServer::_instance = new GameServer();

GameServer::GameServer()
{
	_serverEnvir = new WindowsEnvir();

	for (int i = 0; i < 4; ++i)
	{
		_ioProc[i] = new IOThreadProc;
	}

	_logicProc = new LogicThreadProc();
	_sendThreadProc = new SendThreadProc();

}

GameServer::~GameServer()
{
	_serverEnvir->clearUp();
}

bool GameServer::startServer()
{
	if (!_serverEnvir->startUp())
		return false;



	return true;
}

bool GameServer::stopServer()
{
	delete this;
}