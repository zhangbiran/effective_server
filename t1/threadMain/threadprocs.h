#ifndef __thread_proc_h
#define __thread_proc_h
#include "thread.h"
#include "syncthreaddata.h"
#include "testdata.h"
#include <iostream>
using namespace std;
#include <vector>
#include "iodataproducer.h"
#include "dataanalyzer.h"
#include "iodatapackager.h"

class IOThreadProc : public ThreadProc
{
public:
	IOThreadProc(IODataProducer* producer, IODataPackager* handler);
	int excute();
	const IODataProducer* getProducer() const;
	const IODataPackager* getHandler() const;
private:
	IODataProducer* _ioDataProducer;
	IODataPackager* _ioDataHandler;
};

class LogicThreadProc : public ThreadProc
{
public:
	int excute();
	void handleLogic();
	void addLogicDataConsumer(SyncThreadDataConsumer<LogicData>* logcDataConsumer);
	void setSendDataProducer(SyncThreadDataProducer<SendToIOData>* syncDataProducer);
private:
	std::vector<SyncThreadDataConsumer<LogicData>*> _logicDataConsumers;
	SyncThreadDataProducer<SendToIOData>* _sendDataProducer;
};

class SendThreadProc : public ThreadProc
{
public:
	int excute();
	void sendData();

	SyncThreadDataConsumer<SendToIOData>*_sendToIODataProvider;
};

#endif