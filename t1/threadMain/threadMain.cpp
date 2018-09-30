#include <iostream>
using namespace std;
#include <windows.h>
#include "loop.h"
#include "twothreaddata.h"
#include "threadprocs.h"

#include "testdata.h"
#include "stream.h"
#include "memorypool.h"
#include "objectpool.h"
#include "serverenvir.h"
#include "ioreader.h"

int main(void)
{
	ServerEnvir* serverEnvir = new WindowsEnvir();
	serverEnvir->startUp();

	const int n = 6;

	LogicThreadProc* logicProc = new LogicThreadProc;

	Thread *ioThread[n];
	for (int i = 0; i < n; ++i)
	{
		TwoThreadData<LogicData>* ioDataProvider = new TwoThreadData < LogicData >();

		IOThreadProc* ioThreadProc = new IOThreadProc;
		ioThreadProc->_dataProvider = ioDataProvider;
		ioThreadProc->_ioReader = new SelectIOReader();
		ioThreadProc->_dataCollectorProvider = new TwoThreadData < CollectData>();
		logicProc->_dataProvider.push_back(ioDataProvider);

		ioThread[i] = new Thread(ioThreadProc);
	}

	for (int i = 0; i < n; ++i)
	{
		ioThread[i]->excute();
	}

	SendThreadProc* sendThreadProc = new SendThreadProc();
	TwoThreadData<SendToIOData>* serverDataProvider = new TwoThreadData < SendToIOData >();
	sendThreadProc->_sendToIODataProvider = serverDataProvider;
	logicProc->_sendToIODataProvider = serverDataProvider;
	
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