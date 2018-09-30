#ifndef __data_container_h
#define __data_container_h

class DataCollector;
#include "dataanalyzer.h"

class DataContainer
{
public:
	virtual ~DataContainer();
	virtual OneQuestData beAnalyzer(DataAnalyzer* dataAnalyzer) = 0;
	virtual DataCollector* getDataCollector() = 0;
};

class RemoteIODataContainer : public DataContainer
{
public:
	friend class DataAnalyzer;
	friend class RemoteIODataCollector;

	RemoteIODataContainer(int size = 4096);
	OneQuestData beAnalyzer(DataAnalyzer* dataAnalyzer);
	DataCollector* getDataCollector();

	void addWritePos(int n);
	void addReadPos(int n);
	int getTotalCanWriteSize(int n) const;
	int getTotalCanReadSize(int) const;
	int getToTailCanWriteSize() const;
	int getToTailCanReadSize() const;

private:
	char* _buf;
	int _size;
	int _writePos;
	int _readPos;
	DataCollector* _dataCollector;
};

#endif