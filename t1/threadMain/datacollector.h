#ifndef __data_collector_h
#define __data_collector_h

class MemoryPool;
class RemoteIODataContainer;

class DataCollector
{
public:
	virtual ~DataCollector();
	virtual void collect(const char* buf, int size) = 0;
};

class RemoteIODataCollector : public DataCollector
{
public:
	RemoteIODataCollector(RemoteIODataContainer* dataContainer);
	void collect(const char* buf, int size);

private:
	RemoteIODataContainer* _dataContainer;
};



class MemoryPoolCollector : public DataCollector
{
public:
	MemoryPoolCollector(MemoryPool* pool)
	{
		_pool = pool;
	}

	void collect(const char* buf);

private:
	MemoryPool* _pool;
};

#endif