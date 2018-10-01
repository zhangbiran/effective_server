#include "gameserverconfig.h"


GameServerConfig* GameServerConfig::instance()
{
	static GameServerConfig ins;
	return &ins;
}