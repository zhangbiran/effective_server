#include "gameserverconfig.h"


GameServerConfig::GameServerConfig()
{

}

GameServerConfig::~GameServerConfig()
{

}

GameServerConfig* GameServerConfig::instance()
{
	static GameServerConfig ins;
	return &ins;
}