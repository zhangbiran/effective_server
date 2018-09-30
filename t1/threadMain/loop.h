#ifndef __loop_h
#define __loop_h
#include <assert.h>
#include "objectpool.h"

template<class Type>
struct Item
{
	Type data;
	Item* prior;
	Item* next;
};

template<class Type>
class LoopIterator
{
public:

	LoopIterator(Item<Type>* item = NULL)
	{
		_item = item;
	}

	LoopIterator& operator ++ ()
	{
		_item = _item->next;
		return *this;
	}

	LoopIterator operator ++ (int)
	{
		LoopIterator oldItem(_item);
		_item = _item->next;
		return oldItem;
	}

	LoopIterator operator +(int n)
	{
		Item<Type>* item = _item;
		for (int i = 0; i < n; ++i)
		{
			item = item->next;
		}

		return LoopIterator(item);
	}

	LoopIterator& operator -- ()
	{
		_item = _item->prior;
		return *this;
	}

	LoopIterator& operator -- (int)
	{
		LoopIterator oldItem(_item);
		_item = _item->prior;
		return oldItem;
	}

	Type& operator* ()
	{
		return (_item->data);
	}

	bool operator != (const LoopIterator& other) const
	{
		return _item != other._item;
	}

	bool operator == (const LoopIterator& other) const
	{
		return _item == other._item;
	}


	Item<Type>* _item;
};

template<class Type, class Alloc=ObjectPool<Item<Type> > >
class Loop
{
public:
	Loop(Alloc* alloc = NULL) : _alloc(alloc)
	{
		if (_alloc == NULL)
		{
			_alloc = new Alloc(10);
		}

		_head = _alloc->allocObject();
		_tail = _alloc->allocObject();
		_head->prior = NULL;
		_head->next = _tail;
		_tail->prior = _head;
		_tail->next = NULL;
		_size = 0;
	}
	~Loop()
	{
		if (_alloc != NULL)
			delete _alloc;
	}

	void appandToHead(const Type& data)
	{
		Item<Type>* item = _alloc->allocObject();
		item->data = data;
		item->prior = _head;
		item->next = _head->next;
		_head->next->prior = item;
		_head->next = item;
		++_size;
	}

	void appandToTail(const Type& data)
	{
		Item<Type>* item = _alloc->allocObject();
		item->data = data;
		item->next = _tail;
		item->prior = _tail->prior;
		_tail->prior->next = item;
		_tail->prior = item;
		++_size;
	}

	void insertBefore(const LoopIterator<Type>& it, const Type& data)
	{
		assert(it._item != _head);
		Item<Type>* item = _alloc->allocObject();
		item->data = data;
		
		Item<Type>* refer = it._item;
		item->next = refer;
		item->prior = refer->prior;
		refer->prior->next = item;
		refer->prior = item;

		++_size;
	}

	void insertAfter(const LoopIterator<Type>& it, const Type& data)
	{
		assert(it._item != _tail);
		Item<Type>* item = _alloc->allocObject();
		item->data = data;

		Item<Type>* refer = it._item;
		item->prior = refer;
		item->next = refer->next;
		refer->next->prior = item;
		refer->next = item;

		++_size;
	}

	bool isEmpty()
	{
		if (_head->next == _tail)
		{
			assert(_size == 0);
			return true;
		}

		return false;
	}

	int size()
	{
		return _size;
	}

	LoopIterator<Type> begin()
	{
		LoopIterator<Type> iterator(_head->next);
		return iterator;
	}

	LoopIterator<Type> end()
	{
		LoopIterator<Type> iterator(_tail);
		return iterator;
	}
	
	void clear()
	{
		Item<Type>* p = _head->next;
		while (p != _tail)
		{
			_head->next = p->next;
			p->next->prior = _head;

			delete p;
			p = _head->next;
		}

		_size = 0;
	}

private:
	Alloc* _alloc;
	Item<Type>* _head;
	Item<Type>* _tail;
	int _size;
};




#endif
