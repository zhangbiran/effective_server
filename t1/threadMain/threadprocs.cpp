#include "threadprocs.h"
#include "datacollector.h"

int IOThreadProc::excute()
{
	int i = 0;
	while (1)
	{
		DataContainer* dataContainer = _ioReader->getData();
		if (dataContainer == NULL)
		{
			continue;
		}

		handleData(dataContainer);
	}
}

void IOThreadProc::handleData(DataContainer* dataContainer)
{
	do 
	{
		OneQuestData data = DataAnalyzer::instance()->analyzer(dataContainer);
		if (data._buf == NULL)
		{
			break;
		}

		WriteInterface<CollectData>* collectDataWriter = waitForCollectData();
		collectDataWriter->_data._dataCollector = data._dataCollector;
		collectDataWriter->_data.buf = data._buf;
		collectDataWriter->_data.size = data._size;

		WriteInterface<LogicData>* logicData = waitForLogicData();
		logicData->_data._collectDataWriteInterface = collectDataWriter;
		logicData->_data.stream.init(data._buf, data._size);
		logicData->setCanRead();

		collectBuffer();

	} while (1);
}

WriteInterface<LogicData>* IOThreadProc::waitForLogicData()
{
	do 
	{
		auto logicDataWriter = _dataProvider->getWriteData();
		if (logicDataWriter != NULL)
			return logicDataWriter;

		Sleep(1);
	} while (1);
}

WriteInterface<CollectData>* IOThreadProc::waitForCollectData()
{
	do
	{
		auto collectDataWriter = _dataCollectorProvider->getWriteData();
		if (collectDataWriter != NULL)
			return collectDataWriter;

		Sleep(1);
	} while (1);
}

void IOThreadProc::collectBuffer()
{
	ReadInterface<CollectData>* collectDataReader = _dataCollectorProvider->getReadData();
	if (collectDataReader != NULL)
	{
		collectDataReader->_data._dataCollector->collect(collectDataReader->_data.buf,
			collectDataReader->_data.size);
		collectDataReader->setCanWrite();
	}
}

int LogicThreadProc::excute()
{
	while (1)
	{
		for (int i = 0; i < _dataProvider.size(); ++i)
		{
			ReadInterface<LogicData>* data = _dataProvider[i]->getReadData();
			if (data == NULL)
			{
				//cout << "-----------------getReadData() NULL" << endl;
				//Sleep(10);
				continue;
			}

			//cout << data->_data.age << "  " << data->_data.score << endl;
			data->_data._collectDataWriteInterface->setCanRead();
			data->setCanWrite();

			WriteInterface<SendToIOData>* sendData = _sendToIODataProvider->getWriteData();
			if (sendData != NULL)
			{
				sendData->_data.name = "hahaha";
				sendData->_data.number = 100000000;
				sendData->setCanRead();
			}
		}
	}
}

int SendThreadProc::excute()
{
	while (1)
	{
		ReadInterface<SendToIOData>* data = _sendToIODataProvider->getReadData();
		if (data == NULL)
		{
			Sleep(10);
			continue;
		}

		//cout << data->_data.name << " " << data->_data.number << endl;
		data->setCanWrite();
	}
}