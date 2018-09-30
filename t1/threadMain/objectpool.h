#ifndef __obj_pool_h
#define __obj_pool_h

#include "memorypool.h"


template<class Type>
class ObjectPool : private MemoryPool
{
public:
	ObjectPool(int everyTimeIncreaseNum = 256, int maxNum = INT_MAX) :
		MemoryPool((sizeof(Type) + MEMORY_HEAD_SIZE)*everyTimeIncreaseNum, maxNum)
	{

	}

	Type* allocObject()
	{
		Type*p = (Type*)alloc(sizeof(Type));
		::new(p)Type();
		return p;
	}

	void freeObject(const Type* obj)
	{
		obj->~Type();
		free((char*)obj);
	}
};

#endif