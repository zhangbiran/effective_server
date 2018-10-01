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