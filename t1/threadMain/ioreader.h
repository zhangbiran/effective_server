#ifndef __io_reader_h
#define __io_reader_h
#include "serverenvir.h"
#include <hash_map>

class DataContainer;

class IOReader
{
public:
	virtual ~IOReader() {}
	virtual DataContainer* getData() = 0;
};

class SelectIOReader : public IOReader
{
public:
	SelectIOReader();
	DataContainer* getData();

private:
	DataContainer* _testDataContainer;
	std::hash_map<SOCKET, DataContainer*> _dataContainers;
};


#endif