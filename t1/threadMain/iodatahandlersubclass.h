#ifndef __io_data_handler_subclass_h
#define __io_data_handler_subclass_h

#include "iodatapackager.h"
#include "testdata.h"

class SelectIODataPackager : public IODataPackager
{
public:
	virtual void handlerIOData(DataContainer* dataContainer);

	void handleData(DataContainer* dataContainer);
	void collectBuffer();
	SyncThreadDataWriter<LogicData>* waitForLogicData();
	SyncThreadDataWriter<CollectData>* waitForCollectData();

	SyncThreadDataProducer<LogicData>* _dataProvider;
	SyncThreadData<CollectData>* _dataCollectorProvider;
};


#endif