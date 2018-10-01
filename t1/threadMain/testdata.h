#ifndef __DATA_
#define __DATA_
#include <iostream>
using namespace std;
#include "syncthreaddata.h"
#include "stream.h"

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}

	virtual void print()
	{
		cout << data << " ---- " << score << endl;
	}

	int data;
	int score;
};

class B : public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		cout << "~B()" << endl;
	}


	virtual void print()
	{
		cout << data << " #### " << score << endl;
	}
};




class DataCollector;
class OneQuestData;

class CollectData
{
public:
	DataCollector* _dataCollector;
	char*buf;
	int size;
};

class LogicData
{
public:
	Stream stream;
	SyncThreadDataWriter<CollectData>* _collectDataWriteInterface;
};

struct SendToIOData
{
public:
	int number;
	char* name;
};


#endif