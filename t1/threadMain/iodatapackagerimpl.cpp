#include "iodatapackagerimpl.h"
#include <windows.h>
#include "dataanalyzer.h"
#include "syncthreaddata.h"
#include "datacollector.h"

void SelectIODataPackager::handlerIOData(DataContainer* dataContainer)
{
	if (NULL == dataContainer)
		return;

	handleData(dataContainer);
}


void SelectIODataPackager::handleData(DataContainer* dataContainer)
{
	do
	{
		OneQuestData oneQuestData = DataAnalyzer::instance()->analyzer(dataContainer);
		if (oneQuestData._buf == NULL)
		{
			break;
		}

		SyncThreadDataWriter<CollectData>* collectDataWriter = waitForCollectData();
		collectDataWriter->_data._dataCollector = oneQuestData._dataCollector;
		collectDataWriter->_data.buf = oneQuestData._buf;
		collectDataWriter->_data.size = oneQuestData._size;

		SyncThreadDataWriter<LogicData>* logicData = waitForLogicData();
		logicData->_data._collectDataWriteInterface = collectDataWriter;
		logicData->_data.stream.init(oneQuestData._buf, oneQuestData._size);
		logicData->setCanRead();

		collectBuffer();

	} while (1);
}

SyncThreadDataWriter<LogicData>* SelectIODataPackager::waitForLogicData()
{
	do
	{
		auto logicDataWriter = _dataProvider->getWriteData();
		if (logicDataWriter != NULL)
			return logicDataWriter;

		Sleep(1);
	} while (1);
}

SyncThreadDataWriter<CollectData>* SelectIODataPackager::waitForCollectData()
{
	do
	{
		auto collectDataWriter = _dataCollectorProvider->getWriteData();
		if (collectDataWriter != NULL)
			return collectDataWriter;

		Sleep(1);
	} while (1);
}

void SelectIODataPackager::collectBuffer()
{
	SyncThreadDataReader<CollectData>* syncThreadDataReader = _dataCollectorProvider->getReadData();
	if (syncThreadDataReader != NULL)
	{
		syncThreadDataReader->_data._dataCollector->collect(syncThreadDataReader->_data.buf,
			syncThreadDataReader->_data.size);
		syncThreadDataReader->setCanWrite();
	}
}