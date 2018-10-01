#ifndef __game_server_h
#define __game_server_h

class ServerEnvir;
class LogicThreadProc;
class SendThreadProc;
class IOThreadProc;

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

	LogicThreadProc* _logicProc;
	SendThreadProc* _sendThreadProc;
	IOThreadProc* _ioProc[4];

};


#endif