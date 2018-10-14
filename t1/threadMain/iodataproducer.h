#ifndef __io_reader_h
#define __io_reader_h
#include "serverenvir.h"
#include <hash_map>

class DataContainer;

class IODataProducer
{
public:
	virtual ~IODataProducer() {}
	virtual DataContainer* productData() = 0;
};

class SelectIODataProducer : public IODataProducer
{
public:
	SelectIODataProducer();
	DataContainer* productData();

private:
	DataContainer* _testDataContainer;
	std::hash_map<SOCKET, DataContainer*> _dataContainers;
};

class IOCPIODataProducer : public IODataProducer
{
public:
	IOCPIODataProducer();
	DataContainer* productData();

private:
	DataContainer* _testDataContainer;
};


#endif