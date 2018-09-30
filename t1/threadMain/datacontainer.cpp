#include "datacontainer.h"
#include "dataanalyzer.h"
#include "datacollector.h"
#include <memory>
#include "stream.h"
#include <assert.h>

DataContainer::~DataContainer()
{

}

RemoteIODataContainer::RemoteIODataContainer(int size)
{
	_size = size;
	char* _buf = (char*)malloc(size);
	memset(_buf, 0, size);
	_writePos = 0;
	_readPos = 0;

	_dataCollector = new RemoteIODataCollector(this);

	Stream stream(_buf, size);
	stream.writeInt(8);
	stream.writeInt(1000);
	stream.writeInt(2000);
	_writePos = 16;
}

OneQuestData RemoteIODataContainer::beAnalyzer(DataAnalyzer* dataAnalyzer)
{
	return dataAnalyzer->analyzerRemoteIODataContainer(this);
}

DataCollector* RemoteIODataContainer::getDataCollector()
{
	return _dataCollector;
}

void RemoteIODataContainer::addWritePos(int n)
{
	if (_writePos >= _readPos)
	{
		_writePos += n;
		if (_writePos >= _size)
		{
			_writePos %= _size;
			assert(_writePos <= _readPos);
		}
	}
	else
	{
		_writePos += n;
		assert(_writePos <= _readPos);
	}
}

void RemoteIODataContainer::addReadPos(int n)
{
	if (_readPos >= _writePos)
	{
		_readPos += n;
		if (_readPos >= _size)
		{
			_readPos %= _size;
			assert(_readPos <= _writePos);
		}
	}
	else
	{
		_readPos += n;
		assert(_readPos <= _writePos);
	}
}

int RemoteIODataContainer::getTotalCanWriteSize(int n) const
{
	if (_readPos >= _writePos)
		return _readPos - _writePos;
	return _size - _writePos + _readPos;
}

int RemoteIODataContainer::getTotalCanReadSize(int n) const
{
	if (_writePos >= _readPos)
		return _writePos - _readPos;
	return _size - _readPos + _writePos;
}

int RemoteIODataContainer::getToTailCanWriteSize() const
{
	if (_readPos >= _writePos)
		return _readPos - _writePos;
	return _size - _writePos;
}

int RemoteIODataContainer::getToTailCanReadSize() const
{
	if (_writePos >= _readPos)
		return _writePos - _readPos;
	return _size - _readPos;
}
