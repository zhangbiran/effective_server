#include "ioreader.h"

#include "datacontainer.h"

SelectIOReader::SelectIOReader()
{
	_testDataContainer = new RemoteIODataContainer();
}

DataContainer* SelectIOReader::getData()
{
	return _testDataContainer;
}