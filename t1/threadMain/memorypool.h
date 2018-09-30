#ifndef __memory_pool_h
#define __memory_pool_h

#include <vector>
#include <set>

struct MemoryHead
{
public:
	bool isUsing;
	int size;
	MemoryHead * priv;
	MemoryHead * next;

};

const int MEMORY_HEAD_SIZE = sizeof(MemoryHead);
const int MIN_SIZE = 100 + MEMORY_HEAD_SIZE;

class MemoryPool
{
public:
	MemoryPool(int everyBuffSize = 1024 * 1024, int maxNum = INT_MAX);
	~MemoryPool();
	char *alloc(int size);
	void free(const char* buf);

	int _alloced;
	int _total;
private:
	char* tryAllocBuf(int size);
	bool appandOne();
	std::vector<char*> _bufs;
	std::set<MemoryHead*> _memoryHeads;
	int _everyBuffSize;
	int _maxNum;
};


#endif