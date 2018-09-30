#include "datacollector.h"
#include "memorypool.h"
#include <iostream>
using namespace std;

DataCollector::~DataCollector()
{

}

RemoteIODataCollector::RemoteIODataCollector(RemoteIODataContainer* dataContainer)
{
	_dataContainer = dataContainer;
}

void RemoteIODataCollector::collect(const char* buf, int size)
{
	cout << "»ØÊÕ:" << size << endl;
}

void MemoryPoolCollector::collect(const char* buf)
{
	_pool->free(buf);
}