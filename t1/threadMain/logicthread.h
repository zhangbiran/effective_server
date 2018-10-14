#ifndef __LOGIC_THREAD_H
#define __LOGIC_THREAD_H

#include "thread.h"

class LogicThread : public Thread
{
public:
	virtual int onStart();
};


#endif