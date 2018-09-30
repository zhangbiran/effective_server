#ifndef __two_thread_data_h
#define __two_thread_data_h
#include "loop.h"

#define CAN_WRITE 0
#define CAN_READ 1

template<class Type>
class SyData
{
public:
	Type _data;
protected:
	char _flag;

};

template<class Type>
class ReadInterface : virtual public SyData<Type>
{
public:
	
	void setCanWrite()
	{
		_flag = CAN_WRITE;
	}

	bool isCanWrite()
	{
		return _flag == CAN_WRITE;
	}

	
};

template<class Type>
class WriteInterface : virtual public SyData < Type >
{
public:
	void setCanRead()
	{
		_flag = CAN_READ;
	}


	bool isCanRead()
	{
		return _flag == CAN_READ;
	}
};

template<class Type>
class SyncData : public ReadInterface<Type>, public WriteInterface<Type>
{
public:
	SyncData()
	{
		setCanWrite();
	}
};

template<class Type>
class ThreadData
{
protected:
	Loop<SyncData<Type> > _datas;
	LoopIterator<SyncData<Type> > _readIt;
	LoopIterator<SyncData<Type> > _writeIt;
	int _size;
};

template<class Type>
class WriteDataProvider : virtual public ThreadData<Type>
{
public:
	WriteInterface<Type>* getWriteData()
	{
		if (!(*_writeIt).isCanWrite())
		{
			return NULL;
		}

		auto it = _writeIt;
		adjustWritePos();
		return &(*it);
	}

protected:
	void adjustWritePos()
	{
		auto itnext = _writeIt + 1;
		if (itnext == _datas.end())
			itnext = _datas.begin();

		if ((*itnext).isCanWrite())
		{
			_writeIt = itnext;
		}
		else
		{
			if (_datas.size() <= 10000)
			{
				appandSize();
				++_writeIt;
			}
			else
			{
				_writeIt = itnext;
			}
		
		}
	}

	void appandSize()
	{
		for (int i = 0; i < _size; ++i)
		{
			SyncData<Type> data;
			_datas.insertAfter(_writeIt, data);
		}

		//cout << "					size: " << _datas.size() << endl;
	}
};

template<class Type>
class ReadDataProvider : virtual public ThreadData<Type>
{
public:
	ReadInterface<Type>* getReadData()
	{
		if (!(*_readIt).isCanRead())
			return NULL;

		auto it = _readIt;
		adjustReadPos();
		return &(*it);
	}

protected:
	void adjustReadPos()
	{
		++_readIt;
		if (_readIt == _datas.end())
		{
			_readIt = _datas.begin();
		}
	}
};

template<class Type>
class TwoThreadData :public WriteDataProvider<Type>, public ReadDataProvider<Type>
{
public:
	TwoThreadData(int size = 10)
	{
		_size = size;

		for (int i = 0; i < _size; ++i)
		{
			SyncData<Type> data;
			_datas.appandToHead(data);
		}

		_writeIt = _datas.begin();
		_readIt = _writeIt;
	}
};

#endif