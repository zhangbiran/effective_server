#ifndef __game_server_config_h
#define __game_server_config_h

class GameServerConfig
{
public:
	static GameServerConfig* instance();
private:
	GameServerConfig();
	~GameServerConfig();
};

#endif