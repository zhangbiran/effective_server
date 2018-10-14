#include "gameserver.h"
#include "serverenvir.h"
#include "threadprocs.h"
#include "iodataproducer.h"
#include "iodatapackager.h"

GameServer* GameServer::_instance = new GameServer();

GameServer::GameServer()
{
	_serverEnvir = new WindowsEnvir();
}

GameServer* GameServer::instance()
{
	return _instance;
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
	return true;
}