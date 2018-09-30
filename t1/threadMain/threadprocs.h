#ifndef __thread_proc_h
#define __thread_proc_h
#include "thread.h"
#include "twothreaddata.h"
#include "testdata.h"
#include <iostream>
using namespace std;
#include <vector>
#include "ioreader.h"
#include "dataanalyzer.h"

class IOThreadProc : public ThreadProc
{
public:
	int excute();
	void handleData(DataContainer* dataContainer);
	WriteInterface<LogicData>* waitForLogicData();
	WriteInterface<CollectData>* waitForCollectData();
	void collectBuffer();

	WriteDataProvider<LogicData>* _dataProvider;
	TwoThreadData<CollectData>* _dataCollectorProvider;
	IOReader* _ioReader;
};

class LogicThreadProc : public ThreadProc
{
public:
	int excute();

	std::vector<ReadDataProvider<LogicData>*> _dataProvider;
	WriteDataProvider<SendToIOData>* _sendToIODataProvider;
};

class SendThreadProc : public ThreadProc
{
public:
	int excute();

	ReadDataProvider<SendToIOData>*_sendToIODataProvider;
};

#endif