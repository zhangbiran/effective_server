#include "memorypool.h"
#include <assert.h>



MemoryPool::MemoryPool(int everyBuffSize, int maxNum) : _everyBuffSize(everyBuffSize)
{
	_alloced = 0;
	_total = 0;

	if (_everyBuffSize < MEMORY_HEAD_SIZE)
	{
		_everyBuffSize = 1024 + MEMORY_HEAD_SIZE;
	}

	appandOne();
}

MemoryPool::~MemoryPool()
{
	for (int i = 0; i < _bufs.size(); ++i)
	{
		::free(_bufs[i]);
	}

	_bufs.clear();
	_memoryHeads.clear();
}

char *MemoryPool::alloc(int size)
{
	char *p = tryAllocBuf(size);
	if (p == NULL)
	{
		if (!appandOne())
			return NULL;
		return tryAllocBuf(size);
	}

	return p;
}

void MemoryPool::free(const char* buf)
{
	const char*p = buf - MEMORY_HEAD_SIZE;
	MemoryHead* memoryHead = (MemoryHead*)p;
	assert(memoryHead->isUsing);
	memoryHead->isUsing = false;
	_alloced -= (MEMORY_HEAD_SIZE + memoryHead->size);
	if (memoryHead->next != NULL && !memoryHead->next->isUsing)
	{
		memoryHead->size += (MEMORY_HEAD_SIZE + memoryHead->next->size);
		_memoryHeads.erase(memoryHead->next);
		memoryHead->next = NULL;
	}

	if (memoryHead->priv != NULL && !memoryHead->priv->isUsing)
	{
		memoryHead->priv->size += (MEMORY_HEAD_SIZE + memoryHead->size);

		if (memoryHead->next != NULL)
			memoryHead->next->priv = memoryHead->priv;

		memoryHead->priv->next = memoryHead->next;
	}
	else
	{
		_memoryHeads.insert(memoryHead);
	}
}

char* MemoryPool::tryAllocBuf(int size)
{
	for (auto it = _memoryHeads.begin(); it != _memoryHeads.end(); ++it)
	{
		if ((*it)->size < size)
		{
			continue;
		}

		MemoryHead* memoryHead = (*it);
		char*p = ((char*)(memoryHead))+MEMORY_HEAD_SIZE;
		memoryHead->isUsing = true;

		if (memoryHead->size - size >= MIN_SIZE)
		{
			MemoryHead* newMemoryHead = (MemoryHead*)(p + size);
			newMemoryHead->isUsing = false;
			newMemoryHead->size = memoryHead->size - size - MEMORY_HEAD_SIZE;
			newMemoryHead->priv = memoryHead;
			memoryHead->next = newMemoryHead;
			memoryHead->size = size;

			_memoryHeads.erase(it);
			_memoryHeads.insert(newMemoryHead);
			_alloced += memoryHead->size + MEMORY_HEAD_SIZE;
		}
		else
		{
			_memoryHeads.erase(it);
			_alloced += memoryHead->size + MEMORY_HEAD_SIZE;
		}

		return p;
	}

	return NULL;
}

bool MemoryPool::appandOne()
{
	if (_memoryHeads.size() < _maxNum)
	{
		char*p = (char*)malloc(_everyBuffSize);
		memset(p, 0, _everyBuffSize);
		_bufs.push_back(p);
		MemoryHead* memoryHead = (MemoryHead*)p;
		memoryHead->isUsing = false;
		memoryHead->size = _everyBuffSize - MEMORY_HEAD_SIZE;
		memoryHead->priv = NULL;
		memoryHead->next = NULL;
		_memoryHeads.insert(memoryHead);
		_total += _everyBuffSize;
		return true;
	}

	return false;
}
