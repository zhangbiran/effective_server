#include "logicthread.h"
#include <iostream>
using namespace std;

int LogicThread::onStart()
{
	while (1)
	{
		cout << "hello world" << endl;
	}

	return 0;
}