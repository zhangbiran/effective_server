#include "threadprocs.h"
#include "datacollector.h"
#include <vector>

IOThreadProc::IOThreadProc(IODataProducer* producer, IODataPackager* handler)
{
	_ioDataProducer = producer;
	_ioDataPackager = handler;
}

int IOThreadProc::excute()
{
	int i = 0;
	while (1)
	{
		_ioDataPackager->handlerIOData(_ioDataProducer->productData());
	}
}

const IODataProducer* IOThreadProc::getProducer() const
{
	return _ioDataProducer;
}

const IODataPackager* IOThreadProc::getHandler() const
{
	return _ioDataPackager;
}


int LogicThreadProc::excute()
{
	while (1)
	{
		handleLogic();
	}
}

void LogicThreadProc::handleLogic()
{
	for (int i = 0; i < _logicDataConsumers.size(); ++i)
	{
		SyncThreadDataReader<LogicData>* syncThreadDataReader = _logicDataConsumers[i]->getReadData();
		if (syncThreadDataReader == NULL)
		{
			//cout << "-----------------getReadData() NULL" << endl;
			//Sleep(10);
			continue;
		}

		//cout << data->_data.age << "  " << data->_data.score << endl;
		syncThreadDataReader->_data._collectDataWriteInterface->setCanRead();
		syncThreadDataReader->setCanWrite();

		SyncThreadDataWriter<SendToIOData>* sendData = _sendDataProducer->getWriteData();
		if (sendData != NULL)
		{
			sendData->_data.name = "hahaha";
			sendData->_data.number = 100000000;
			sendData->setCanRead();
		}
	}
}

void LogicThreadProc::addLogicDataConsumer(SyncThreadDataConsumer<LogicData>* logcDataConsumer)
{
	_logicDataConsumers.push_back(logcDataConsumer);
}

void LogicThreadProc::setSendDataProducer(SyncThreadDataProducer<SendToIOData>* syncDataProducer)
{
	_sendDataProducer = syncDataProducer;
}


int SendThreadProc::excute()
{
	while (1)
	{
		sendData();
	}
}

void SendThreadProc::sendData()
{
	SyncThreadDataReader<SendToIOData>* data = _sendToIODataProvider->getReadData();
	if (data == NULL)
	{
		Sleep(10);
		return;
	}

	//cout << data->_data.name << " " << data->_data.number << endl;
	data->setCanWrite();
}