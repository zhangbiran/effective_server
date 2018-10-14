#include "iodataproducer.h"

#include "datacontainer.h"

SelectIODataProducer::SelectIODataProducer()
{
	_testDataContainer = new RemoteIODataContainer();
}

DataContainer* SelectIODataProducer::productData()
{
	return _testDataContainer;
}

IOCPIODataProducer::IOCPIODataProducer()
{
	_testDataContainer = new RemoteIODataContainer();
}

DataContainer* IOCPIODataProducer::productData()
{
	return _testDataContainer;
}