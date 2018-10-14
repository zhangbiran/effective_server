#ifndef __game_server_h
#define __game_server_h

class ServerEnvir;

class GameServer
{
public:
	static GameServer* instance();
	virtual bool startServer();
	virtual bool stopServer();
private:
	GameServer();
	virtual ~GameServer();
	static GameServer* _instance;

private:
	ServerEnvir* _serverEnvir;
};


#endif