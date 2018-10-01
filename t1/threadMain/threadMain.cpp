#include <iostream>
using namespace std;
#include <windows.h>
#include "loop.h"
#include "syncthreaddata.h"
#include "threadprocs.h"

#include "testdata.h"
#include "stream.h"
#include "memorypool.h"
#include "objectpool.h"
#include "iodataproducer.h"
#include "iodatahandlersubclass.h"
#include "gameserver.h"

int main(int argc, char** argv)
{
	if (!GameServer::instance()->startServer())
	{
		GameServer::instance()->stopServer();
	}

	const int n = 6;

	LogicThreadProc* logicProc = new LogicThreadProc;
	SendThreadProc* sendThreadProc = new SendThreadProc();
	IOThreadProc* ioProc[n];
	Thread *ioThread[n];
	IODataProducer* iodataProducer[n];
	IODataPackager* iodataHandler[n];

	for (int i = 0; i < n; ++i)
	{
		iodataProducer[i] = new SelectIODataProducer();
		iodataHandler[i] = new SelectIODataPackager();
		ioProc[i] = new IOThreadProc(iodataProducer[i], iodataHandler[i]);
		ioThread[i] = new Thread(ioProc[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		ioThread[i]->excute();
	}

	SyncThreadData<SendToIOData>* serverDataProvider = new SyncThreadData < SendToIOData >();
	sendThreadProc->_sendToIODataProvider = serverDataProvider;
	//logicProc->_sendDataProducer = serverDataProvider;
	
	Thread sendThread(sendThreadProc);
	sendThread.excute();
	Thread logicThread(logicProc);
	logicThread.excute();






	ObjectPool<B> objPool;
	A* b = objPool.allocObject();
	b->data = 200;
	b->score = 100;
	b->print();

	B*temp = (B*)b;
	objPool.freeObject(temp);
	

	getchar();
	return 0;
}